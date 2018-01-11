// Need G4P library
import g4p_controls.*;
import processing.serial.*;

Serial myPort;
String portConst = "COM12";
String inString;
boolean initialised = false;

public void setup(){
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[4], 9600);
}

public void draw(){
  background(230);
  while(!initialised){
    initialised = true;
    myPort.write('@');
  }
  fireAllButtonEvents();
  if (myPort.available() > 0) {
    inString = myPort.readStringUntil('\n');
  }
  if(inString != "") {
    txtaComments.appendText(inString);
  }
  inString = "";
}

private void fireAllButtonEvents() {
  btnW.fireAllEvents(true);
  btnA.fireAllEvents(true);
  btnS.fireAllEvents(true);
  btnD.fireAllEvents(true);
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  //btnAutoStart.setEnabled(false);
}