// Arduino includes
#include "SPISlave.h"
#include "ESP8266WiFi.h"

#include "WEB_Radio.h"

bool inHeader = true;
int  metaInt = 0;
int  receivedBytes = 0;

WEB_Radio::WEB_Radio() :
    fifo( FIFO_SIZE ),
    spiBufferPtr(nullptr),
    sda( 0 ),
    scl( 2 ),
    i2c(sda, scl, I2C_SLAVE_ADDR),
    sendSize ( 0 )
{
}

void WEB_Radio::setup(void)
{
    // Setup UART
    Serial.begin ( 115200 );
    // Setup SPI Slave and callback methods
    SPISlave.onData([this](uint8_t * data, size_t len) { });
    SPISlave.onDataSent([this] () { setSpiBuffer(); });
    SPISlave.begin();
}

void WEB_Radio::loop(void)
{
    /////////////////////
    // Connect to WLAN //
    /////////////////////
    if (i2c.connectWLAN()) {
        WiFi.mode(WIFI_STA);
        WiFi.begin ( i2c.ssid(), i2c.passwd() );
        // Wait for connection
        Serial.print("Trying to connect to ");
        Serial.print( i2c.ssid() );
        while ( WiFi.status() != WL_CONNECTED ) {
            delay ( 500 );
            Serial.print ( "." );
        }
        Serial.println ( "" );
        Serial.print   ( "Connected to ");
        Serial.println ( i2c.ssid() );
        Serial.print   ( "IP address: " );
        Serial.println ( WiFi.localIP() );
        i2c.connectWLAN(0);
    }
    delay(5);

    /////////////////////////////////
    // Connect to streaming server //
    /////////////////////////////////
    if (i2c.connectSRV()) {
        Serial.print("Trying to connect to ");
        Serial.print(i2c.httpHost());
        Serial.print(":");
        Serial.println(i2c.httpPort());
        // Stop client if it was connected before
//        if (client.connected()) {
//            client.stop();
//        }
        if (client.connect(i2c.httpHost(), i2c.httpPort())) {
            Serial.print("Connected to ");
            Serial.print(i2c.httpHost());
            Serial.print(":");
            Serial.println(i2c.httpPort());
            Serial.println();
        }
        String req = String ("GET "  ) + i2c.httpPath() + String (" HTTP/1.1\r\n") +
                     String ("Host: ") + i2c.httpHost() + String ("\r\n") +
                     String ("Icy-MetaData: 1\r\n")  +
                     String ("Connection: close\r\n");
        Serial.println("**** HTTP Request ****");
        Serial.println(req);
        client.println(req);
        i2c.connectSRV(0);
    }
    delay(5);

    /////////////////////////////////
    // Check for new received data //
    /////////////////////////////////
    if (client.available() >= TMP_BUFF_SIZE) {
        // Process HTTP Header
        //////////////////////
        if (inHeader) {
            Serial.println("**** HTTP Respone ****");
            while (inHeader) {
                String s = client.readStringUntil('\n');
                s.trim();
                Serial.println(s);
                if (s.length()) {
                    int colon = s.indexOf(':');
                    if (colon != -1) {
                        String key   = s.substring(0,colon);
                        String value = s.substring(colon+1);
                        key.trim();
                        value.trim();
                        if (key == "icy-metaint") {
                            metaInt = atoi(value.c_str());
                        }
                    }
                } else {
                    Serial.print("ICY metadata interval set to ");
                    Serial.println(metaInt);
                    inHeader = false;
                }
            }
        } else {
            int len = TMP_BUFF_SIZE;
            if (metaInt) {
                // Check if we need to read the metadata
                ////////////////////////////////////////
                if (receivedBytes == metaInt) {
                    int metaLen = client.read(); // Read numer of 16 bytes-chunks
                    if (metaLen) {
                        client.readBytes(buffer, metaLen * 16);
//                        memcpy(metaData, buffer, 320);
//                        metaData[320] = 0;
                        Serial.print("MetaInfo: ");
                        Serial.println((char*)buffer);
                    }
                    receivedBytes = 0;
                }
                // Calculate new amount of data to read
                ///////////////////////////////////////
                len = ((metaInt - receivedBytes) > TMP_BUFF_SIZE) ?
                        TMP_BUFF_SIZE : metaInt - receivedBytes;
            }
            // Read the data in any case so the internal
            // WiFiClient buffer does not overflow
            ////////////////////////////////////////////
            int result = client.read(buffer, len);
            receivedBytes += result;
            if (fifo.available_put() >= result) {
                for (int i=0; i < result; ++i) {
                    fifo.put( buffer[i] );
                }
                // Update FIFO size in I2C device
                i2c.fifoSize(fifo.available_get());
            }
        }
    }
    delay(5);

    ///////////////////////////////////////////////////////
    // Check if we need to prepare data for SPI transfer //
    ///////////////////////////////////////////////////////
    if (i2c.readData()) {
        Serial.print(fifo.available_get());
        Serial.print("     \r");
        uint16_t size = i2c.readData();
        // check if we have enough data
        if (fifo.available_get() >= size) {
            // Set the amount of data to send. We add 320
            // byte of metadata to every packet.
            sendSize = size; // + 320;
            // Fill the buffer
            for (int i=0; i < sendSize; ++i) {
                fifo.get( spiBuffer[i] );
            }
//            for (int i=0; i < 320; ++i) {
//                spiBuffer[i+sendSize] = metaData[i];
//            }
            spiBufferPtr = spiBuffer;
            setSpiBuffer();
            // Update FIFO size in I2C device
            i2c.fifoSize(fifo.available_get());
            // Reset the value to 0 so master can see we are ready
            i2c.readData(0);
        }
    }

    /////////////////////////////////////////////////////
    // Small delay to give WLAN and I2C slave a chance //
    /////////////////////////////////////////////////////
    delay(5);
}

void WEB_Radio::setSpiBuffer() {
    if (sendSize) {
        int size = (sendSize >= 32) ? 32 : sendSize;
        sendSize -= size;
        SPISlave.setData(spiBufferPtr, size);
        spiBufferPtr += size;
    }
}

