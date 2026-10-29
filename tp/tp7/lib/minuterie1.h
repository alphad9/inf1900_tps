/*
 * Fichier     : tp/tp7/lib/minuterie1.h
 * Description : Delais avec la minuterie 1 (16 bits, mode CTC)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>

// Avec activerInterruption(), le materiel efface lui-meme l'indicateur :
// utiliser alors ISR(TIMER1_COMPA_vect) plutot que estExpiree().
class Minuterie1 {
public:
    void demarrer(uint16_t dureeMs);
    void attendre(uint16_t dureeMs);
    bool estExpiree();
    void activerInterruption();
    void desactiverInterruption();
    void arreter();

private:
    static constexpr uint16_t PRESCALER = 1024;
    static constexpr uint16_t MS_PAR_SECONDE = 1000;
    static constexpr uint8_t MASQUE_MODE_A = (1 << WGM11) | (1 << WGM10);
    static constexpr uint8_t MASQUE_MODE_B = (1 << WGM13) | (1 << WGM12);
    static constexpr uint8_t MASQUE_HORLOGE =
        (1 << CS12) | (1 << CS11) | (1 << CS10);
    static constexpr uint8_t HORLOGE_DIV_1024 = (1 << CS12) | (1 << CS10);

    static uint16_t convertirEnCycles(uint16_t dureeMs);
};
