/*
 * Fichier     : tp/tp7/lib/uart.h
 * Description : Communication RS232 avec le PC (2400 bauds)
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include <avr/io.h>
#include <stdint.h>

class Uart {
public:
    Uart();

    void transmettre(uint8_t donnee);
    void transmettre(const char* texte);
    void transmettreNombre(uint16_t nombre);
    uint8_t recevoir();

private:
    void initialiser();

    static constexpr uint16_t UBRR_2400_BAUDS = 207;
    static constexpr uint8_t TAILLE_TAMPON_NOMBRE = 6;
    static constexpr uint8_t BASE_DECIMALE = 10;
    static constexpr uint8_t BITS_PAR_OCTET = 8;
};
