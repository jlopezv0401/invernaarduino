#include <SPI.h>
#include <Ethernet.h>
#include <MsTimer2.h>

char val;
byte val2;
// network configuration.  gateway and subnet are optional.
int temperatura,valor;
float resultado;
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0xEE, 0xEB};
IPAddress ip(192,168,40, 47);


IPAddress subnet(255,255,255, 0);
IPAddress gateway(198,168,40, 254);

// telnet defaults to port 23
EthernetServer server = EthernetServer(9999);

void envioSensor() {
  
   valor=analogRead(0); 
  
   resultado = (5.0 * valor * 100.0)/1024;
   server.write((byte)resultado);
   Serial.println(resultado);
   
}

void receiverServer(){
  EthernetClient client = server.available();
  if (client == true) {
    //val=client.read();
    val2=client.read();
    Serial.println(val2);
    //Para el ventilador
    switch (val2){
      case 0:
       delay(10);
       if(val2==0){
          digitalWrite(2,HIGH);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
       }
       break;
       
      case 1:
       delay(10);
       if(val2==1){
          digitalWrite(2,LOW);
          digitalWrite(3,HIGH);
          digitalWrite(4,LOW);
       } 
       break;   
       
      case 2:
       delay(10);
       if(val2==2){
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,LOW);
       }
       break;
       
      case 3:
       delay(10);
       if(val2==3){
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,HIGH);
       }
       break;
       
      case 4:
       delay(10);
       if(val2==4){
          digitalWrite(2,HIGH);
          digitalWrite(3,LOW);
          digitalWrite(4,HIGH);
       }
       break;
      
      case 5:
       delay(10);
       if(val2==5){
          digitalWrite(2,LOW);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
       }
       break;
       
      case 6:
       delay(10);
       if(val2==6){
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
       }
       break;
       
      case 7:
       delay(10);
       if(val2==7){
          digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
       }
       break;
        
    }
    
  }
}



void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
  Serial.print("SETUP");
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);  
  pinMode(4, OUTPUT);   
}

void loop()
{
  envioSensor();
  delay(2);
  receiverServer();
  delay(2);
}

