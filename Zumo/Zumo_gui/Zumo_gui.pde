// Need G4P library
import g4p_controls.*;
import processing.serial.*;

Serial myPort;
String portConst = "com13";
String inString;

public void setup(){
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  myPort = new Serial(this, portConst, 9600);
}

public void draw(){
  background(230);
    if (myPort.available() > 0) {
       inString = myPort.readStringUntil('\n');
    }
    if(inString != "") {
      txtaComments.appendText(inString);
    }
  inString = "";
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  //btnAutoStart.setEnabled(false);
}