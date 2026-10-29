#pragma once
#include <avr/io.h>
#include "del.h"
#include "moteurs.h"
#include "minuterie2.h"
#include "memoire_24.h"

class Interpreteur {
public:
    Interpreteur(Del& del);
    void executerProgramme();

private:
    void lireTaille();
    void executerInstruction(uint8_t instruction, uint8_t operande);
    void attendre(uint8_t nbUnites);
    void allumerDel(uint8_t operande);
    void jouerNote(uint8_t note);
    void deplacer(uint8_t vitesse, Direction direction);
    void tourner(Direction directionGauche, Direction directionDroite);

    Memoire24CXXX memoire_;
    Moteurs moteurs_;
    Minuterie2 son_;
    Del& del_;
    uint16_t taille_;
    uint16_t adresse_;
    uint16_t adresseBoucle_;
    uint8_t compteurBoucle_;
    bool estCommence_;
    bool estTermine_;
};
