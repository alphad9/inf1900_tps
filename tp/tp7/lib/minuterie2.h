/*
 * Fichier     : tp/tp7/lib/minuterie2.h
 * Description : Generation de frequence pour le piezo (minuterie 2)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>

class Minuterie2 {
public:
    Minuterie2();

    void genererFrequence(uint16_t frequenceHz);
    void arreter();

private:
    static constexpr uint8_t BROCHE_SIGNAL = PD7;
    static constexpr uint8_t BROCHE_MASSE = PD6;
    static constexpr uint16_t PRESCALER = 256;
    static constexpr uint16_t FREQUENCE_MIN_HZ = 62;
    static constexpr uint16_t FREQUENCE_MAX_HZ = 15625;
    static constexpr uint8_t MASQUE_A =
        (1 << COM2A1) | (1 << COM2A0) | (1 << WGM21) | (1 << WGM20);
    static constexpr uint8_t MASQUE_B =
        (1 << WGM22) | (1 << CS22) | (1 << CS21) | (1 << CS20);
    static constexpr uint8_t HORLOGE_DIV_256 = (1 << CS22) | (1 << CS21);
};
