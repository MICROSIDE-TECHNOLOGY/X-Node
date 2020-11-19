
/*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Implementar una lectura anal�gica de un potenci�metro, si el valor del ADC supera
un Set Point, el LED encender�.   
**************************************************************************/

#include <18F45K50.h>                     //Para PIC18F4550 cambiar por: #include <18F4550.h>
#DEVICE ADC=8                          //Configura el ADC a 8 bits
#use delay(internal=48MHz)              //Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)//Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000,0x1FFF {}                 //Reserva espacio en memoria para el bootloader
#define LED PIN_A1        //Pin donde est� conectado el LED de X-TRAINER

int ValorPot;                       //Variable para almacenar el valor le�do del ADC

void SisInit(void) 
{
   setup_adc_ports (sAN3); //Configura solo el puerto A0 como entrada anal�gica
   setup_adc (ADC_CLOCK_INTERNAL); //Configura oscilador interno para la conversi�n
}

void main()
{
   SisInit();

   while (1)
   {
      set_adc_channel (3); //Selecciona el canal 0 para la conversi�n
      ValorPot = read_adc (); //Lee el valor del ADC y lo guarda en la variable
      
      
      if (ValorPot >= 128) //Compara el valor de el ADC con 114
      {
         output_HIGH (LED); // Leds activos
      }

      else
      {
         output_LOW (LED); // Leds activos
      }
   }
}

