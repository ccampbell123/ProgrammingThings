/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void btnAutoStart_click(GButton source, GEvent event) { //_CODE_:btnAutoStart:621694:
  println("btnAutoStart - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('p');
} //_CODE_:btnAutoStart:621694:

public void btnStop_click(GButton source, GEvent event) { //_CODE_:btnStop:807242:
  println("btnStop - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('x');
} //_CODE_:btnStop:807242:

public void btnW_click(GButton source, GEvent event) { //_CODE_:btnW:364075:
  println("btnW - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('w');
} //_CODE_:btnW:364075:

public void btnA_click(GButton source, GEvent event) { //_CODE_:btnA:227525:
  println("btnA - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('a');
} //_CODE_:btnA:227525:

public void btnS_click(GButton source, GEvent event) { //_CODE_:btnS:431688:
  println("btnS - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('s');
} //_CODE_:btnS:431688:

public void btnD_click(GButton source, GEvent event) { //_CODE_:btnD:470462:
  println("btnD - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('d');
} //_CODE_:btnD:470462:

public void btnComplete_click(GButton source, GEvent event) { //_CODE_:btnComplete:320450:
  println("btnComplete - GButton >> GEvent." + event + " @ " + millis());
  myPort.write('c');
} //_CODE_:btnComplete:320450:

public void txtaComments_change(GTextArea source, GEvent event) { //_CODE_:txtaComments:879480:
  println("txtaComments - GTextArea >> GEvent." + event + " @ " + millis());
} //_CODE_:txtaComments:879480:

public void btnCalibrate_click(GButton source, GEvent event) { //_CODE_:btnCalibrate:602138:
  println("btnCalibrate - GButton >> GEvent." + event + " @ " + millis());
} //_CODE_:btnCalibrate:602138:

synchronized public void win_draw1(PApplet appc, GWinData data) { //_CODE_:window1:790959:
  appc.background(230);
} //_CODE_:window1:790959:

public void panel1_Click1(GPanel source, GEvent event) { //_CODE_:panel1:721524:
  println("panel1 - GPanel >> GEvent." + event + " @ " + millis());
} //_CODE_:panel1:721524:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  surface.setTitle("Sketch Window");
  btnAutoStart = new GButton(this, 208, 16, 80, 32);
  btnAutoStart.setText("Auto Start");
  btnAutoStart.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  btnAutoStart.addEventHandler(this, "btnAutoStart_click");
  btnStop = new GButton(this, 304, 16, 80, 30);
  btnStop.setText("Stop");
  btnStop.setLocalColorScheme(GCScheme.RED_SCHEME);
  btnStop.addEventHandler(this, "btnStop_click");
  btnW = new GButton(this, 112, 80, 80, 30);
  btnW.setText("W");
  btnW.setTextBold();
  btnW.addEventHandler(this, "btnW_click");
  btnA = new GButton(this, 16, 128, 80, 30);
  btnA.setText("A");
  btnA.setTextBold();
  btnA.addEventHandler(this, "btnA_click");
  btnS = new GButton(this, 112, 128, 80, 30);
  btnS.setText("S");
  btnS.setTextBold();
  btnS.addEventHandler(this, "btnS_click");
  btnD = new GButton(this, 208, 128, 80, 30);
  btnD.setText("D");
  btnD.setTextBold();
  btnD.addEventHandler(this, "btnD_click");
  btnComplete = new GButton(this, 112, 16, 80, 30);
  btnComplete.setText("Complete");
  btnComplete.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  btnComplete.addEventHandler(this, "btnComplete_click");
  txtaComments = new GTextArea(this, 16, 176, 368, 112, G4P.SCROLLBARS_VERTICAL_ONLY | G4P.SCROLLBARS_AUTOHIDE);
  txtaComments.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  txtaComments.setOpaque(true);
  txtaComments.addEventHandler(this, "txtaComments_change");
  btnCalibrate = new GButton(this, 16, 16, 80, 30);
  btnCalibrate.setText("Calibrate");
  btnCalibrate.addEventHandler(this, "btnCalibrate_click");
  window1 = GWindow.getWindow(this, "Window title", 0, 0, 240, 120, JAVA2D);
  window1.noLoop();
  window1.addDrawHandler(this, "win_draw1");
  panel1 = new GPanel(window1, 70, 30, 100, 60, "Tab bar text");
  panel1.setText("Tab bar text");
  panel1.setOpaque(true);
  panel1.addEventHandler(this, "panel1_Click1");
  window1.loop();
}

// Variable declarations 
// autogenerated do not edit
GButton btnAutoStart; 
GButton btnStop; 
GButton btnW; 
GButton btnA; 
GButton btnS; 
GButton btnD; 
GButton btnComplete; 
GTextArea txtaComments; 
GButton btnCalibrate; 
GWindow window1;
GPanel panel1; 