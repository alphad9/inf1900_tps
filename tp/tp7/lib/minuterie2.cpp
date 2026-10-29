/*
 * Fichier     : tp/tp7/lib/minuterie2.cpp
 * Description : Generation de frequence pour le piezo (minuterie 2)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "minuterie2.h"

Minuterie2::Minuterie2() {
    DDRD |= (1 << BROCHE_SIGNAL) | (1 << BROCHE_MASSE);
    PORTD &= ~(1 << BROCHE_MASSE);
    arreter();
}

void Minuterie2::genererFrequence(uint16_t frequenceHz) {
    if (frequenceHz < FREQUENCE_MIN_HZ) {
        frequenceHz = FREQUENCE_MIN_HZ;
    } else if (frequenceHz > FREQUENCE_MAX_HZ) {
        frequenceHz = FREQUENCE_MAX_HZ;
    }
    const uint32_t diviseur = 2UL * PRESCALER * frequenceHz;

    arreter();
    TCNT2 = 0;
    OCR2A = static_cast<uint8_t>(F_CPU / diviseur - 1);

    TCCR2A |= (1 << COM2A0) | (1 << WGM21);
    TCCR2B |= HORLOGE_DIV_256;
}

void Minuterie2::arreter() {
    TCCR2B &= ~MASQUE_B;
    TCCR2A &= ~MASQUE_A;
    PORTD &= ~(1 << BROCHE_SIGNAL);
}
