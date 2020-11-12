/*
AUTOR: MICROSIDE TECHNOLOGY S.A. DE C.V.
FECHA: NOVIEMBRE 2020
*/

/**************************************************************************
En esta práctica se implementa la comunicación con la 
plataforma Ubidots mediante la conexión a internet que proporciona el X-NODE 
MCU WIFI ESP8266,  de este modo es  posible visualizar una  lectura de 
luminosidad con el X-NODE Ambient Light, así como la medición de temperatura 
y humedad con el X-NODE Temp & Hum.
**************************************************************************/

#include  <18F45K50.h>                         // Para PIC18F4550 cambiar por: #include <18F4550.h>
#use delay(internal=48MHz)                     // Tipo de oscilador y frecuencia dependiendo del microcontrolador 
#build(reset=0x02000,interrupt=0x02008)        // Asigna los vectores de reset e interrupción para la versión con bootloader
#org 0x0000,0x1FFF {}                          // Reserva espacio en memoria para el bootloader 
#use rs232(baud=115200, xmit=PIN_C6, rcv=PIN_C7,STREAM=UART )   //Configuración del puerto UART

char Node03[]="XB003A";    //ID del X-node
char Node09[]="XB009A";    //ID del X-node
char Node03GetTemp[]="+GT\r\n";  // Comando para solicitar el dato de temperatura
char Node03GetHum[]="+GH\r\n";   // Comando para solicitar el dato de humedad
char Node09GetLum[]="+G\r\n";    // Comando para solicitar el dato de Luminosidad
char SSID[]="IZZI-E4AXX";        //Sustituir por el nombre de tu red WiFi
char PASS[]="FCAE34B9E4AXX";     //Sustituir por la clave de tu red WiFi
char CommandUBI[]="XB016A+OU=";  //Comando para configurar la conexión con Ubidots

char Token[]="BBFF-AkKMkWNQ7OupTDsusZxv"; //Sustituye por tu token de Ubidots 
char DevieAPI[]="test";       //Nombre del dispositivo (debe coincidir con el de Ubidots)
char VariableAPIHum[]="hum";  //Nombre de la variable para la humedad (debe coincidir con Ubidots)
char VariableAPITemp[]="temp";//Nombre de la variable para la temperatura (debe coincidir con Ubidots)
char VariableAPILum[]="lum";  //Nombre de la variable para la luminosidad (debe coincidir con Ubidots)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void waitOk(void);                                 //Función para esperar confirmación del X-NODE
float ReadFloat(char* resp);                       //Procesa la cadena que responde el X-NODE
float ReadFloatFromNode(char* node, char* com);    //Envia el comando para la lectura de sensores 
void ConfigureAP(void);                            //Configura el X-NODE MCU WIFI
void SendUbi(float Value, char* VariableAPI);      //Función para enviar información a Ubidots 

void main (void){
   delay_ms(3000);  
   int cause = Restart_Cause();     //Comprueba que no exista una fuente de reinicio
   if (cause != 0)
      reset_cpu();                  //Reinicia el sistema en caso de existir una fuente de reincio
   ConfigureAP();                   //Envia las credenciales para conectarse a la red WIFI
   while(1){
      delay_ms(10000);              //Tiempo de espera entre adquisción y transmición de datos
      float T = ReadFloatFromNode(Node03,Node03GetTemp); //Guarda la lectura de temperatura al X-NODE
      float H = ReadFloatFromNode(Node03,Node03GetHum);  //Guarda la lectura de humedad al X-NODE
      float L = ReadFloatFromNode(Node09,Node09GetLum);  //Guarda la lectura de luminosidad al X-NODE
      SendUbi(T,VariableAPITemp);      //Envía los datos a Ubidots 
      SendUbi(H,VariableAPIHum);       //Envía los datos a Ubidots
      SendUbi(L,VariableAPILum);       //Envía los datos a Ubidots
   }
}
 
/**************************************************************************
Función para esperar confirmación del X-NODE
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
Función para procesar la cadena que responde el X-NODE
Procesa los datos recibidos en el puerto serial; obtiene el valor númerico en
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
Envia el ID del x-node y el comando mediante comunicación serial, retorna el
valor regresado por la función ReadFloat.
**************************************************************************/
float ReadFloatFromNode(char* node, char* com){
   delay_ms(100);
   printf(node);
   printf(com);
   return ReadFloat(Node);
}

/**************************************************************************
Función para configurar el X-NODE MCU WIFI
Transmite al nodo X-NODE MCU WIFI el SSID y la contraseña de la red WIFI para
que se pueda conectar, espera la confirmación del X-NODE
**************************************************************************/
void ConfigureAP(void){
   delay_ms(100);
   while(kbhit())
      char c = getch();
   printf("XB016A+CA=%s,%s\r\n",SSID,PASS); //Asigna el nombre y contraseña de la red al X-NODE
   waitOk();                                //Espera la confirmación del X-NODE
}

/**************************************************************************
Función para enviar información a Ubidots
Envia el comando al  X-NODE MCU WIFI con la información a enviar a ubidots
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



