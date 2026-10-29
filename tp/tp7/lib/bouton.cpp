/*
 * Fichier     : tp/tp7/lib/bouton.cpp
 * Description : Lecture du bouton-poussoir avec anti-rebond
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "bouton.h"

#include <util/delay.h>

Bouton::Bouton(volatile uint8_t& pin, volatile uint8_t& ddr, uint8_t broche)
    : pin_(&pin), masque_(1 << broche) {
    ddr &= ~masque_;
}

bool Bouton::estAppuye() const {
    if (!lireEtat()) {
        return false;
    }
    _delay_ms(DELAI_ANTIREBOND_MS);
    return lireEtat();
}

bool Bouton::lireEtat() const {
    return (*pin_ & masque_) != 0;
}
