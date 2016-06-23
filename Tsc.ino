#include <Servo.h>
#include <DHT.h>
 
#define DHTPIN A1
#define DHTTYPE DHT11

DHT sensor(DHTPIN, DHTTYPE);
Servo leftServo;
Servo rightServo;

int leftServoPin = 9;
int rightServoPin = 10;
 
int leftStop = 72;
int leftUp = 180;
int leftDown = 0;
int rightStop = 95;
int rightUp = 0;
int rightDown = 180;

float t, threshHold;
bool frio;

//funcionalidade adicional: controle manual
int buttonLUPin = 5;
int buttonLDPin = 4;
int buttonRUPin = 3;
int buttonRDPin = 2;

int buttonLU, buttonLD, buttonRU, buttonRD;
//

void setup() 
{ 
  Serial.begin(9600);
  sensor.begin();
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
    
  t = sensor.readTemperature();
  threshHold = t + 2;
  frio = true;

  Serial.print("Iniciado com treshold: ");
  Serial.println(threshHold);

  //mudança manual
  pinMode(buttonLUPin, INPUT);
  pinMode(buttonLDPin, INPUT);
  pinMode(buttonRUPin, INPUT);
  pinMode(buttonRDPin, INPUT);
} 

void loop() 
{ 
  //mudança manual
  buttonLU = digitalRead(buttonLUPin);
  buttonLD = digitalRead(buttonLDPin);
  buttonRU = digitalRead(buttonRUPin);
  buttonRD = digitalRead(buttonRDPin);
  if (buttonLU == HIGH || buttonLD == HIGH)
  {
    if (buttonLU == HIGH)
      leftServo.write(leftUp);
    else
      leftServo.write(leftDown);
    
  }
  else
  {
    leftServo.write(leftStop);
  }

  if(buttonRU == HIGH || buttonRD == HIGH)
  {
    if (buttonRU == HIGH)
      rightServo.write(rightUp);
    else
      rightServo.write(rightDown);
  }
  else
  {
    rightServo.write(rightStop);
  }
  
  t = sensor.readTemperature();
  if (isnan(t))
  {
    Serial.println("Falha na leitura de temperatura");
  }
  else
  {
    Serial.println(t);
    if (t >= threshHold && frio)
    {
      Serial.println("Subindo");
      leftServo.write(leftUp);
      rightServo.write(rightUp);
      delay(5000);
      leftServo.write(leftStop);
      rightServo.write(rightStop);
      frio = false;
    }
    else if (t < threshHold && !frio)
    {
      Serial.println("Descendo");
      leftServo.write(leftDown);
      rightServo.write(rightDown);
      delay(4150);
      leftServo.write(leftStop);
      rightServo.write(rightStop);
      frio = true;
    }
  }
  delay(500);
}
