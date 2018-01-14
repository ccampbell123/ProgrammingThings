#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int speed = 100;
int threshold = 200;
int sensorArr[6];
bool roomArr[10];
int roomNo = 0;
char corridorArr[10];
int corridorNo = 0;
enum runType { automatic, manual, pause, room, corridor}; 
enum runType active = pause;

bool connected = false;
bool obstical = false;
bool corridorEntered = false;
bool corridorEnd = false;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  connectToGUI();
  calibrate();
}

void sensorTest(){
  while(2>1) {
    bool checked = checkForObstacle();
    if(checked) {
      Serial.println("yes");
    } else {
      Serial.println("no");
    }
  }
}

void connectToGUI(){
  while(!connected) {
    char input = Serial.read();
    if(input == '@') {
      connected = true;
    }
  }
}

void calibrate(){
  delay(100);
  Serial.println("Please press the button on the Zumo for calibration.");
  buzzer.play(">g32>>c32");
  reflectanceSensors.init();
  button.waitForButton();
  Serial.println("Calibrating...");
  digitalWrite(13, HIGH);
  delay(1000);
  for(int i = 0; i < 80; i++)
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
  Serial.println("Calibrated.");
  delay(200);
  Serial.print("Please place the Zumo in the starting position and ");
  Serial.println("press the button on the Zumo when ready to start.");
  button.waitForButton();
  buzzer.play("L16 cdegreg4");
  delay(200);
  Serial.println("Press Auto-Start to continue");
}

void loop()
{
  char input = Serial.read();
  checkInput(input);
  switch(active){
    case automatic:
      run();
      break;
    case manual:
      manualMode();
      break;
    case pause:
      stop();
      break;
    case corridor:
      corridorMode();
      break;
    case room:
      roomMode();
      break;
    default:
      break;
  }
  delay(100);
}

void checkInput(char input) {
  if (input == 'p') {
    Serial.println("Automatic mode.");
    active = automatic;
  } else if (input == 'x') {
    Serial.println("Pause mode.");
    delay(200);
    Serial.println("Press any button to continue.");
    active = pause;
  } else if (input == 'm') {
    Serial.println("Manual mode.");
    delay(200);
    Serial.println("Press the complete button when finished.");
    active = manual;
  } else if (input == 'r') {
    Serial.println("Room mode.");
    active = room;
  } else if (input == 'o') {
    Serial.println("Corridor Mode.");
    active = corridor;
  }
}

void run() {
  reflectanceSensors.readCalibrated(sensorArr);
  forward();
  if (sensorArr[2] > threshold || sensorArr[3] > threshold ){
    Serial.println("I Have hit a wall, entering manual mode for my next command.");
    delay(200);
    Serial.println("Press the complete button when finished.");
    stop();
    active = manual;
    corridorCheck();
  } else if (sensorArr[5] > threshold) {
    left();
  } else if (sensorArr[0] > threshold) {
    right();
  }
}

void corridorCheck(){
  if(corridorEntered){
      if(corridorEnd){
        char turn = corridorArr[corridorNo - 1];
        if(turn == 'l') {
          Serial.println("Zumo must turn left out of the corridor to continue search.");
        } else {
          Serial.println("Zumo must turn right out of the corridor to continue search.");
        }
        corridorEntered = false;
        corridorEnd = false;
      }
      corridorEnd = true;
    }
}

void manualMode() {
  while(active == manual){
    char input = Serial.read();
    switch(input){
      case 'w':
        forward();
        break;
      case 'a':
        left();
        break;
      case 's':
        back();
        break;
      case 'd':
        right();
        break;
      case 'c':
        active = automatic;
        break;
      case 'x':
        stop();
        break;
      default:
        break;
    }
  }
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

void corridorMode() {
  delay(100);
  Serial.println("Waiting for corridor location, Left or Right? (A/D)");
  while(active == corridor) {
    char input = Serial.read();
    switch(input){
      case('a'):
        delay(100);
        Serial.println("Corridor is on the left.");
        corridorArr[corridorNo] = 'l';
        active = manual;
        break;
      case('d'):
        delay(100);
        Serial.println("Corridor is on the right.");
        corridorArr[corridorNo] = 'r';
        active = manual;
        break;
      default:
        break;
    }
  }
  delay(100);
  Serial.print("Entered corridor ");
  Serial.print(corridorNo+1);
  Serial.println(".");
  corridorNo++;
  corridorEntered = true;
}

void roomMode() {
  Serial.println("Waiting for room location, Left or Right? (A/D)");
  while(active == room) {
    char input = Serial.read();
    switch(input){
      case('a'):
        delay(100);
        Serial.println("Room is on the left.");
        active = manual;
        delay(200);
        Serial.println("Entered manual mode, one in position, click complete to scan the room.");
        delay(200);
        Serial.println("Press the complete button when finished.");
        manualMode();
        scanRoom();
        break;
      case('d'):
        delay(100);
        Serial.println("Room is on the right.");
        active = manual;
        delay(200);
        Serial.println("Entered manual mode, one in position, click complete to scan the room.");
        delay(200);
        Serial.println("Press the complete button when finished.");
        manualMode();
        scanRoom();
        break;
      default:
        break;
    }
  }
}

void scanRoom() {
  delay(100);
  Serial.print("Zumo has entered room number ");
  Serial.print(roomNo + 1);
  Serial.print(" in corridor ");
  Serial.println(corridorNo + 1);
  for(int i = 0; i < 40; i++) {
    if ((i > 10 && i <= 30) ) {
      motors.setSpeeds(-200, 200);
    } else { 
      motors.setSpeeds(200, -200);
    }
    if(checkForObstacle()){
      obstical = true;
    }
    delay(20);
  }
  stop();
  if(obstical == true){
    delay(100);
    Serial.print("There is an object that has been found in room ");
    Serial.print(roomNo + 1);
    Serial.println(".");
  } else {
    delay(100);
    Serial.print("There is no object found in room ");
    Serial.print(roomNo + 1);
    Serial.println(".");
  }
  roomNo++;
  roomArr[roomNo] = obstical;
  obstical = false;
  delay(100);
  Serial.println("Entered manual mode to leave room.");
  delay(200);
  Serial.println("Press the complete button when finished.");
  active = manual;
}

bool checkForObstacle(){
  delay(50);
  int ping = sonar.ping_cm();
  if (ping < 20 && ping != 0){
    return true;
  }
  return false;
}

