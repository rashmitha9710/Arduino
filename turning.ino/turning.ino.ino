#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define Center 0
#define CenterLeft 1
#define Left 2
#define CenterRight 3
#define Right 4

Adafruit_MotorShield motorkort = Adafruit_MotorShield();
Adafruit_DCMotor *venstreMotor = motorkort.getMotor(1);
Adafruit_DCMotor *hoyreMotor = motorkort.getMotor(2);

bool folgeLinje = true;

unsigned int venstre, hoyre, senter;
unsigned int S;
unsigned int Input;
unsigned int Output;

const int venstreSensor = A0;
const int senterSensor = A1;
const int hoyreSensor = A2;

const int trigPin = 2;
const int echoPin = 4;
const int voltage = 6;

struct State
{
  unsigned int out;
  unsigned int next[6];
};

typedef const struct State StateType;

StateType fsm[5] = {
  {Center, {Center, CenterLeft, Left, CenterRight, Right, Right}},
  {CenterLeft, {Center, CenterLeft, Left, CenterRight, Right, Left}},
  {Left, {Center, CenterLeft, Left, CenterRight, Right, Left}},
  {CenterRight, {Center, CenterLeft, Left, CenterRight, Right, Right}},
  {Right, {Center, CenterLeft, Left, CenterRight, Right, Right}}
};

void setup()
{
  motorkort.begin();

  venstreMotor->setSpeed(80);
  hoyreMotor->setSpeed(80);

  pinMode(venstreSensor, INPUT);
  pinMode(senterSensor, INPUT);
  pinMode(hoyreSensor, INPUT);

  pinMode(voltage, OUTPUT);
  digitalWrite(voltage, HIGH);

  S = Center;

  Serial.begin(9600);

  delay(8000);
}

void loop()
{
  long duration, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  awayFromWall(cm);
  
  Output = fsm[S].out;
  Robot_Output(Output);
  delay(10);
  Input = Robot_Input();
  S = fsm[S].next[Input];
}

unsigned int Robot_Input()
{
  unsigned int resultat;

  resultat = 0;

  if (venstre == 1 && senter == 1 && hoyre == 1)  resultat = 1;
  if (venstre == 1 && senter == 0 && hoyre == 0)  resultat = 2;  
  if (venstre == 1 && senter == 1 && hoyre == 0)  resultat = 3;  
  if (venstre == 0 && senter == 0 && hoyre == 1)  resultat = 4;  
  if (venstre == 0 && senter == 1 && hoyre == 1)  resultat = 5;

  return resultat;
}

void Robot_Output(unsigned int output)
{/*
  switch (output) 
  {
    case 0:
      venstreMotor->setSpeed(80);
      hoyreMotor->setSpeed(80);
      break;
    case 1:
      venstreMotor->setSpeed(50);
      hoyreMotor->setSpeed(50);
      break;
    case 2:
      venstreMotor->setSpeed(80);
      hoyreMotor->setSpeed(20);
      break;
    case 3:
      venstreMotor->setSpeed(60);
      hoyreMotor->setSpeed(0);
      break;
    case 4:
      venstreMotor->setSpeed(20);
      hoyreMotor->setSpeed(80);
      break;
    case 5:
      venstreMotor->setSpeed(0);
      hoyreMotor->setSpeed(60);
      break;
  }
  forover();*/
}

void LesFraSensorer()
{
  venstre = digitalRead(venstreSensor);
  senter = digitalRead(senterSensor);
  hoyre = digitalRead(hoyreSensor);
}

void forover()
{
  venstreMotor->run(FORWARD);
  hoyreMotor->run(FORWARD);
}

void stopp()
{
  venstreMotor->run(RELEASE);
  hoyreMotor->run(RELEASE);
}

void awayFromWall(long centimeters)
{
  if (centimeters <= 10)
  {
    venstreMotor->setSpeed(200);
    hoyreMotor->setSpeed(0);
    forover();
  }
  else
  {
    venstreMotor->setSpeed(100);
    hoyreMotor->setSpeed(100);
    forover();
  }
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / (2 * 29);
}

