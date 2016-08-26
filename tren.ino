#include <Servo.h> 
#define ECHO2 6
#define TRIG2 7
#define ECHO1 5
#define TRIG1 4
#define ROJO 2
#define VERDE 3
long duracion;
boolean plumillaArriba;
Servo servo;
int fuerza;


int getDistancia1() {
  int dis = 0;
  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duracion = pulseIn(ECHO1, HIGH);
  dis = (duracion / 2) / 29;

  return dis;
}

int getDistancia2() {
  int dis = 0;
  digitalWrite(TRIG2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  duracion = pulseIn(ECHO2, HIGH);
  dis = (duracion / 2) / 29;
  
  return dis;
}

void setup() {
  Serial.begin(9600);
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  digitalWrite(VERDE, LOW);
  digitalWrite(ROJO, HIGH);
  plumillaArriba = true;
  servo.attach(9);
  servo.write(90);
}

void loop() {

  fuerza = analogRead(0);
  
  if(fuerza > 20) {
    digitalWrite(ROJO, LOW);
    digitalWrite(VERDE, HIGH);
  }
  else {
    digitalWrite(ROJO, HIGH);
    digitalWrite(VERDE, LOW); 
  }
    
  
  if(plumillaArriba) {
    Serial.println("Arriba");
    servo.write(90);
    
    if(getDistancia1() <= 5) 
      plumillaArriba = false;
  
  }
  else {
    Serial.println("Abajo");
    servo.write(1);

    if(getDistancia2() <= 5 && getDistancia1() > 5)
      plumillaArriba = true;
  }
  
  //Serial.print("1: "); Serial.println(getDistancia1());
  //Serial.print("2: "); Serial.println(getDistancia2());
  //Serial.println();
  //Serial.println(fuerza);

  
  delay(100);

}
