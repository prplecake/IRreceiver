//
// Created by prplecake on 10/7/23.
//

#include <Arduino.h>
#include "units.h"

void FRA12HT2(String command) // Adds info
{
    String unit = "Frigidaire FRA124HT2::";
    Serial.println(unit + command);
}