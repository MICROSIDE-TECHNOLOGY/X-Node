
/*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Esta pr�ctica consiste en realizar la medici�n de temperatura por medio de un 
sensor LM35 e imprimir la lectura en una pantalla LCD
**************************************************************************/

#include  <18F45K50.h>                         // Para PIC18F4550 cambiar por: #include <18F4550.h>
#device ADC=10                                  // Configura el ADC a 10 bits
#use delay(internal=48MHz)                     // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)        // Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000,0x1FFF {}                          // Reserva espacio en memoria para el bootloader 

//-------------------------------------------------------------------------------
//CONFIGURACION DE PINES LCD
#define LCD_RS PIN_B0      //CONTROL del LCD
#define LCD_RW PIN_B1
#define LCD_E  PIN_B2
#define LCD_DB4 PIN_B3    //DATOS del LCD (4 lineas)
#define LCD_DB5 PIN_B4
#define LCD_DB6 PIN_B5
#define LCD_DB7 PIN_B6

//=============================
#include "flex_lcd.h"     //LIBRERIA LCD

float temperatura;      //variable
void main(void)
{
   lcd_init (); // comandos de inicializaci�n del lcd.
   delay_ms (50) ;
   setup_adc_ports (sAN3);    //configuracion indiuvidual deL canal ADC en A0
   setup_adc (ADC_CLOCK_INTERNAL);
   
   //----------------------------rutina principal ----------------------------
   while (1)
   {
   set_adc_channel( 3 );                  //conversion analogica por canal 0
   delay_ms(100);                        //tiempo de espera para conversion de ADC
   temperatura = read_adc();            //lee voltaje analogico en puerto A0
   temperatura = temperatura*0.488;    //5.00volts*temperatura * (100.00/1023.00)=0.488                        
   printf(lcd_putc,"\fTemperatura  \n%3.1fC", temperatura);
    delay_ms(100); 
   
   }
}

