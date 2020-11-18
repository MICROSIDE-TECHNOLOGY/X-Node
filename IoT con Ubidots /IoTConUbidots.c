/*
AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
FECHA: NOVIEMBRE 2020
*/

/*
---------------------------------------------------------------------------
En esta practica se implementa la comunicacion con la 
plataforma Ubidots mediante la conexion a internet que proporciona el X-NODE 
MCU WIFI ESP8266,  de este modo es  posible visualizar una  lectura de 
luminosidad con el X-NODE Ambient Light, asi como la medicion de temperatura 
y humedad con el X-NODE Temp & Hum.
---------------------------------------------------------------------------
*/

#include <18F45K50.h>                         // Para PIC18F4550 cambiar por: #include <18F4550.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#use delay(internal=48MHz)                     // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)        // Asigna los vectores de reset e interrupcion para la version con bootloader
#org 0x0000,0x1FFF {}                          // Reserva espacio en memoria para el bootloader 
#use rs232(baud=115200, xmit=PIN_C6, rcv=PIN_C7,STREAM=UART )   //Configuracion del puerto UART
#define LED PIN_A1

char Node03[]="XB003A";    //ID del X-node
char Node09[]="XB009A";    //ID del X-node
char Node03GetTemp[]="+GT\r\n";  // Comando para solicitar el dato de temperatura
char Node03GetHum[]="+GH\r\n";   // Comando para solicitar el dato de humedad
char Node09GetLum[]="+G\r\n";    // Comando para solicitar el dato de Luminosidad
char SSID[]="XXXXXXXXX";        //Sustituir por el nombre de tu red WiFi
char PASS[]="XXXXXXXXX";     //Sustituir por la clave de tu red WiFi
char CommandUBI[]="XB016A+OU=";  //Comando para configurar la conexion con Ubidots

char Token[]="BBFF-AkKMkWNQ32JyzXYY8M7OupTDsusZFv"; //Sustituye por tu token de Ubidots 
char DevieAPI[]="test";       //Nombre del dispositivo (debe coincidir con el de Ubidots)
char VariableAPILed[]="led";  //Nombre de la variable para la humedad (debe coincidir con Ubidots)
char VariableAPIHum[]="hum";  //Nombre de la variable para la humedad (debe coincidir con Ubidots)
char VariableAPITemp[]="temp";//Nombre de la variable para la temperatura (debe coincidir con Ubidots)
char VariableAPILum[]="lum";  //Nombre de la variable para la luminosidad (debe coincidir con Ubidots)

void waitOk(void);                                 //Funcion para esperar confirmacion del X-NODE
float ReadFloat(char* resp);                       //Procesa la cadena que responde el X-NODE
float ReadFloatFromNode(char* node, char* com);    //Envia el comando para la lectura de sensores 
void ConfigureAP(void);                            //Configura el X-NODE MCU WIFI
void SendUbi(float Value, char* VariableAPI);      //Funcion para enviar informacion a Ubidots 
char waitBool(void);                               //Funcion para esperar informacion del X-NODE
char ReadUbiBool(char* VariableAPI);               //Funcion para enviar informacion a Ubidots 


void main (void){
   delay_ms(3000);  
   int cause = Restart_Cause();     //Comprueba que no exista una fuente de reinicio
   if (cause != 0)
      reset_cpu();                  //Reinicia el sistema en caso de existir una fuente de reincio
   ConfigureAP();                   //Envia las credenciales para conectarse a la red WIFI
   while(1){
      delay_ms(10000);              //Tiempo de espera entre adquiscion y transmicion de datos
      float T = ReadFloatFromNode(Node03,Node03GetTemp); //Guarda la lectura de temperatura al X-NODE
      float H = ReadFloatFromNode(Node03,Node03GetHum);  //Guarda la lectura de humedad al X-NODE
      float L = ReadFloatFromNode(Node09,Node09GetLum);  //Guarda la lectura de luminosidad al X-NODE
      SendUbi(T,VariableAPITemp);      //Envia los datos a Ubidots 
      SendUbi(H,VariableAPIHum);       //Envia los datos a Ubidots
      SendUbi(L,VariableAPILum);       //Envia los datos a Ubidots
      char dataRead=ReadUbiBool(VariableAPILed);
      if (dataRead=='1')
         output_HIGH(LED);
      else
         output_LOW(LED);
   }
}
 
