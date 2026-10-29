#include "interpreteur.h"
#include <util/delay.h>

const uint8_t DBT = 0x01;
const uint8_t ATT = 0x02;
const uint8_t DAL = 0x44;
const uint8_t DET = 0x45;
const uint8_t SGO = 0x48;
const uint8_t SAR = 0x09;
const uint8_t MAR_1 = 0x60;
const uint8_t MAR_2 = 0x61;
const uint8_t MAV = 0x62;
const uint8_t MRE = 0x63;
const uint8_t TRD = 0x64;
const uint8_t TRG = 0x65;
const uint8_t DBC = 0xC0;
const uint8_t FBC = 0xC1;
const uint8_t FIN = 0xFF;

const uint16_t ADRESSE_TAILLE = 0;
const uint16_t ADRESSE_PREMIERE_INSTRUCTION = 2;
const uint8_t TAILLE_INSTRUCTION = 2;
const uint8_t NB_BITS_PAR_OCTET = 8;

const uint8_t DUREE_UNITE_ATTENTE_MS = 25;

const uint8_t OPERANDE_VERT = 1;
const uint8_t OPERANDE_ROUGE = 2;

const uint8_t VITESSE_VIRAGE = 200;
const uint16_t DUREE_VIRAGE_MS = 500;

const uint8_t NOTE_MIN = 45;
const uint8_t NOTE_MAX = 81;
const uint16_t FREQUENCES_NOTES_HZ[] = {
    110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208,
    220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415,
    440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831,
    880
};

Interpreteur::Interpreteur(Del& del)
    : del_(del),
      taille_(0),
      adresse_(ADRESSE_PREMIERE_INSTRUCTION),
      adresseBoucle_(ADRESSE_PREMIERE_INSTRUCTION),
      compteurBoucle_(0),
      estCommence_(false),
      estTermine_(false) {
}

void Interpreteur::executerProgramme() {
    lireTaille();

    while (adresse_ < taille_ && !estTermine_) {
        uint8_t instruction = 0;
        uint8_t operande = 0;
        memoire_.lecture(adresse_, &instruction);
        memoire_.lecture(adresse_ + 1, &operande);
        adresse_ += TAILLE_INSTRUCTION;

        if (instruction == DBT) {
            estCommence_ = true;
        }
        else if (estCommence_ && instruction == FIN) {
            estTermine_ = true;
        }
        else if (estCommence_) {
            executerInstruction(instruction, operande);
        }
    }

    moteurs_.arreter();
    son_.arreter();
}

void Interpreteur::lireTaille() {
    uint8_t haut = 0;
    uint8_t bas = 0;

    memoire_.lecture(ADRESSE_TAILLE, &haut);
    memoire_.lecture(ADRESSE_TAILLE + 1, &bas);

    taille_ = (static_cast<uint16_t>(haut) << NB_BITS_PAR_OCTET) | bas;
}

void Interpreteur::executerInstruction(uint8_t instruction, uint8_t operande) {
    switch (instruction) {
        case ATT:
            attendre(operande);
            break;

        case DAL:
            allumerDel(operande);
            break;

        case DET:
            del_.changerCouleur(Couleur::ETEINTE);
            break;

        case SGO:
            jouerNote(operande);
            break;

        case SAR:
            son_.arreter();
            break;

        case MAR_1:
        case MAR_2:
            moteurs_.arreter();
            break;

        case MAV:
            deplacer(operande, Direction::AVANT);
            break;

        case MRE:
            deplacer(operande, Direction::ARRIERE);
            break;

        case TRD:
            tourner(Direction::AVANT, Direction::ARRIERE);
            break;

        case TRG:
            tourner(Direction::ARRIERE, Direction::AVANT);
            break;

        case DBC:
            adresseBoucle_ = adresse_;
            compteurBoucle_ = operande;
            break;

        case FBC:
            if (compteurBoucle_ != 0) {
                adresse_ = adresseBoucle_;
                compteurBoucle_--;
            }
            break;
    }
}

void Interpreteur::attendre(uint8_t nbUnites) {
    for (uint8_t i = 0; i < nbUnites; i++) {
        _delay_ms(DUREE_UNITE_ATTENTE_MS);
    }
}

void Interpreteur::allumerDel(uint8_t operande) {
    if (operande == OPERANDE_VERT) {
        del_.changerCouleur(Couleur::VERTE);
    }
    else if (operande == OPERANDE_ROUGE) {
        del_.changerCouleur(Couleur::ROUGE);
    }
}

void Interpreteur::jouerNote(uint8_t note) {
    if (note >= NOTE_MIN && note <= NOTE_MAX) {
        son_.genererFrequence(FREQUENCES_NOTES_HZ[note - NOTE_MIN]);
    }
}

void Interpreteur::deplacer(uint8_t vitesse, Direction direction) {
    moteurs_.ajusterRoueGauche(vitesse, direction);
    moteurs_.ajusterRoueDroite(vitesse, direction);
}

void Interpreteur::tourner(Direction directionGauche, Direction directionDroite) {
    moteurs_.ajusterRoueGauche(VITESSE_VIRAGE, directionGauche);
    moteurs_.ajusterRoueDroite(VITESSE_VIRAGE, directionDroite);
    _delay_ms(DUREE_VIRAGE_MS);
    moteurs_.arreter();
}