//Probleme 2 du TP4 de INF1900
#include <avr/interrupt.h>

volatile uint8_t gMinuterieExpiree;

volatile uint8_t gBoutonPoussoir;

ISR ( TIMER1_COMPA_vect ) {

gMinuterieExpiree = 1;

}



ISR ( INT0_vect ) {

gBoutonPoussoir = 1;

// anti-rebond

delay_ms(10)

}

void partirMinuterie ( uint16_t duree ) {

gMinuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024

// interruption après la durée spécifiée

TCNT1 = 0 ;

OCR1A = duree;

TCCR1A = 0 ;

TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

TCCR1C = 0;

TIMSK1 |= (1<< OCIE1A ) ;

}
void allumerRouge()
{
    PORTB |= (1 << PB4);
    PORTB &= ~(1 << PB5);
}

void eteindreDel()
{
    PORTB &= ~(1 << PB4);
    PORTB &= ~(1 << PB5);
}

void allumerVert()
{
    PORTB |= (1 << PB5);
    PORTB &= ~(1 << PB4);
}

int main() {
    DDRB |= (1 << PB4) | (1 << PB5);

    delay_ms(10000);

    allumerRouge();

    delay_ms(100);

    eteindreDel();
    do {

    // attendre qu'une des deux variables soit modifiée

    // par une ou l'autre des interruptions.

    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );



    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli ();

    // Verifier la réponse

    if (gBoutonPoussoir == 1)
    {
        allumerVert();
    }
    else if (gMinuterieExpiree == 1)
    {
        allumerRouge();
    }


}

