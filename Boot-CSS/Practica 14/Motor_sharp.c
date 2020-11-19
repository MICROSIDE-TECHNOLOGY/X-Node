 /*
  AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
  FECHA: JUNIO 2019
*/
/**************************************************************************
Esta práctica consiste en variar la velocidad de un motor por medio de un sensor 
SHARP usando los modulos PWM y ADC.
**************************************************************************/

#include  <18F45K50.h>                          // Para PIC18F4550 cambiar por: #include <18F4550.h>
#device ADC=8                                  // Configura el ADC a 8 bits
#use delay(internal=48MHz)                    // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)      // Asigna los vectores de reset e interrupción para la versión con bootloader
#org 0x0000,0x1FFF {}                       // Reserva espacio en memoria para el bootloader 

//-------------------------------------------------------------------------------
int VALOR_ADC;                              //Variable para almacenar el valor leído del ADC 
void SisInit()
{
   setup_timer_2 (T2_DIV_BY_16, 254, 16);      //Configura Timer2
   setup_ccp1 (CCP_PWM|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L); //Configura el módulo CCP para uso del PWM
   setup_adc_ports (sAN3);        //Configura solo el puerto A3 como entrada analógica
   setup_adc (ADC_CLOCK_INTERNAL);
}

void main(void)
{
  SisInit();
  
    while (1)
   {
      set_adc_channel (3);     //Selecciona el canal 3 para la conversión
      VALOR_ADC = read_adc ()*1.53;    //Lee el valor del ADC y lo guarda en la variable
      set_pwm1_duty (VALOR_ADC);   //Salida Pin_C2
   } 
}

