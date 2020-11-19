/*
 AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
 FECHA: NOVIEMBRE DE 2020
*/
#include "18f45K50.h" //Para PIC18F4550 cambiar por: #include <18F4550.h>
#use delay(internal=48000000) // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#use rs232(baud=115200, xmit=PIN_C6, rcv=PIN_C7, stream=UART)   //Comunicacion serial a 115200bps, 1 bit de paro, sin paridad
#zero_ram
#build(reset=0x02000,interrupt=0x02008) // Asigna los vectores de reset e interrupcion para la version con bootloader
#org 0x0000,0x1FFF {} // Reserva espacio en memoria para el bootloader 

//--------------------------------------------------------------------------------------------------------------------

#include <usb_cdc.h> //Libreria USB
#include <usb_desc_cdc.h> //Libreria USB

char c,u; //Crea variables tipo char para guardar los datos

void main() {

usb_cdc_init(); // Configuramos al puerto virtual
usb_init(); //inicializamos el USB

      while (!usb_cdc_connected()) {} // espera a detectar una transmision de la PC
      while (true)
      {
         usb_task();
         if(usb_enumerated()) // Espera a que el dispositivo sea enumerado
         {
            if (usb_cdc_kbhit())
            {
               c = usb_cdc_getc(); //Espera a recibir un datos por el puerto USB
               putc(c,UART); //Envia la informacion por UART
            }

            if (kbhit(UART))
            {
               u=getc(UART); //Recibe informacion por UART
               usb_cdc_putc(u); //Envia informacion hacia la computadora por puerto emulado USB
            }
         }
      }
   }



