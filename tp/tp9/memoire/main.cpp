#include <avr/io.h>
#include <stdint.h>
#include "memoire_24.h"

void initialiserUART() {
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0A = 0;
    UCSR0B = (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t recevoirOctet() {
    while (!(UCSR0A & (1 << RXC0))) {
    }

    return UDR0;
}

int main() {
    initialiserUART();

    Memoire24CXXX memoire;

    uint8_t premierOctet = recevoirOctet();
    uint8_t deuxiemeOctet = recevoirOctet();

    uint16_t longueur = (uint16_t(premierOctet) << 8) | deuxiemeOctet;

    memoire.ecriture(0, premierOctet);
    memoire.ecriture(1, deuxiemeOctet);

    for (uint16_t adresse = 2; adresse < longueur; adresse++) {
        uint8_t octet = recevoirOctet();
        memoire.ecriture(adresse, octet);
    }

    return 0;
}
