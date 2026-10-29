/*
 * Fichier     : tp/tp7/lib/minuterie1.cpp
 * Description : Delais avec la minuterie 1 (16 bits, mode CTC)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "minuterie1.h"

void Minuterie1::demarrer(uint16_t dureeMs) {
    arreter();
    TCNT1 = 0;
    OCR1A = convertirEnCycles(dureeMs);
    TIFR1 |= (1 << OCF1A);

    TCCR1A &= ~MASQUE_MODE_A;
    TCCR1B &= ~MASQUE_MODE_B;
    TCCR1B |= (1 << WGM12) | HORLOGE_DIV_1024;
}

void Minuterie1::attendre(uint16_t dureeMs) {
    demarrer(dureeMs);
    while (!estExpiree()) {
    }
    arreter();
}

bool Minuterie1::estExpiree() {
    if ((TIFR1 & (1 << OCF1A)) == 0) {
        return false;
    }
    TIFR1 |= (1 << OCF1A);
    return true;
}

void Minuterie1::activerInterruption() {
    TIMSK1 |= (1 << OCIE1A);
}

void Minuterie1::desactiverInterruption() {
    TIMSK1 &= ~(1 << OCIE1A);
}

void Minuterie1::arreter() {
    TCCR1B &= ~MASQUE_HORLOGE;
}

uint16_t Minuterie1::convertirEnCycles(uint16_t dureeMs) {
    const uint32_t cyclesParSeconde = F_CPU / PRESCALER;
    const uint32_t cycles = cyclesParSeconde * dureeMs / MS_PAR_SECONDE;
    return (cycles == 0) ? 0 : static_cast<uint16_t>(cycles - 1);
}
