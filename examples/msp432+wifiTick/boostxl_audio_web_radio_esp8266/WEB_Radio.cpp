// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//

#include "SPISlave.h"
#include "ESP8266WiFi.h"
#include "WEB_Radio.h"

WEB_Radio::WEB_Radio() :
    _fifo( FIFO_SIZE ),
    _inHeader(true),
    _metaInt(0),
    _receivedBytes(0),
    _spiBufferPtr(nullptr),
    _sda( 0 ),
    _scl( 2 ),
    _i2c(_sda, _scl, I2C_SLAVE_ADDR),
    _sendSize ( 0 )
{
}

void WEB_Radio::setSpiBuffer() {
    if (_sendSize) {
        int size = (_sendSize >= 32) ? 32 : _sendSize;
        _sendSize -= size;
        SPISlave.setData(_spiBufferPtr, size);
        _spiBufferPtr += size;
    }
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
    // Connect to WLAN
    if (_i2c.connectWLAN()) {
        connect_to_WLAN();
        _i2c.connectWLAN(0);
    }
    // Connect to streaming server
    if ((WiFi.status() == WL_CONNECTED) && _i2c.connectSRV()) {
        connect_to_server();
        _i2c.connectSRV(0);
    }
    // Disconnect from the server
    if (_i2c.stopSRV() && _client.connected()) {
        stop_server();
        _i2c.stopSRV(0);
    }

    /////////////////////////////////
    // Check for new received data //
    /////////////////////////////////
    if (_client.available() >= TMP_BUFF_SIZE) {
        // Process HTTP Header
        //////////////////////
        if (_inHeader) {
            Serial.println("**** HTTP Respone ****");
            while (_inHeader) {
                String s = _client.readStringUntil('\n');
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
                            _metaInt = atoi(value.c_str());
                        }
                    }
                } else {
                    // Found empty line -> end of HTTP header
                    Serial.print("ICY metadata interval set to ");
                    Serial.println(_metaInt);
                    _inHeader = false;
                }
            }
        } else {
            int len = TMP_BUFF_SIZE;
            if (_metaInt) {
                // Check if we need to read the metadata
                ////////////////////////////////////////
                if (_receivedBytes == _metaInt) {
                    int metaLen = _client.read(); // Read numer of 16 bytes-chunks
                    if (metaLen) {
                        _client.readBytes(_buffer, metaLen * 16);
//                        memcpy(metaData, buffer, 320);
//                        metaData[320] = 0;
                        Serial.print("MetaInfo: ");
                        Serial.println((char*)_buffer);
                    }
                    _receivedBytes = 0;
                }
                // Calculate new amount of data to read
                ///////////////////////////////////////
                len = ((_metaInt - _receivedBytes) > TMP_BUFF_SIZE) ?
                        TMP_BUFF_SIZE : _metaInt - _receivedBytes;
            }
            // Read the data in any case so the internal
            // WiFiClient buffer does not overflow
            ////////////////////////////////////////////
            int result = _client.read(_buffer, len);
            _receivedBytes += result;
            if (_fifo.available_put() >= result) {
                for (int i=0; i < result; ++i) {
                    _fifo.put( _buffer[i] );
                }
                // Update FIFO size in I2C device
                _i2c.fifoSize(_fifo.available_get());
            }
        }
    }

    ///////////////////////////////////////////////////////
    // Check if we need to prepare data for SPI transfer //
    ///////////////////////////////////////////////////////
    if (_client.connected() && _i2c.readData()) {
        Serial.print(_fifo.available_get());
        Serial.print("     \r");
        uint16_t size = _i2c.readData();
        // check if we have enough data
        if (_fifo.available_get() >= size) {
            // Set the amount of data to send. We add 320
            // byte of metadata to every packet.
            _sendSize = size; // + 320;
            // Fill the buffer
            for (int i=0; i < _sendSize; ++i) {
                _fifo.get( _spiBuffer[i] );
            }
//            for (int i=0; i < 320; ++i) {
//                spiBuffer[i+sendSize] = metaData[i];
//            }
            _spiBufferPtr = _spiBuffer;
            setSpiBuffer();
            // Update FIFO size in I2C device
            _i2c.fifoSize(_fifo.available_get());
            // Reset the value to 0 so master can see we are ready
            _i2c.readData(0);
        }
    }

    // Small delay to give WLAN and I2C slave a chance
    delay(20);
}


/////////////////////
// Connect to WLAN //
/////////////////////
void WEB_Radio::connect_to_WLAN() {
    WiFi.mode(WIFI_STA);
    WiFi.begin ( _i2c.ssid(), _i2c.passwd() );
    // Wait for connection
    Serial.print("Trying to connect to ");
    Serial.print( _i2c.ssid() );
    while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 500 );
        Serial.print ( "." );
    }
    Serial.println ( "" );
    Serial.print   ( "Connected to ");
    Serial.println ( _i2c.ssid() );
    Serial.print   ( "IP address: " );
    Serial.println ( WiFi.localIP() );
}

/////////////////////////////////
// Connect to streaming server //
/////////////////////////////////
void WEB_Radio::connect_to_server() {
    Serial.print("Trying to connect to ");
    Serial.print(_i2c.httpHost());
    Serial.print(":");
    Serial.println(_i2c.httpPort());
    if (_client.connect(_i2c.httpHost(), _i2c.httpPort())) {
        Serial.print("Connected to ");
        Serial.print(_i2c.httpHost());
        Serial.print(":");
        Serial.println(_i2c.httpPort());
        Serial.println();
    }
    String req = String ("GET "  ) + _i2c.httpPath() + String (" HTTP/1.1\r\n") +
                 String ("Host: ") + _i2c.httpHost() + String ("\r\n") +
                 String ("Icy-MetaData: 1\r\n")  +
                 String ("Connection: close\r\n");
    Serial.println("**** HTTP Request ****");
    Serial.println(req);
    _client.println(req);

    _sendSize = 0;
    _inHeader = true;
    _metaInt = 0;
    _receivedBytes = 0;
    _fifo.clear();
}

///////////////////////////
// Stop streaming server //
///////////////////////////
void WEB_Radio::stop_server() {
    _client.stop();
    while (_client.available()) {
        int bytes = _client.available();
        if (bytes > TMP_BUFF_SIZE) bytes = TMP_BUFF_SIZE;
        _client.readBytes(_buffer, bytes);
    }
}

