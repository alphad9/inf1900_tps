/******************************************************************************/
/*                                                                            */
/* Isidore Lauzier - 9 juillet 2005                                           */
/*                                                                            */
/* Cet exemple d'utilisation d'une memoire eeprom i2c est une modification du */
/* programme de Joerg Wunsch twitest.c fourni avec Winavr. Il est compatible  */
/* aux eeprom 24C128, 24C256 et 24c512. Ce programme a ete simplifie afin     */
/* d'illustrer la programmation du bus TWI et des memoires I2C.               */
/*                                                                            */
/* NOTE IMPORTANTE: Le protocule I2C utilise les broches C0 et C1 sur un      */
/*                  microcontroleur Atmel ATMega244pa.                        */
/*                                                                            */
/* Modifications mineures:                                                    */
/*   - Pour refaire l'indentation - ete 2007 - Jerome Collin                  */
/*   - Pour preciser les broches utilisees - novembre 2008 - Jerome Collin    */
/*   - ajouts de commentaires - septembre 2017 - Jerome Collin                */
/*   - Correction de certains commentaires - septembre 2022 - Jérôme Collin   */
/*                                                                            */
/******************************************************************************/

#ifndef MEMOIRE_24_H
#define MEMOIRE_24_H

// F_CPU est défini par le Makefile via -DF_CPU=8000000UL
// NE PAS le définir ici pour éviter les conflits de redéfinition.

#include <avr/io.h>
#include <util/twi.h>

/**
 * Classe Memoire24CXXX - Interface I2C pour EEPROM 24LC256
 *
 * Branchement sur le robot:
 *   PC0 = SCL
 *   PC1 = SDA
 *   A0, A1, A2 reliés à la masse (adresse 0)
 *
 * Le constructeur appelle init() automatiquement.
 */
class Memoire24CXXX {
public:
    Memoire24CXXX();    // Le constructeur appelle init()
    ~Memoire24CXXX();

    // Initialisation de l'interface I2C (TWI).
    // Ne pas rappeler à moins de changements en cours d'utilisation.
    void init();

    // Choisir un banc mémoire (0 à 3)
    // Retourne l'adresse périphérique calculée, ou 255 si invalide
    static uint8_t choisir_banc(const uint8_t banc);

    // Lecture d'un seul octet à l'adresse donnée
    uint8_t lecture(const uint16_t adresse, uint8_t *donnee);

    // Lecture d'un bloc (longueur <= 127)
    uint8_t lecture(const uint16_t adresse, uint8_t *donnee,
                    const uint8_t longueur);

    // Écriture d'un seul octet à l'adresse donnée
    uint8_t ecriture(const uint16_t adresse, const uint8_t donnee);

    // Écriture d'un bloc (longueur <= 127)
    uint8_t ecriture(const uint16_t adresse, uint8_t *donnee,
                     const uint8_t longueur);

private:
    uint8_t ecrire_page(const uint16_t adresse, uint8_t *donnee,
                        const uint8_t longueur);

    static uint8_t m_adresse_peripherique;
    const uint8_t PAGE_SIZE;
};

#endif
