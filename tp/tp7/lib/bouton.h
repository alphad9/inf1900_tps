/*
 * Fichier     : tp/tp7/lib/bouton.h
 * Description : Lecture du bouton-poussoir avec anti-rebond
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>

class Bouton {
public:
    Bouton(volatile uint8_t& pin, volatile uint8_t& ddr, uint8_t broche);

    bool estAppuye() const;

private:
    static constexpr uint8_t DELAI_ANTIREBOND_MS = 10;

    bool lireEtat() const;

    volatile uint8_t* pin_;
    uint8_t masque_;
};
