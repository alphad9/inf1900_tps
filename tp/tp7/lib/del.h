/*
 * Fichier     : tp/tp7/lib/del.h
 * Description : DEL bicolore (rouge, verte, ambre) sur deux broches
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>

enum class Couleur : uint8_t { ROUGE, VERTE, ETEINTE };

class Del {
public:
    Del(volatile uint8_t* port, volatile uint8_t* ddr,
        uint8_t brocheRouge, uint8_t brocheVerte);

    void changerCouleur(Couleur couleur);
    void afficherAmbre();

private:
    static constexpr uint8_t DUREE_ALTERNANCE_AMBRE_MS = 5;

    volatile uint8_t* port_;
    uint8_t brocheRouge_;
    uint8_t brocheVerte_;
};
