/*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Implementar comunicaci�n USB (CDC) para enviar un comando simple para prender y
apagar un LED incluido en la tarjeta X-TRAINER, y un segundo comando para
preguntar el estado de un bot�n.
**************************************************************************/

#include  <18F45K50.h>                           // Para PIC18F4550 cambiar por: #include <18F4550.h>
#use delay(internal=48MHz)                     // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)       // Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000,0x1FFF {}                        // Reserva espacio en memoria para el bootloader 
//-------------------------------------------------------------------------------
#include <usb_cdc.h>
#define LED PIN_A1        //Pin donde est� conectado el LED de X-TRAINER
#define Boton PIN_A2        //Pin donde est� conectado el LED de X-TRAINER

void main(void)
{
  set_tris_a(0b11111111);
  set_tris_b(0b11111100);                  //Configura puerto B (1= entrada  0= salida )
  setup_adc_ports(sAN0);                  // configura canal_0 ADC
  setup_adc( ADC_CLOCK_INTERNAL );       //asigna oscilador interno al ADC
  usb_cdc_init();                       // Configuramos al puerto virtual.
  usb_init();                          // Inicializamos el stack USB.
 while(!usb_cdc_connected()) {}       // espera a detectar una transmisi�n de la PC (Set_Line_Coding)
                              

do{


     usb_task();
  if(usb_enumerated())
   {
   char Caracter =usb_cdc_getc(); //Guarda el caracter
       
       if (Caracter == '0')
       {
          output_low (LED); //Apaga el LED
          printf(usb_cdc_putc,"LED apagado\n"); //Env�a un 0 si el bot�n no est� presionado
       }

       else if (Caracter == '1')
       {
          output_HIGH (LED); //Enciende el LED
          printf(usb_cdc_putc,"LED encendido\n"); //Env�a un 0 si el bot�n no est� presionado
       }

       
       else if (Caracter == '?')
       {
          
          if (1 == input (Boton))
          {
             //Pregunta el estado del bot�n
             printf(usb_cdc_putc,"1\n"); //Env�a un 0 si el bot�n no est� presionado
          }

          else
          {
               printf(usb_cdc_putc,"0\n"); //Env�a un 0 si el bot�n no est� presionado
          }

       }
   
   }                           
  }while (TRUE); // bucle infinito.
}

