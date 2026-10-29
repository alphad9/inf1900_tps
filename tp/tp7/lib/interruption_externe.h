/*
 * Fichier     : tp/tp7/lib/interruption_externe.h
 * Description : Configuration des interruptions externes INT0 a INT2
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>

enum class Declencheur : uint8_t {
    NIVEAU_BAS       = 0b00,
    CHANGEMENT       = 0b01,
    FRONT_DESCENDANT = 0b10,
    FRONT_MONTANT    = 0b11
};

class InterruptionExterne {
public:
    InterruptionExterne(uint8_t numero, Declencheur declencheur);

    void activer();
    void desactiver();
    void changerDeclencheur(Declencheur declencheur);
    void effacerDrapeau();

private:
    static constexpr uint8_t NB_BITS_PAR_DECLENCHEUR = 2;
    static constexpr uint8_t MASQUE_DECLENCHEUR = 0b11;

    void ecrireDeclencheur(Declencheur declencheur);

    uint8_t numero_;
};
