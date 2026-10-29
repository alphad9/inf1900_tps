/*
 * Fichier     : tp/tp7/exec/main.cpp
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 *
 * Test de librobot.a : DEL, son, roues et interruption INT0, puis la
 * machine a etat.
 *
 * Branchements : DEL PA0/PA1, bouton PD2 (cavalier IntEN), piezo
 * PD6/PD7, roue gauche PB2 (D) / PB3 (E), roue droite PB4 (E) / PB5 (D).
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "bouton.h"
#include "debug.h"
#include "del.h"
#include "interruption_externe.h"
#include "minuterie1.h"
#include "minuterie2.h"
#include "moteurs.h"
#include "uart.h"

namespace {
constexpr uint16_t DUREE_TEST_MS = 1000;
constexpr uint16_t FREQUENCE_LA_HZ = 440;
constexpr uint16_t FREQUENCE_LA_AIGU_HZ = 880;
constexpr uint8_t VITESSE_MOITIE = 128;
constexpr uint8_t NB_APPUIS_REQUIS = 3;
constexpr uint16_t DUREE_VERT_MS = 2000;
constexpr uint16_t DUREE_TEST_INTERRUPTION_MS = 5000;
constexpr uint8_t DELAI_ANTIREBOND_MS = 30;
constexpr uint8_t NUMERO_INT0 = 0;
}

volatile bool gBoutonAppuye = false;

ISR(INT0_vect) {
    gBoutonAppuye = true;
}

enum class Etat : uint8_t {
    ATTENTE_APPUI,
    ATTENTE_RELACHEMENT,
    VERT
};

void testerUart() {
    Uart uart;
    uart.transmettre("Test de librobot.a\r\n");
}

void testerDel(Del& del, Minuterie1& minuterie) {
    del.changerCouleur(Couleur::ROUGE);
    minuterie.attendre(DUREE_TEST_MS);

    del.changerCouleur(Couleur::VERTE);
    minuterie.attendre(DUREE_TEST_MS);

    minuterie.demarrer(DUREE_TEST_MS);
    while (!minuterie.estExpiree()) {
        del.afficherAmbre();
    }
    minuterie.arreter();

    del.changerCouleur(Couleur::ETEINTE);
}

void testerSon(Minuterie1& minuterie) {
    Minuterie2 son;
    son.genererFrequence(FREQUENCE_LA_HZ);
    minuterie.attendre(DUREE_TEST_MS);
    son.genererFrequence(FREQUENCE_LA_AIGU_HZ);
    minuterie.attendre(DUREE_TEST_MS);
    son.arreter();
}

void testerMoteurs(Minuterie1& minuterie) {
    Moteurs moteurs;

    moteurs.ajusterRoueGauche(VITESSE_MOITIE, Direction::AVANT);
    moteurs.ajusterRoueDroite(VITESSE_MOITIE, Direction::AVANT);
    minuterie.attendre(DUREE_TEST_MS);

    moteurs.ajusterRoueGauche(VITESSE_MOITIE, Direction::ARRIERE);
    moteurs.ajusterRoueDroite(VITESSE_MOITIE, Direction::ARRIERE);
    minuterie.attendre(DUREE_TEST_MS);

    moteurs.ajusterRoueGauche(VITESSE_MOITIE, Direction::AVANT);
    moteurs.arreterRoueDroite();
    minuterie.attendre(DUREE_TEST_MS);

    moteurs.arreter();
}

void testerInterruption(Del& del, Minuterie1& minuterie) {
    InterruptionExterne interruption(NUMERO_INT0, Declencheur::FRONT_MONTANT);
    gBoutonAppuye = false;
    sei();

    Couleur couleur = Couleur::ROUGE;
    del.changerCouleur(couleur);
    uint8_t nbAppuis = 0;

    minuterie.demarrer(DUREE_TEST_INTERRUPTION_MS);
    while (!minuterie.estExpiree()) {
        if (gBoutonAppuye) {
            _delay_ms(DELAI_ANTIREBOND_MS);
            gBoutonAppuye = false;
            interruption.effacerDrapeau();

            ++nbAppuis;
            DEBUG_PRINT("Interruption: ", nbAppuis);

            couleur = (couleur == Couleur::ROUGE) ? Couleur::VERTE
                                                  : Couleur::ROUGE;
            del.changerCouleur(couleur);
        }
    }
    minuterie.arreter();

    interruption.desactiver();
    del.changerCouleur(Couleur::ETEINTE);
}

int main() {
    Del del(&PORTA, &DDRA, PA1, PA0);
    Bouton bouton(PIND, DDRD, PD2);
    Minuterie1 minuterie;

    testerUart();
    testerDel(del, minuterie);
    testerSon(minuterie);
    testerMoteurs(minuterie);
    testerInterruption(del, minuterie);

    Etat etat = Etat::ATTENTE_APPUI;
    Etat etatPrecedent = Etat::VERT;
    uint8_t nbAppuis = 0;

    while (true) {
        switch (etat) {
            case Etat::ATTENTE_APPUI:
                if (bouton.estAppuye()) {
                    etat = Etat::ATTENTE_RELACHEMENT;
                }
                break;

            case Etat::ATTENTE_RELACHEMENT:
                if (!bouton.estAppuye()) {
                    ++nbAppuis;
                    if (nbAppuis >= NB_APPUIS_REQUIS) {
                        nbAppuis = 0;
                        minuterie.demarrer(DUREE_VERT_MS);
                        etat = Etat::VERT;
                    } else {
                        etat = Etat::ATTENTE_APPUI;
                    }
                }
                break;

            case Etat::VERT:
                if (minuterie.estExpiree()) {
                    minuterie.arreter();
                    etat = Etat::ATTENTE_APPUI;
                }
                break;
        }

        if (etat != etatPrecedent) {
            DEBUG_PRINT("Etat: ", etat);
            DEBUG_PRINT("Appuis: ", nbAppuis);
            etatPrecedent = etat;
        }

        switch (etat) {
            case Etat::ATTENTE_APPUI:
            case Etat::ATTENTE_RELACHEMENT:
                del.changerCouleur(Couleur::ETEINTE);
                break;

            case Etat::VERT:
                del.changerCouleur(Couleur::VERTE);
                break;
        }
    }
}
