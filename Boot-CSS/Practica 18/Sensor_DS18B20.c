/*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Esta pr�ctica consiste en realizar la medici�n de temperatura por medio de un 
sensor LM35 e imprimir la lectura en una pantalla LCD
**************************************************************************/

#include  <18F45K50.h>                         // Para PIC18F4550 cambiar por: #include <18F4550.h>
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
#define DS1820_PIN  PIN_A0                  //Se define pin como entrada digital para leer datos del sensor DS18B20
#define ONE_WIRE_PIN DS1820_PIN            
//=============================
#include<1wire.c>                        //Se eincluyen las librerias correspondientes para el manejo del protocolo 1WIRE
#include<ds1820.c>                      //Se incluyela librer�a del driver para el manejo del sensor DS18B20
#include "flex_lcd.h"                 //LIBRERIA LCD

float temperatura;      //Variable

void main(void)
{
  port_b_pullups(0xff);
  lcd_init();      // Comandos de inicializaci�n del lcd.
  delay_ms(50);                       // Inicializamos el stack USB.
                          
//----------------------------Rutina principal ----------------------------
while (TRUE)
 {
   temperatura = ds1820_read();                              //Lee el sensor                       
   printf(lcd_putc,"\fTemperatura  \n%3.1fC", temperatura); //Imprime en display
    delay_ms(1000);             
  } 
}

