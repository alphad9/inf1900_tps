#include <avr/io.h>
#include <util/delay.h>
#include "del.h"
#include "interpreteur.h"

const uint8_t NB_CLIGNOTEMENTS = 2;
const uint16_t DUREE_CLIGNOTEMENT_MS = 250;

void clignoter(Del& del, Couleur couleur) {
    for (uint8_t i = 0; i < NB_CLIGNOTEMENTS; i++) {
        del.changerCouleur(couleur);
        _delay_ms(DUREE_CLIGNOTEMENT_MS);
        del.changerCouleur(Couleur::ETEINTE);
        _delay_ms(DUREE_CLIGNOTEMENT_MS);
    }
}

void faireSequenceDemarrage(Del& del) {
    clignoter(del, Couleur::ROUGE);
    clignoter(del, Couleur::VERTE);
}

int main() {
    Del del(&PORTB, &DDRB, PB1, PB0);
    faireSequenceDemarrage(del);

    Interpreteur interpreteur(del);
    interpreteur.executerProgramme();
}