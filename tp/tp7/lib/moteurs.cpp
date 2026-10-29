/*
 * Fichier     : tp/tp7/lib/moteurs.cpp
 * Description : PWM materiel des deux roues (minuterie 0)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "moteurs.h"

Moteurs::Moteurs() {
    DDRB |= (1 << BROCHE_PWM_GAUCHE) | (1 << BROCHE_PWM_DROITE)
          | (1 << BROCHE_DIRECTION_GAUCHE) | (1 << BROCHE_DIRECTION_DROITE);

    arreter();
    PORTB &= ~((1 << BROCHE_DIRECTION_GAUCHE) | (1 << BROCHE_DIRECTION_DROITE));

    TCCR0A &= ~MASQUE_MODE_A;
    TCCR0B &= ~MASQUE_MODE_B;
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B |= (1 << CS01);
}

void Moteurs::ajusterRoueDroite(uint8_t vitesse, Direction direction) {
    ajusterDirection(BROCHE_DIRECTION_DROITE, direction);
    OCR0B = vitesse;
}

void Moteurs::ajusterRoueGauche(uint8_t vitesse, Direction direction) {
    ajusterDirection(BROCHE_DIRECTION_GAUCHE, direction);
    OCR0A = vitesse;
}

void Moteurs::arreterRoueDroite() {
    OCR0B = 0;
}

void Moteurs::arreterRoueGauche() {
    OCR0A = 0;
}

void Moteurs::arreter() {
    arreterRoueDroite();
    arreterRoueGauche();
}

void Moteurs::ajusterDirection(uint8_t broche, Direction direction) {
    if (direction == Direction::ARRIERE) {
        PORTB |= (1 << broche);
    } else {
        PORTB &= ~(1 << broche);
    }
}
