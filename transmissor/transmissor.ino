#include <SPI.h>
#include <nRF24L01.h>               
#include <RF24.h>               //biblioteca necessária para usar o módulo RF24L01. Facilmente encontrada na internet.


#define JOYSTICK1_EIXOX A0      //dados analógicos
#define JOYSTICK1_EIXOY A1
#define JOYSTICK2_EIXOX A2        
#define JOYSTICK2_EIXOY A3      
#define JOYSTICK1_BUTTON 7      //dados booleanos   
#define JOYSTICK2_BUTTON 6  


RF24 radio(9, 8); // CE, CSN              
const byte address[6] = "00001";            //canal de operação

struct Dado{                      //É cabível enviar todos os valores lidos como um tipo abstrado de dado.
  int joystick1X;
  int joystick1Y;
  int joystick2X;
  int joystick2Y;
  bool buttonJ1;
  bool buttonJ2;
};

Dado dado;                      //instância da variável do tipo Dado.

void setup() {
  radio.begin();
  radio.setAutoAck(false);                      //desabilita a confirmação do recebimento da informação.
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(JOYSTICK1_BUTTON, INPUT_PULLUP);
  pinMode(JOYSTICK2_BUTTON, INPUT_PULLUP);
}
void loop() {
  dado.joystick1X = analogRead(JOYSTICK1_EIXOX);            //Grava os dados lidos em seus respectivos campos na variavel dado
  dado.joystick1Y = analogRead(JOYSTICK1_EIXOY);
  dado.joystick2X = analogRead(JOYSTICK2_EIXOX);
  dado.joystick2Y = analogRead(JOYSTICK2_EIXOY);
  dado.buttonJ1 = !digitalRead(JOYSTICK1_BUTTON);
  dado.buttonJ2 = !digitalRead(JOYSTICK2_BUTTON);

  radio.write(&dado, sizeof(Dado));                  //manda de uma vez só
  delay(20);
}
