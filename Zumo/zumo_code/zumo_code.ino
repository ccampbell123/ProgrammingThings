#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#define trigPin 2
#define echoPin 3
#define SENSOR_THRESHOLD 200

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int speed = 100;
int threshold = 300;
int sensorArr[6];
int j = 0;
enum runType { automatic, manual, pause}; 
enum runType active;

bool connected = false;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //trouble connecting to gui now, method to check connection needed.
  connectToGUI();
  calibrate();
}

void connectToGUI(){
  
  while(!connected) {
    char input = Serial.read();
    if(input == '@') {
      connected = true;
    }
    delay(100);
  }
}

void calibrate(){
  Serial.println("Please press the button on the Zumo for calibration.");
  buzzer.play(">g32>>c32");
  reflectanceSensors.init();
  button.waitForButton();
  Serial.println("Calibrating");
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
      
    reflectanceSensors.calibrate();
    delay(20);
  }
  motors.setSpeeds(0,0);
  digitalWrite(13, LOW);
  buzzer.play(">g32>>c32");
  Serial.println("Calibrated");
  button.waitForButton();
  buzzer.play("L16 cdegreg4");
}

void forward() {
  motors.setLeftSpeed(speed);
  motors.setRightSpeed(speed);
}

void back(){
  motors.setLeftSpeed(-speed);
  motors.setRightSpeed(-speed);
}

void left(){
  motors.setLeftSpeed(-speed*2);
  motors.setRightSpeed(speed*2);
}

void right(){
  motors.setLeftSpeed(speed*2);
  motors.setRightSpeed(-speed*2);
}

void stop(){
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

void avoidObstacle(){
  motors.setLeftSpeed(speed*2);
  motors.setRightSpeed(-speed*2);
  delay (2000);
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

//bool checkForObstacle(){
//  long duration, distance;
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = (duration/2) / 29.1;
//  if (distance<4){
//    return false;
//  }
//  return true;
//}

void loop()
{
  char input = Serial.read();
  checkInput(input);
  switch(active){
    case automatic:
      //Serial.println("automatic");
      run();
      break;
    case manual:
      //Serial.println("manual");
      break;
    case pause:
      //Serial.println("pause");
      stop();
      break;
    default:
      //Serial.println("default");
      break;
  }
  delay(100);
}

void checkInput(char input) {
  if (input == 'p') {
    Serial.println("Running");
    active = automatic;
  } else if (input == 'x') {
    Serial.println("Stopping");
    active = pause;
  }
}

void run(){
    reflectanceSensors.readCalibrated(sensorArr);
    forward();
    if (sensorArr[2] > threshold && sensorArr[3] > threshold){//wall has to go first or left gets hit first
      Serial.println("wall");
      stop();
    } else if (sensorArr[5] > threshold) {//right
      Serial.println("Right");
      left();
    } else if (sensorArr[0] > threshold) {//left 
      Serial.println("Left");
      right();
    }
}




