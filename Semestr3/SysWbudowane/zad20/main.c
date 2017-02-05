#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char n = 0;

int main() 
{
	//konfiguracja portow jako wyjscia
	DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4);

	// konfiguracja portow jako wejscia
	DDRD &= ~((1<<PD2) | (1<<PD3) | (1<<PD4)); //konfiguracja 2 pinu portu D jako wejście
	

	//przerwania wywolywane zboczem narastajacym
	EICRA |= (1<<ISC00);
	EICRA |= (1<<ISC01);
	EICRA |= (1<<ISC10);
	EICRA |= (1<<ISC11);
	sei();
	//wlaczenie przerwan
	EIMSK |= (1<<INT0) | (1<<INT1);
	//unsigned char prevState = PIND << PD4;
	while (1) 
	{
		if(PIND & (1 << PD4))
		{
			if(n == 0)
			{
				n = 1<<5;
				continue;
			}
			--n;
			PORTB = n ^ (n >> 1);
			_delay_ms(500);
		}
	}
}

ISR(INT0_vect)
{
	PORTB = 0;
	n = 0;
}

ISR(INT1_vect)
{
	++n;
	if(n > (1<<5))
		n = 0;
	PORTB = n ^ (n >> 1);
}