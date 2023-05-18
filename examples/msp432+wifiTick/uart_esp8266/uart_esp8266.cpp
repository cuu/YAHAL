/////////////////////////////////////////////////////////
// This is the program which is running on the ESP8266.
// It will receive messages via the Serial class. All
// received chars are collected in variable msg. When '\n'
// is received, the whole message is converted to upper
// case and send back using println (this will add a '\n'
// at the end!
/////////////////////////////////////////////////////////

#include "Arduino.h"

String msg;

void setup() {
    // Initialize the serial port
    Serial.begin(115200);
}

void loop() {
    // Check if char is available
    if (Serial.available()) {
        // Get the char
        char c = Serial.read();
        // Did we reach EOL?
        if (c == '\n') {
            // Convert message to upper case
            msg.toUpperCase();
            // Send back message
            Serial.println(msg);
            // Reset message buffer
            msg.clear();
        } else {
            // Add the char to the message
            msg += c;
        }
    }
}

