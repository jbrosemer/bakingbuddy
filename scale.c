#include “uart.h”
#include <stdlib.h>
#include <inttypes.h>
#include <p32xxxx.h>
#define ADDO_PORT PORTAbits.RA1 /* If ADC Data Input is connected to RD5 */
#define ADDO_SetHigh() LATAbits.LATA1 = 1
#define ADDO_SetLow() LATAbits.LATA1 = 0
#define ADDO_GetValue() PORTAbits.RA1
#define ADDO_TRIS TRISAbits.TRISA1 /*set RA1 as input */
#define ADDO_ANSEL ANSELAbits.ANSA1 /*set RA1 as input */
#define ADSCK_LAT LATAbits.LATA3 /* If ADC Clock signal is connected to RD0 */
#define ADSCK_TRIS TRISAbits.TRISA3
#define ADSCK_SetHigh() LATAbits.LATA3 = 1
#define ADSCK_SetLow() LATAbits.LATA3 = 0
// PIC16F877A Configuration Bit Settings
signed long weight;
float scaled;
int i;
float gain = 0.00332182; //calculated gain to callibrate load cell scale
float offset = 436411; //offset value of empty scale reading
signed long ReadCount() /* Function to read measurement from HX711 */
{
	signed long Count;
	unsigned char i;
	TRISA = 1;
	ADDO_TRIS = 1; /* Data line is Input to PIC */
	ADDO_ANSEL = 0;
	ADSCK_TRIS = 0; /* Clock line to Output from PIC */
	//ADSCK = 0; /* Clear Clock line to start conversion */
	Count = 0;
	while (ADDO_GetValue()); /* Wait for measurement conversion. */
	for (i=0; i<24; i++)
	{
		ADSCK_SetHigh(); /* Clock signal High */
		Count = Count << 1; /* Shift value left */

		ADSCK_SetLow(); /* Clock signal Low */
		Count = Count | ADDO_GetValue(); /* Read result bit from HX711 */
		//delay_ms(10);
	}
	for (i=0; i<3; i++) /* Resolution bits to HX711 */
	{ ADSCK_SetHigh();
		Nop();
		ADSCK_SetLow();
		Nop();
	}
	uart_init();
	analog_in_init();
	TRISB = 0;
	return Count;
}

float Convert(){ //function that converts HX711 reading to grams
	weight = ReadCount();
	scaled = gain*(offset – weight);
	return scaled;
}
