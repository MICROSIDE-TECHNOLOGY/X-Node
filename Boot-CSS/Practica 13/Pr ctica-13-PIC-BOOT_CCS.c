 /*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Esta pr�ctica consiste en variar la velocidad de un motor usando el m�dulo
PWM.
**************************************************************************/

#include  <18F45K50.h>                          //Para PIC18F4550 cambiar por: #include <18F4550.h>
#use delay(internal=48MHz)                    // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)      // Asigna los vectores de reset e interrupci�n para la versi�n con bootloader
#org 0x0000,0x1FFF {}                       // Reserva espacio en memoria para el bootloader 

//-------------------------------------------------------------------------------
#define IN_1 pin_C0
#define IN_2 pin_C1

int16 VELOCIDAD=0;                     //Variable para ajustar el valor del PWM1 en CCP1 

int1 SUBE=1;  //Variable para control de ascenso y descenso del valor del PWM


void main()
{
   setup_timer_2 (T2_DIV_BY_16, 255, 1);      //Configura Timer2, periodo ajustado a 342uS
   setup_ccp1 (CCP_PWM|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L); //Configura el m�dulo CCP para uso del PWM
   while (TRUE)
   {
      output_bit (IN_1, 1);     //Direcci�n del motor
      output_bit (IN_2, 0) ;
      SUBE = 1;

      while (VELOCIDAD < 1020&&SUBE)
      {
         //Se va incrementando del valor en el PWM hasta el m�ximo
         VELOCIDAD += 5;      //Se incrementa en pasos de 15 el ciclo de trabajo
         set_pwm1_duty (VELOCIDAD);  //Salida Pin_C2
         delay_ms (40);     //Cada 40 mili segundo
      }

      SUBE = 0;
      
      while (VELOCIDAD > 5&& ! SUBE)
      {
         //Se va reduciendo el valor en el PWM hasta el m�nimo
         VELOCIDAD -= 5;    //Se reduce en pasos de 15 el ciclo de trabajo
         set_pwm1_duty (VELOCIDAD); //Salida Pin_C2
         delay_ms (40) ;
      }

      SUBE = 1;
      output_bit (IN_1, 0);     //Alto del motor
      output_bit (IN_2, 0);
      delay_ms (1000) ;
      
      output_bit (IN_1, 0);     //Direcci�n del motor
      output_bit (IN_2, 1) ;
      SUBE = 1;

      while (VELOCIDAD < 1020&&SUBE)
      {
         //Se va incrementando del valor en el PWM hasta el m�ximo
         VELOCIDAD += 5;      //Se incrementa en pasos de 15 el ciclo de trabajo
         set_pwm1_duty (VELOCIDAD);  //Salida Pin_C2
         delay_ms (40);     //Cada 40 mili segundo
      }

      SUBE = 0;
      
      while (VELOCIDAD > 5&& ! SUBE)
      {
         //Se va reduciendo el valor en el PWM hasta el m�nimo
         VELOCIDAD -= 5;    //Se reduce en pasos de 15 el ciclo de trabajo
         set_pwm1_duty (VELOCIDAD); //Salida Pin_C2
         delay_ms (40) ;
      }

      SUBE = 1;
      output_bit (IN_1, 0);     //Alto del motor
      output_bit (IN_2, 0);
      
      delay_ms (500) ;
   }
}

