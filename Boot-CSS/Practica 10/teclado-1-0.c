 /*

AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.

FECHA: JUNIO 2019

*/

/**************************************************************************

En esta práctica se realiza el control de encendido o apagado de un LED mediante un teclado matricial,

que al presionar la tecla 1 se enciende el LED y al presionar la tecla 0 se apagará el LED.

**************************************************************************/

 

#include <18F45K50.h>                                // Para PIC18F4550 cambiar por: #include <18F4550.h>

#use delay(internal=48MHz)                          // Tipo de oscilador y frecuencia dependiendo del microcontrolador 

#build(reset=0x02000,interrupt=0x02008)      // Asigna los vectores de reset e interrupción para la versión con bootloader

#org 0x0000,0x1FFF {}                                  // Reserva espacio en memoria para el bootloader

#define LED PIN_A1                                       //Pin donde está conectado el LED de X-TRAINER
char TECLA_PRESS; 

////CONFIGURACION DE PINES TECLADO

#define row0 PIN_B0           //Filas del teclado colocar resistecia pullup
#define row1 PIN_B1          //Filas del teclado colocar resistecia pullup
#define row2 PIN_B2         //Filas del teclado colocar resistecia pullup
#define row3 PIN_B3        //Filas del teclado colocar resistecia pullup
#define col0 PIN_B4       //Columnas del teclado
#define col1 PIN_B5
#define col2 PIN_B6
#define col3 PIN_B7

#include "Teclado4x4.h"                                     //LIBRERIA DE TECLADO

 

void main()

{
       
           kbd_init ();                                                    //inicialización del teclado.
           

            while(TRUE)
   {
      TECLA_PRESS = kbd_getc () ;  
      
      if (TECLA_PRESS == '1')
      {
         output_HIGH (LED); //Cambio de estado en el pin RA1
      }

      
      if (TECLA_PRESS == '0')
      {
         output_LOW (LED);
      }
   }
}

