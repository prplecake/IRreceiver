#include <Arduino.h>
#include "../lib/IRremote/IRremote.h"
#include "units.h"

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
        case 0xFFFFFFFF: Serial.println(" REPEAT"); break;
        case 0x10AF8877: FRA12HT2("POWER"); break;
        case 0x10AF708F: FRA12HT2("TEMP/TIMER UP"); break;
        case 0x10AFB04F: FRA12HT2("TEMP/TIMER DWN"); break;
        case 0x10AF807F: FRA12HT2("FAN SPEED+"); break;
        case 0x10AF20DF: FRA12HT2("FAN SPEED-"); break;
        case 0x10AF906F: FRA12HT2("COOL"); break;
        case 0x10AF40BF: FRA12HT2("ENERGY SAVER"); break;
        case 0x10AFE01F: FRA12HT2("FAN ONLY"); break;
        case 0x10AF00FF: FRA12HT2("SLEEP"); break;
        case 0x10AFF00F: FRA12HT2("AUTO FAN"); break;
        case 0x10AF609F: FRA12HT2("TIMER"); break;
        case 0x10AFF53B: FRA12HT2("REMOTE SENSING ON"); break;
        case 0x10AFF708: FRA12HT2("REMOTE SENSING OFF"); break;

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
