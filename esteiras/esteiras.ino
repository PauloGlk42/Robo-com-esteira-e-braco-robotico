#define MOTOR1RD 4 // MOTOR 1 ROTACAO DIREITA
#define MOTOR1RE 7
#define MOTOR2RD 8 
#define MOTOR2RE 3
#define VELM1 6
#define VELM2 5
#define EIXOX A0
#define EIXOY A1

int valEixoX;
int valEixoY;

void setup() {
  pinMode(MOTOR1RD, OUTPUT);
  pinMode(MOTOR1RE, OUTPUT);
  pinMode(MOTOR2RD, OUTPUT);
  pinMode(MOTOR2RE, OUTPUT);
  pinMode(VELM1, OUTPUT);
  pinMode(VELM2, OUTPUT);
  pinMode(EIXOX, INPUT);
  pinMode(EIXOY, INPUT);

}

void loop() {
  valEixoX = analogRead(EIXOX);
  valEixoY = analogRead(EIXOY);

  int velocidade=0; 

  if(valEixoX > 450 && valEixoX < 550){      //se o eixo x ta centralizado
    if(valEixoY > 450 && valEixoY < 550){   //se o eixo y também ta centralizado -> para os motores
      digitalWrite(MOTOR1RD, LOW);
      digitalWrite(MOTOR1RE, LOW);
      digitalWrite(MOTOR2RD, LOW);
      digitalWrite(MOTOR2RE, LOW);
      analogWrite(VELM1, 0);
      analogWrite(VELM2, 0);
    }else{
      velocidade = map(valEixoX, 0, 1023, 60, 255);
      analogWrite(VELM1, velocidade);
      analogWrite(VELM2, velocidade );

      if (valEixoY > 550){              
        digitalWrite(MOTOR1RD, HIGH);
        digitalWrite(MOTOR1RE, LOW);
        digitalWrite(MOTOR2RD, HIGH);
        digitalWrite(MOTOR2RE, LOW);
      }else{                               
        digitalWrite(MOTOR1RD, LOW);
        digitalWrite(MOTOR1RE, HIGH);
        digitalWrite(MOTOR2RD, LOW);
        digitalWrite(MOTOR2RE, HIGH);
      }
    }
  }else{
    velocidade = map(valEixoX, 0, 1023, 255, 60);
    analogWrite(VELM1, velocidade);
    analogWrite(VELM2, velocidade );

    if(valEixoY > 450 && valEixoY < 550){         
      if(valEixoX > 550){                               
        digitalWrite(MOTOR1RD, HIGH);
        digitalWrite(MOTOR1RE, LOW);
        digitalWrite(MOTOR2RD, LOW);
        digitalWrite(MOTOR2RE, HIGH);
      }else{                                
        digitalWrite(MOTOR1RD, LOW);
        digitalWrite(MOTOR1RE, HIGH);
        digitalWrite(MOTOR2RD, HIGH);
        digitalWrite(MOTOR2RE, LOW);
      }
    }
  }
}
