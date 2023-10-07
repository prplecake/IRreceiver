#include <Arduino.h>
#include "../lib/IRremote/IRremote.h"
#include "units.h"

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
        // Frigidaire FRA12HT2
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
        // Genuine Comfort GCTTW-12CRA2
        case 0x80FF48B7: GCTTW_12CRA2("POWER"); break;
        case 0x80FF58A7: GCTTW_12CRA2("UP"); break;
        case 0x80FFC837: GCTTW_12CRA2("DOWN"); break;
        case 0x80FF40BF: GCTTW_12CRA2("MODE"); break;
        case 0x80FF50AF: GCTTW_12CRA2("SLEEP"); break;
        case 0x80FF708F: GCTTW_12CRA2("SPEED"); break;
        case 0x80FFD827: GCTTW_12CRA2("TIMER"); break;
        case 0x80FF6897: GCTTW_12CRA2("ONE TOUCH"); break;
        case 0x80FFF00F: GCTTW_12CRA2("ENERGY SAVER"); break;

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
