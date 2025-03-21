////////////////////////////////////////////////////////////
// This is the test program which is running on the ESP8266.
// Use the WifiTick-Programmer to download this program
// to the WifiTick board!
////////////////////////////////////////////////////////

#include "Arduino.h"
#include "SPISlave.h"

void setup() {
    // Initialize the serial port
    Serial.begin(115200);

    // Initialize the SPI interface.
    // The ESP is the SPI master,
    // and running the SPI interface with 1MHz
    SPISlave.onData([](uint8_t * data, size_t len) {
        Serial.print("on Data cb: ");
        Serial.println((char * )data);
    });
    SPISlave.onDataSent([] () {
        SPISlave.setData("Message from the ESP8266!");
        Serial.println("onDataSent cb");
    });
    SPISlave.begin();
    SPISlave.setData("Message from the ESP8266!");
}

void loop() {
    delay(1000);
}

