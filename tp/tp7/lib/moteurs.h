/*
 * Fichier     : tp/tp7/lib/moteurs.h
 * Description : PWM materiel des deux roues (minuterie 0)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>

enum class Direction : uint8_t { AVANT, ARRIERE };

class Moteurs {
public:
    Moteurs();

    void ajusterRoueDroite(uint8_t vitesse, Direction direction);
    void ajusterRoueGauche(uint8_t vitesse, Direction direction);

    void arreterRoueDroite();
    void arreterRoueGauche();
    void arreter();

private:
    static constexpr uint8_t BROCHE_DIRECTION_GAUCHE = PB2;
    static constexpr uint8_t BROCHE_PWM_GAUCHE = PB3;
    static constexpr uint8_t BROCHE_PWM_DROITE = PB4;
    static constexpr uint8_t BROCHE_DIRECTION_DROITE = PB5;

    static constexpr uint8_t MASQUE_MODE_A = (1 << WGM01) | (1 << WGM00);
    static constexpr uint8_t MASQUE_MODE_B =
        (1 << WGM02) | (1 << CS02) | (1 << CS01) | (1 << CS00);

    static void ajusterDirection(uint8_t broche, Direction direction);
};
