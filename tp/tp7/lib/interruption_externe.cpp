/*
 * Fichier     : tp/tp7/lib/interruption_externe.cpp
 * Description : Configuration des interruptions externes INT0 a INT2
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "interruption_externe.h"

InterruptionExterne::InterruptionExterne(uint8_t numero,
                                         Declencheur declencheur)
    : numero_(numero) {
    changerDeclencheur(declencheur);
}

void InterruptionExterne::activer() {
    EIMSK |= (1 << numero_);
}

void InterruptionExterne::desactiver() {
    EIMSK &= ~(1 << numero_);
}

void InterruptionExterne::changerDeclencheur(Declencheur declencheur) {
    desactiver();
    ecrireDeclencheur(declencheur);
    effacerDrapeau();
    activer();
}

void InterruptionExterne::effacerDrapeau() {
    EIFR |= (1 << numero_);
}

void InterruptionExterne::ecrireDeclencheur(Declencheur declencheur) {
    uint8_t code = static_cast<uint8_t>(declencheur);
    uint8_t position = numero_ * NB_BITS_PAR_DECLENCHEUR;
    EICRA &= ~(MASQUE_DECLENCHEUR << position);
    EICRA |= (code << position);
}
