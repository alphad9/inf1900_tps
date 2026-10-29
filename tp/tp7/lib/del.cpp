/*
 * Fichier     : tp/tp7/lib/del.cpp
 * Description : DEL bicolore (rouge, verte, ambre) sur deux broches
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "del.h"

#include <util/delay.h>

Del::Del(volatile uint8_t* port, volatile uint8_t* ddr,
         uint8_t brocheRouge, uint8_t brocheVerte)
    : port_(port), brocheRouge_(brocheRouge), brocheVerte_(brocheVerte) {
    *ddr |= (1 << brocheRouge) | (1 << brocheVerte);
}

void Del::changerCouleur(Couleur couleur) {
    switch (couleur) {
        case Couleur::ROUGE:
            *port_ |= (1 << brocheRouge_);
            *port_ &= ~(1 << brocheVerte_);
            break;

        case Couleur::VERTE:
            *port_ |= (1 << brocheVerte_);
            *port_ &= ~(1 << brocheRouge_);
            break;

        case Couleur::ETEINTE:
            *port_ &= ~(1 << brocheRouge_);
            *port_ &= ~(1 << brocheVerte_);
            break;
    }
}

void Del::afficherAmbre() {
    changerCouleur(Couleur::ROUGE);
    _delay_ms(DUREE_ALTERNANCE_AMBRE_MS);
    changerCouleur(Couleur::VERTE);
    _delay_ms(DUREE_ALTERNANCE_AMBRE_MS);
}
