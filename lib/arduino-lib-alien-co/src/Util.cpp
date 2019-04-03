//
// Created by ferna on 07/07/2018.
//
#include <Arduino.h>
#include "Util.h"

unsigned int analogReadReference(void) {

    /* Elimine toutes charges résiduelles */
#if defined(__AVR_ATmega328P__)
    ADMUX = 0x4F;
#elif defined(__AVR_ATmega2560__)
    ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5F;
#elif defined(__AVR_ATmega32U4__)
    ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5F;
#endif
    delayMicroseconds(5);

    /* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
#if defined(__AVR_ATmega328P__)
    ADMUX = 0x4E;
#elif defined(__AVR_ATmega2560__)
    ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5E;
#elif defined(__AVR_ATmega32U4__)
    ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5E;
#endif
    delayMicroseconds(200);

    /* Active le convertisseur analogique -> numérique */
    ADCSRA |= (1 << ADEN);

    /* Lance une conversion analogique -> numérique */
    ADCSRA |= (1 << ADSC);

    /* Attend la fin de la conversion */
    while(ADCSRA & (1 << ADSC));

    /* Récupère le résultat de la conversion */
    return ADCL | (ADCH << 8);
}