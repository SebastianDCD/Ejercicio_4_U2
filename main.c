#include "msp.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1->DIR |= BIT0;    //Configuramos el pin 1.0 como salida

	TIMER_A0->CCR[0] = 65000;   //Valor maximo de cuenta del temporizador
	TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
	//Temporizador de A0, modo de cuenta ascendente, borramos registro TAR de la cuenta

	while(1)
	{   //Comprobamos si la bandera A0 esta establecida
	    if((TIMER_A0->CTL & TIMER_A_CTL_IFG) != 0)  //
	    {
	        P1->OUT ^= BIT0;    //el Pin de salida 1.0, se invierte mediante una XOR
	        TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;  //Borramos la bandera de interrupcion
	    }
	}
}
