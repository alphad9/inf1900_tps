/*
 * Fichier     : tp/tp7/lib/debug.h
 * Description : Macro DEBUG_PRINT active seulement avec make debug
 * Auteurs     : Nermine Morri, Felicia Remadji Libar,
 *               Kamal Chalhoub, Diaby Alpha Boubacar
 * INF1900 - equipe 0110
 */

#pragma once

#include "uart.h"

#ifdef DEBUG

#define DEBUG_PRINT(message, valeur)                           \
    do {                                                       \
        Uart uart;                                             \
        uart.transmettre(message);                             \
        uart.transmettreNombre(static_cast<uint16_t>(valeur)); \
        uart.transmettre("\r\n");                              \
    } while (0)

#else

#define DEBUG_PRINT(message, valeur) do {} while (0)

#endif
