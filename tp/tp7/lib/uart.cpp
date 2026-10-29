/*
 * Fichier     : tp/tp7/lib/uart.cpp
 * Description : Communication RS232 avec le PC (2400 bauds)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#include "uart.h"

#include <stdlib.h>

Uart::Uart() {
    initialiser();
}

void Uart::initialiser() {
    const uint8_t masqueActivation = (1 << RXEN0) | (1 << TXEN0);
    if ((UCSR0B & masqueActivation) == masqueActivation) {
        return;
    }

    UBRR0H = static_cast<uint8_t>(UBRR_2400_BAUDS >> BITS_PAR_OCTET);
    UBRR0L = static_cast<uint8_t>(UBRR_2400_BAUDS);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0B |= masqueActivation;
}

void Uart::transmettre(uint8_t donnee) {
    while ((UCSR0A & (1 << UDRE0)) == 0) {
    }
    UDR0 = donnee;
}

void Uart::transmettre(const char* texte) {
    while (*texte != '\0') {
        transmettre(static_cast<uint8_t>(*texte));
        texte++;
    }
}

void Uart::transmettreNombre(uint16_t nombre) {
    char tampon[TAILLE_TAMPON_NOMBRE];
    utoa(nombre, tampon, BASE_DECIMALE);
    transmettre(tampon);
}

uint8_t Uart::recevoir() {
    while ((UCSR0A & (1 << RXC0)) == 0) {
    }
    return UDR0;
}
