#include "WEB_Radio.h"

// Arduino includes
#include "SPISlave.h"
#include "ESP8266WiFi.h"

WEB_Radio::WEB_Radio() :
    fifo( FIFO_SIZE ),
    spiBufferPtr(nullptr),
    oneQuarter( 3 ),
    twoQuarters( 4 ),
    threeQuarters( 5 ),
    sda( 0 ),
    scl( 2 ),
    i2c(sda, scl, i2c_receive, i2c_transmit, i2c_stop, this),
    i2c_cmd  (-1 ),
    sendSize ( 0 )
{
}

WEB_Radio::~WEB_Radio()
{
    // Free I2C data area
    for (size_t i=0; i < I2C_COMMAND_SIZE; ++i) {
        delete [] i2c_cmd_data[i].data;
        i2c_cmd_data[i].data = nullptr;
    }
}


void WEB_Radio::setSpiBuffer() {
    if (sendSize) {
        int size = (sendSize >= 32) ? 32 : sendSize;
        sendSize -= size;
        SPISlave.setData(spiBufferPtr, size);
        spiBufferPtr += size;
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
    // Setup GPIOs
    oneQuarter.   gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
    twoQuarters.  gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);
    threeQuarters.gpioMode(GPIO::OUTPUT | GPIO::INIT_LOW);

    // Allocate I2C data space
    i2c_cmd_data[WLAN_SSID  ] = { 80, new char[80] };
    i2c_cmd_data[WLAN_PASSWD] = { 80, new char[80] };
    i2c_cmd_data[HTTP_HOST  ] = { 80, new char[80] };
    i2c_cmd_data[HTTP_PORT  ] = {  2, new char[ 2] };
    i2c_cmd_data[HTTP_PATH  ] = { 80, new char[80] };
    i2c_cmd_data[CONN_WLAN  ] = {  1, new char[ 1] };
    i2c_cmd_data[CONN_SRV   ] = {  1, new char[ 1] };
    i2c_cmd_data[DATA_SIZE  ] = {  2, new char[ 2] };
    // Clear I2C data area
    for (size_t i=0; i < I2C_COMMAND_SIZE; ++i) {
        memset(i2c_cmd_data[i].data, 0, i2c_cmd_data[i].len);
    }
    // Set I2C slave address
    i2c.setI2cAddress(I2C_SLAVE_ADDR);
}

void WEB_Radio::loop(void)
{
    //////////////////////
    // Connect to WLAN. //
    //////////////////////
    if (connectWLAN()) {
        WiFi.mode(WIFI_STA);
        WiFi.begin ( ssid(), passwd() );
        // Wait for connection
        while ( WiFi.status() != WL_CONNECTED ) {
            delay ( 500 );
            Serial.print ( "." );
        }
        Serial.println ( "" );
        Serial.print   ( "Connected to ");
        Serial.println ( ssid() );
        Serial.print   ( "IP address: " );
        Serial.println ( WiFi.localIP() );
        connectWLAN(0);
    }
    /////////////////////////////////
    // Connect to streaming server //
    /////////////////////////////////
    if (connectSRV()) {
        if (client.connect(httpHost(), httpPort())) {
            Serial.print("Connected to ");
            Serial.print(httpHost());
            Serial.print(":");
            Serial.println(httpPort());
        }
        String req = String ("GET "  ) + httpPath() + String (" HTTP/1.1\r\n") +
                     String ("Host: ") + httpHost() + String ("\r\n") +
                     //String ("Icy-MetaData: 1\r\n")  +
                     String ("Connection: close\r\n\r\n");
        Serial.println("Sending GET request:");
        Serial.println(req);
        client.print  (req);
        connectSRV(0);
    }
    /////////////////////////////////
    // Check for new received data //
    /////////////////////////////////
    if (client.available() >= TMP_BUFF_SIZE) {
        // Read the data in any case so the internal
        // WiFiClient buffer does not overflow
        client.read(buffer, TMP_BUFF_SIZE);
        if (fifo.available_put() >= TMP_BUFF_SIZE) {
            for (int i=0; i < TMP_BUFF_SIZE; ++i) {
                fifo.put( buffer[i] );
            }
        }
    }
    //////////////////////
    // Update the GPIOS //
    //////////////////////
    int avail = fifo.available_get();
    oneQuarter.   gpioWrite( avail >=     (FIFO_SIZE / 4) );
    twoQuarters.  gpioWrite( avail >=     (FIFO_SIZE / 2) );
    threeQuarters.gpioWrite( avail >= (3 * FIFO_SIZE / 4) );

    delay(5);
}

// I2C callback methods
///////////////////////
bool WEB_Radio::i2c_receive (uint16_t index, uint8_t data, void *ptr)
{
    WEB_Radio * _this = (WEB_Radio *)ptr;
    i2c_cmd_struct * cmd_ptr = nullptr;

    if (index==0) {
        // Process the command number
        if (data < I2C_COMMAND_SIZE) {
            _this->i2c_cmd = data;
            return true;
        } else {
            _this->i2c_cmd = -1;
        }
    } else {
        // Process data item
        if (_this->i2c_cmd != -1) {
            cmd_ptr = &(_this->i2c_cmd_data[_this->i2c_cmd]);
        } else return false;
        if ((index <= cmd_ptr->len)) {
            cmd_ptr->data[index-1] = data;
        } else return false;
        if ((_this->i2c_cmd == DATA_SIZE) && (index == 2)) {
            // Set the amount of data to send ...
            _this->sendSize = _this->dataSize();
            // ... and fill the buffer
            for (int i=0; i < _this->sendSize; ++i) {
                _this->fifo.get( _this->spiBuffer[i] );
            }
            _this->spiBufferPtr = _this->spiBuffer;
            _this->setSpiBuffer();
        }
        return true;
    }
    return false;
}

uint8_t WEB_Radio::i2c_transmit(uint16_t index, void *ptr)
{
    WEB_Radio * _this = (WEB_Radio *)ptr;
    if (_this->i2c_cmd != -1) {
        i2c_cmd_struct * cmd_ptr = &(_this->i2c_cmd_data[_this->i2c_cmd]);
        if (index <= cmd_ptr->len) {
            return cmd_ptr->data[index-1];
        }
    }
    return 0;
}

// This function is not used
void WEB_Radio::i2c_stop(void *)
{
}