/**************************************************************************
Funcion para esperar confirmacion del X-NODE
Procesa los datos recibidos en el puerto serial, los compara con la cadena
"OK"
**************************************************************************/
void waitOk(void){
   char wait[] = "OK";
   int cont=2;
   int sum = 0;
   while(1){
      char c = getch();
      sum = (c == wait[sum])? sum+1:0;
      if (cont==sum)
         break;
   }
}


/**************************************************************************
Funcion para esperar confirmacion del UBIDOTS
Procesa los datos recibidos en el puerto serial, los compara con la cadena
"OK|" seguido del valor recibido
**************************************************************************/
char waitBool(void){
   char wait[] = "OK|";
   int cont=3;
   int sum = 0;
   while(1){
      char c = getch();
      sum = (c == wait[sum])? sum+1:0;
      if (cont==sum)
         return getch();
   }
}

/**************************************************************************
Funcion para procesar la cadena que responde el X-NODE
Procesa los datos recibidos en el puerto serial; obtiene el valor numerico en
la respuesta del XNODE.
**************************************************************************/
float ReadFloat(char* resp){
   int cont=6;
   int sum = 0;
   while(1){
      char c = getch();
      sum = (c == resp[sum])? sum+1:0;
      if (cont==sum && '=' == getch()){
         char RecBuff[10];
         int ContBuff=0;
         while(1){
            c=getch();
            if (c== '\n' ||c== '\r'){
               RecBuff[ContBuff]='\0';
               return strtod(RecBuff,NULL);
            } else
               RecBuff[ContBuff++] = c;
         }
      }
   }
}

/**************************************************************************
Funcion para enviar los comandos para la lectura de sensores
Envia el ID del x-node y el comando mediante comunicacion serial, retorna el
valor regresado por la funcion ReadFloat.
**************************************************************************/
float ReadFloatFromNode(char* node, char* com){
   delay_ms(100);
   printf(node);
   printf(com);
   return ReadFloat(Node);
}

/**************************************************************************
Funcion para configurar el X-NODE MCU WIFI
Transmite al nodo X-NODE MCU WIFI el SSID y la contrasena de la red WIFI para
que se pueda conectar, espera la confirmacion del X-NODE
**************************************************************************/
void ConfigureAP(void){
   delay_ms(100);
   while(kbhit())
      char c = getch();
   printf("XB016A+CA=%s,%s\r\n",SSID,PASS); //Asigna el nombre y contrasena de la red al X-NODE
   waitOk();                                //Espera la confirmacion del X-NODE
}

/**************************************************************************
Funcion para enviar informacion a Ubidots
Envia el comando al  X-NODE MCU WIFI con la informacion a enviar a ubidots
El formato de la trama enviada es:
Comando para el X-NODE + PIC + POST + TOKEN + Nombre del dispositivo + Nombre de la varaible + Valor
**************************************************************************/
void SendUbi(float Value, char* VariableAPI){
   while(kbhit())
      char c = getch();
   delay_ms(100);
   printf("%sPIC|POST|%s|%s=>%s:%f|end\r\n",CommandUBI,Token,DevieAPI,VariableAPI,Value);
   waitOk();
}

/**************************************************************************
Funcion para recibir informacion de Ubidots
Envia el comando al  X-NODE MCU WIFI con la informacion a recibir de ubidots
El formato de la trama enviada es:
Comando para el X-NODE + PIC + POST + TOKEN + Nombre del dispositivo + Nombre de la varaible
**************************************************************************/
char ReadUbiBool(char* VariableAPI){
   while(kbhit())
      char c = getch();
   delay_ms(100);
   //sem|LV|BBFF-EULAbu0R9UUIpNnUy4Bv5HM6OThgBw|semaforodemo:panicolamp|end
   printf("%sPIC|LV|%s|%s:%s|end\r\n",CommandUBI,Token,DevieAPI,VariableAPI);
   return waitBool();
}



