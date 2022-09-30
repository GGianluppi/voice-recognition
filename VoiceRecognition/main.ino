#include <SoftwareSerial.h>
//#include "VoiceRecognitionV3.h"

VR myVR(2,3);    // 2:RX 3:TX (Arduino)

uint8_t records[7]; // Save record
uint8_t buf[64];

int Arduino = 13;   // Blue LED
int Ligar = 12;     // (Turn on) - Green LED
int Desligar = 6;   // (Turn Off) - Red LED
int Lampada = 10;   // (Lamp) - Yellow LED
int Ventilador = 9; // (Fun) - White LED

unsigned long tempo_limite; // Max time
unsigned long tempo_espera; // Wait time

// Variables to store the recognized command state

boolean comando_Arduino = false;
boolean comando_Ligar = false;
boolean comando_Desligar = false;
boolean comando_Lampada = false;
boolean comando_Ventilador = false;


#define Arduino (0)  

#define Ligar (1) 
#define Desligar (2)

#define Lampada (3) 
#define Ventilador (4) 

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/*
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("=========================");
  Serial.println("   VOICE RECOGNITION");
  Serial.println("=========================");

  // Declare all pins as output for LEDs
  pinMode(Arduino, OUTPUT);
  pinMode(Ligar, OUTPUT);
  pinMode(Desligar, OUTPUT);
  pinMode(Lampada, OUTPUT);
  pinMode(Ventilador, OUTPUT);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }

  //Load all commands in VR3
  if(myVR.load((uint8_t)Arduino) >= 0){
    Serial.println("onRecord loaded");
  }
  
  if(myVR.load((uint8_t)Desligar) >= 0){
    Serial.println("offRecord loaded");
  }

  if(myVR.load((uint8_t)Ligar) >= 0){
    Serial.println("onRecord loaded");
  }
  
  if(myVR.load((uint8_t)Lampada) >= 0){
    Serial.println("onRecord loaded");
  }
  
  if(myVR.load((uint8_t)Ventilador) >= 0){
    Serial.println("onRecord loaded");
  }
  
}

void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  
  if(ret>0){
    switch(buf[1]){
     // Check if the Arduino command to start the system is recognized
      case Arduino:
            // Check if the system is already started
            if(comando_Arduino==false){
            comando_Arduino = true;
            tempo_limite = millis();
            Serial.println("Hello! What do you want?"); 
            digitalWrite(Arduino, HIGH);               
           }
           
           else{
            Serial.println("I am waiting...");
           }
        
      break;
      
      case Ligar: // Turn on
           if(comando_Arduino==true){
              comando_Ligar = true;
              comando_Desligar = false;
              Serial.println("What do you want to turn on?");
              digitalWrite(Ligar, HIGH);
              digitalWrite(Desligar, LOW);                
           }
           
      break;

      case Desligar: // Turn off
           if(comando_Arduino==true){
              comando_Ligar = false;
              comando_Desligar = true;
              Serial.println("What do you want to turn off?");
              digitalWrite(Ligar, LOW);
              digitalWrite(Desligar, HIGH);                  
           }

      break;

      case Lampada:
      
      if(comando_Ligar==true){
              if(digitalRead(Lampada)==HIGH){
                Serial.println("The lamp is already on");
              }
              else{
              Serial.println("Turn on lamp");  

              } 
              
              digitalWrite(Lampada, HIGH); 
              comando_Arduino = false;
              comando_Ligar = false;
              comando_Desligar = false;
              
              digitalWrite(Ligar, LOW);
              digitalWrite(Desligar, LOW);
              digitalWrite(Arduino, LOW);              
           }
      
      if(comando_Desligar==true){
              if(digitalRead(Lampada)==LOW){
                Serial.println("The lamp is already off");
              }
              else{
               Serial.println("Turn off lamp"); 
              }
              
              digitalWrite(Lampada, LOW); 
              comando_Arduino = false;
              comando_Ligar = false;
              comando_Desligar = false;  
              
              digitalWrite(Ligar, LOW);
              digitalWrite(Desligar, LOW);
              digitalWrite(Arduino, LOW);                  
           }
             
      break;

      case Ventilador:// Fan
      if(comando_Ligar==true){
              if(digitalRead(Ventilador)==HIGH){
                Serial.println("The Fan is already on");
              }
              else{
                Serial.println("Turn on Fan"); 
              } 
              
              digitalWrite(Ventilador, HIGH); 
              comando_Arduino = false;
              comando_Ligar = false;
              comando_Desligar = false;  
              
              digitalWrite(Ligar, LOW);
              digitalWrite(Desligar, LOW);
              digitalWrite(Arduino, LOW);
                     
           }
      
      if(comando_Desligar==true){
              if(digitalRead(Ventilador)==LOW){
                Serial.println("The Fan is already off");
              }
              else{
                Serial.println("Turn off Fan"); 
              }
              
              digitalWrite(Ventilador, LOW); 
              comando_Arduino = false;
              comando_Ligar = false;
              comando_Desligar = false;  
              
              digitalWrite(Ligar, LOW);
              digitalWrite(Desligar, LOW);
              digitalWrite(Arduino, LOW);                  
           }
           
      break;
      default:
        Serial.println("Record function undefined");
        break;
    }
    // Voice recognized (buf  -->  VR module return value when voice is recognized.)
    printVR(buf);
  }

// Calculate the waiting time when there is no voice command after turning on Arduino (Blue LED)
if(comando_Arduino==true){
      tempo_espera = millis() - tempo_limite;
      if(tempo_espera > 10000){ // 10 seconds
        Serial.println("Time is up!");
        comando_Arduino = false;
        comando_Ligar = false;
        comando_Desligar = false;
        digitalWrite(Arduino, LOW);
        digitalWrite(Ligar, LOW);
        digitalWrite(Desligar, LOW);
      }
  }

}
