#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define MOTOR1RD 48 // MOTOR 1 ROTACAO DIREITA
#define MOTOR1RE 49 //MOTOR 1 ROTACAO ESQUERDA
#define MOTOR2RD 46
#define MOTOR2RE 47

#define VELM1 7
#define VELM2 6

#define VELMOTORBASE 8
#define MOTORBASEROTDIR 44
#define MOTORBASEROTESQ 45

#define SERVOGARRA 9
#define SERVOMEIO 11
#define SERVOROTACIONAGARRA 10
#define SERVOBASE 12

Servo servoGarra;
Servo servoBase;
Servo rotacionaGarra;
Servo meio;

RF24 radio(4, 5); // CE, CSN
const byte address[6] = "00001";

struct Dado{
  int joystick1X;
  int joystick1Y;
  int joystick2X;
  int joystick2Y;
  bool buttonJ1;
  bool buttonJ2;
};

Dado dadosRecebidos;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(MOTOR1RD, OUTPUT);
  pinMode(MOTOR1RE, OUTPUT);
  pinMode(MOTOR2RD, OUTPUT);
  pinMode(MOTOR2RE, OUTPUT);
  pinMode(VELM1, OUTPUT);
  pinMode(VELM2, OUTPUT);
  pinMode(VELMOTORBASE, OUTPUT);
  pinMode(MOTORBASEROTDIR, OUTPUT);
  pinMode(MOTORBASEROTESQ, OUTPUT);
  digitalWrite(MOTORBASEROTDIR, LOW);
  digitalWrite(MOTORBASEROTESQ, LOW);

  servoGarra.attach(SERVOGARRA);
  servoBase.attach(SERVOBASE);
  rotacionaGarra.attach(SERVOROTACIONAGARRA);
  meio.attach(SERVOMEIO);
  servoBase.write(90);
  rotacionaGarra.write(90);
  meio.write(90);
}

void loop() {
  if (radio.available()) {
    radio.read(&dadosRecebidos, sizeof(dadosRecebidos)); 

    int velocidade = 0;  //nao é preciso guardar a variável durante as iterações, então nao precisa ser static

    servoBase.write(map(dadosRecebidos.joystick2Y, 0, 1023, 0, 180));

    //controle da garra
    if(dadosRecebidos.buttonJ2 && !dadosRecebidos.buttonJ1){  // se apenas o analogico 2 esta pressionado, abre a garra
      servoGarra.write(70);
    }
    if(dadosRecebidos.buttonJ2 && dadosRecebidos.buttonJ1){  //se ambos estao pressionados, fecha
      servoGarra.write(180);
    }
    if(!dadosRecebidos.buttonJ2){     //se o analogico 2 nao estiver pressionado, mantem a garra parada
      servoGarra.write(88); 
    }

    //como tenho 2 analógicos apenas, precisei usar um deles para fazer mais de uma coisa. Se está precionado, controla os servos, senão, controla os motores
    
    if (dadosRecebidos.buttonJ1 == true) {    
      meio.write(map(dadosRecebidos.joystick1X, 0, 1023, 0 , 180));  //map() é uma regra de 3, como write() recebe valores de 0 a 180 e o analogico funciona de 0  ate 1023, é necessário reduzir o intervalo proporcionalmente.
      rotacionaGarra.write(map(dadosRecebidos.joystick1Y, 0, 1023, 0 , 180));
    }else{
      //é possível fazer com if's independentes também.....
      if(dadosRecebidos.joystick1X > 450 && dadosRecebidos.joystick1X < 550){      //se o eixo x ta centralizado
        if(dadosRecebidos.joystick1Y > 450 && dadosRecebidos.joystick1Y < 550){   //se o eixo y também ta centralizado -> para os motores
          digitalWrite(MOTOR1RD, LOW);
          digitalWrite(MOTOR1RE, LOW);
          digitalWrite(MOTOR2RD, LOW);       //se os dois eixos (X e Y) estao centralizados, os motores devem ficar parados
          digitalWrite(MOTOR2RE, LOW);
          analogWrite(VELM1, 0);
          analogWrite(VELM2, 0);
        }else{
          if (dadosRecebidos.joystick1Y > 550){  //se chegou ate esse if, o eixo x esta parado, e o y é maior que 550, entao o robo deve rotacionar os motores para a direita, para assim, seguir em frente
            digitalWrite(MOTOR1RD, HIGH);
            digitalWrite(MOTOR1RE, LOW);
            digitalWrite(MOTOR2RD, HIGH);
            digitalWrite(MOTOR2RE, LOW);
            velocidade = map(dadosRecebidos.joystick1Y, 0, 1023, 60, 255);
            analogWrite(VELM1, velocidade);
            analogWrite(VELM2, velocidade);
          }else{                               //so resta andar de re
            digitalWrite(MOTOR1RD, LOW);
            digitalWrite(MOTOR1RE, HIGH);
            digitalWrite(MOTOR2RD, LOW);
            digitalWrite(MOTOR2RE, HIGH);
            velocidade = map(dadosRecebidos.joystick1Y, 0, 1023, 255, 60);
            analogWrite(VELM1, velocidade);
            analogWrite(VELM2, velocidade);
          }
        }
      }else{   //se veio para esse else, o eixo x nao esta centralizado, então é preciso analisar o eixo Y
        if(dadosRecebidos.joystick1Y > 450 && dadosRecebidos.joystick1Y < 550){   // o y esta centralizado, entao da para seguir sem conflitos entre as posicoes         
          if(dadosRecebidos.joystick1X > 550){                    
            digitalWrite(MOTOR1RD, HIGH);
            digitalWrite(MOTOR1RE, LOW);    //vira o robo para a direita
            digitalWrite(MOTOR2RD, LOW);
            digitalWrite(MOTOR2RE, HIGH);
            velocidade = map(dadosRecebidos.joystick1X, 0, 1023, 60, 255);
            analogWrite(VELM1, velocidade);
            analogWrite(VELM2, velocidade);
          }else{                               
            digitalWrite(MOTOR1RD, LOW);
            digitalWrite(MOTOR1RE, HIGH);
            digitalWrite(MOTOR2RD, HIGH);   //esquerda
            digitalWrite(MOTOR2RE, LOW);
            velocidade = map(dadosRecebidos.joystick1X, 0, 1023, 255, 60);
            analogWrite(VELM1, velocidade);
            analogWrite(VELM2, velocidade);
          }
        }
      }
    }
    //controle da base, segue a mesma logica
    if(dadosRecebidos.joystick2X > 450 && dadosRecebidos.joystick2X < 550){
      digitalWrite(MOTORBASEROTDIR, LOW);
      digitalWrite(MOTORBASEROTESQ, LOW);
      analogWrite(VELMOTORBASE, 0);
    }else if(dadosRecebidos.joystick2X < 450){
      digitalWrite(MOTORBASEROTDIR, LOW);
      digitalWrite(MOTORBASEROTESQ, HIGH);
      analogWrite(VELMOTORBASE, map(dadosRecebidos.joystick2X, 0, 450, 255, 60));
    }else{
      digitalWrite(MOTORBASEROTDIR, HIGH);
      digitalWrite(MOTORBASEROTESQ, LOW);
      analogWrite(VELMOTORBASE, map(dadosRecebidos.joystick2X, 550, 1023, 60, 255));
    }

  }
}

