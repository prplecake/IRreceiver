#include <Arduino.h>
#include "../lib/IRremote/IRremote.h"

#define DHT_SENSOR_TYPE DHT_TYPE_11

// Initialize pins
static const int IR_RECEIVER_PIN = 3;

// Declare objects
IRrecv irrecv(IR_RECEIVER_PIN);
decode_results results;

/*
 * Initialize the serial port.
 */
__attribute__((unused)) void setup( )
{
    Serial.begin( 9600);
    irrecv.enableIRIn();
}

void translateIR() // takes action based on IR code received
{
    switch(results.value)
    {
        // describing Remote IR codes
        case 0xFFFFFFFF: Serial.println(" REPEAT");break;
        case 0x80FF48B7: Serial.println("POWER"); break;
        case 0x80FF58A7: Serial.println("UP"); break;
        case 0x80FFC837: Serial.println("DOWN"); break;
        case 0x80FF40BF: Serial.println("MODE"); break;
        case 0x80FF50AF: Serial.println("SLEEP"); break;
        case 0x80FF708F: Serial.println("SPEED"); break;
        case 0x80FFD827: Serial.println("TIMER"); break;
        case 0x80FF6897: Serial.println("ONE TOUCH"); break;
        case 0x80FFF00F: Serial.println("ENERGY SAVER"); break;

        default:
            Serial.print(" other input  ");
            Serial.print("\tvalue: 0x");
            Serial.println(results.value, HEX);

    }// End Case

    delay(500); // Do not get immediate repeat


} //END translateIR


/*
 * Main program loop.
 */
__attribute__((unused)) void loop( )
{

    if (irrecv.decode(&results)) // have we received an IR signal?

    {
        translateIR();
        irrecv.resume(); // receive the next value
    }
}
