
/*
AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
FECHA: JUNIO 2019
*/
/**************************************************************************
Implementar un contador binario que incrementar� cada vez que se presione un bot�n,
este ser� configurado como entrada digital. Para visualizar el conteo se utilizan 8 LEDs.
**************************************************************************/
#include <18F45K50.h>                    //Para PIC18F4550 cambiar por: #include <18F4550.h>
#use delay(internal=48MHz)              //Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)//Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000,0x1FFF {}                 //Reserva espacio en memoria para el bootloader
#define Boton PIN_A2                //Asigna el pin A2 al boton BOOT del X-TRAINER

byte cont =0;

 void SisInit (void)
 {

    set_tris_b (0b00000000); //Configura todo el PUERTO B como salida
    set_tris_a (0b11111111); //Configura todo el PUERTO A como entrada
 }


                      
void main(void)
{
  SisInit ();
   
   while (1) //Mientras sea verdadero se ejecuta el siguiente c�digo
   {
      if (!input (Boton)) //Pregunta el estado del boton mediante una comparaci�n
      {
         cont++; //Se incrementa el contador
         output_b (cont); //Se asigna el valor de cont al puerto B y se despliega el valor
         Delay_ms (5); //Retardo
         while (!input (Boton)); //Mientras el bot�n se mantenga igual a cero
         Delay_ms (5);  //Retardo
      }
   }
}

