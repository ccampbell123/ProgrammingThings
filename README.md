# ProgrammingThings

Read me for Programming things Zumo task - modify and code a Pololu Zumo robot to perform a (simulated) search and rescue operation.

## Getting Started

1) Set the Zumo onto the black line ready for calibration. Run the GUI and wait for the connection.
2) Follow the commands within the GUI, press the button on the Zumo for calibration to start.
3) Once calibration is finished, press the Zumo button again to confirm the calibration and place the Zumo in start position.
4) Press the Auto-Start button and follow the commands on the GUI.

## Methodology

Initially started out with the work that was completed in class that contained the basics of the movement of the Zumo. 
This contained the basic WASD functionality as well as collision detection.

The approach that I had taken first, was to create the GUI for the controls of the Zumo. 
This allowed me to get the connection between the GUI and the Zumo working together for the console to output.

From here, I had then looked into the calibration that was needed for the Zumo reflectance sensors to work against the black lines.
The code that I ended up using was the same code from the line following example that was provided with the Zumo examples.

Following through the maze follower example, I was able to get the border detection method working, however, it did not work straight away.
As I had the left most sensor to detect first and then the right most sensor, the Zumo would never detect a wall and would just turn instead of stopping like the spec said.
This was resolved by placing the wall detecting code first which uses the middle sensors detect when they sense a black line.

Once that was finished, I changed the main loop within the Arduino code to incorporate an Enum and a switch statement that will control the main running of the Zumo.
This was added to streamline further updates to the code by adding an efficient way of updating the code as well as make the code easier to read for myself.

After this I had noticed that there was no effective way of making sure that the GUI and the Zumo were connected together, this made me believe that there was a need to add a connection method.
This was done by the Zumo waiting for a certain key send over from the GUI to the Zumo by the XBEE's allowing the definite knowledge that the two were connected together.

The next step was to add back in the manual mode into the code again, which only required a small change in order to get the Enum and buttons to work.
The main issue with this was the fact that the button presses were not consistent, sometimes making the Zumo hold a command.
The solution was to look up the reference for the buttons to understand what other events could be called.

* [GUI Event Buttons](http://www.lagers.org.uk/g4p/ref/classg4p__controls_1_1_g_button.html)

Using this resource, I was able to change button clicks so that they worked on press instead of on click, which allows for a greater precision.

```
=======
Using this resource, I was able to change button clicks so that they worked on press instead of on click, which allows for a greater precision.
'''
  if(source == btnW && event == GEvent.PRESSED) {
    myPort.write('w'); 
  } else if (source == btnW && event != GEvent.PRESSED) {
    myPort.write('x');
  }
  //when the W button is initially pressed, it sends the forward command to the zumo,
  //once any other event is executed, it sends an end of command function, telling the zumo that
  // the command has stopped and it should stop.
```
=======
'''

Finally, the last functionality added was the corridor and room controls. This was done by adding two more buttons onto the GUI that tells the Zumo that it is next to a room/corridor.
After this, the user then tells the Zumo through the GUI which direction the room/corridor is located, left or right, using the direction buttons on the GUI.
This also keeps track of the number of rooms that have been entered as well as the corridor number.

The room search function was simple enough to understand how to complete, get the Zumo to sweep the whole room with the sonar sensors running in a certain radius to detect whether there are any objects within the room.
Using the NewPing library, I was able to follow one example in order to incorporate that into my code. The user is then notified within the GUI that there is either an object or no object located within the room.

The corridor functionality allows the Zumo to understand that it has entered a corridor. once the Zumo has reached the end of the corridor, it stores that data for its return journey.
Once it has hit the wall on return, it tells the user which way the Zumo has to turn in order to continue the search.

Unfortunately, due to time constraints I was not able to complete the final task, the automated return functionality.

## Thoughts

Overall, there were no main issues throughout this project, other than my own time keeping skills. The problems that had arisen were almost all solved by stepping through the program around the area that was the issue to try and find the problem. Problems that were not solved this way were googled and a solution was either created from using existing answers or new methods were added into the program replacing the troubling code.

In reflection of coding the program, there would be several different methods that I would use in order to improve on functionality. This would include using the Clean Code methodology that I had learnt on my placement in order to keep the Zumo code ‘clean’ and readable. There are also areas where there are probably better methods that what I have used for the code that, with time, could be researched and incorporated within the program. 
Another problem that I had faced during this task was this is the first time using GitHub, so in which I would either forget to push work that I had completed or not fully understand how it works and caused myself merging issues. These were not major issues at all as I always have a hard copy of all the work, and when the merge issues happened, the problems were fixed compared to the hard copy. Further research into GitHub could provide some better/automated methods for next time. 

* [Zumo video link] (https://photos.app.goo.gl/bZxPEnNRPh4ZSzoq1) 