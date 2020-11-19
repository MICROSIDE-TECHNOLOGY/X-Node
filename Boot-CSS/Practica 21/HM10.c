/*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Esta pr�ctica consiste en realizar el envio de datos por medio de un m�dulo 
Bluetooth, usando el protocolo de comunicaci�n serial UART, para enviar un 
comando simple para prender y apagar un LED incluido en la tarjeta X-TRAINER,
y un segundo comando para preguntar el estado de un bot�n.
**************************************************************************/
 
#include  <18F45K50.h>                          // Para PIC18F4550 cambiar por: #include <18F4550.h>
#use delay(internal=48MHz)                    // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)      // Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000,0x1FFF {}                       // Reserva espacio en memoria para el bootloader 
//-------------------------------------------------------------------------------
#USE RS232(stream=SERIE, BAUD=9600, PARITY=N, XMIT=PIN_C6, RCV=PIN_C7,BITS=8)
#define LED pin_A1
#define Boton pin_A2

void main(void)
{

while(!kbhit()) //Pregunta si hay algun dato recibido
while (TRUE)
 {
        
       
       
       char Caracter = getc (); //Guarda el caracter
       if (Caracter == '0')
       {
          output_low (LED); //Apaga el LED
           fprintf(SERIE,"LED APAGADO\r\n");
       }

       else if (Caracter == '1')
       {
          output_HIGH (LED); //Enciende el LED
           fprintf(SERIE,"LED ENCENDIDO\r\n");
       }

       
       else if (Caracter == '?')
       {
          
          if (1 == input (Boton))
          {
             //Pregunta el estado del bot�n
             Printf ("1"); //Env�a un 0 si el bot�n no est� presionado
          }

          else
          {
             Printf ("0"); //Env�a un 1 si el bot�n est� presionado
          }

       }
       
  } 
}

