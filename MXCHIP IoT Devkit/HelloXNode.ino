#include "AZ3166WiFi.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"
#include "config.h"
#include "utility.h"

UARTClass Serial1(UART_1);
int resultado; 
int a;


void setup()
{
  Screen.init();
  Screen.print(0,"XNODE");
  Screen.print(1,"by Microside");

  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop()
{
  Serial1.write ("XNODE1A+G");
  String val; 

  while (Serial1.available() > 0 ){

    char byte = Serial1.read(); 
    val += byte;

  }

  char line1 [200];
  char a2 [100];
  
  val.toCharArray(a2,val.length());
  sprintf(line1,"\t %s",a2);
  Screen.print(2,"Respuesta X-NODE");
  Screen.print(3,line1);
  delay (1000);
}
