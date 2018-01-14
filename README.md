# ProgrammingThings

Read me for Programming things Zumo task - modify and code a Pololu Zumo robot to perform a (simulated) search and rescue operation.

## Getting Started



Initially started out with the work that was completed in class that contained the basics of the movement of the zumo. This contained the basic WASD functionality as well as collision detection.

The approach that I had taken first, was to create the GUI for the controlls of the zumo. This allowed me to get the connection between the GUI and the Zumo working together for the console to output.

From here, i had then looked into the calibration that was needed for the zumo reflectance sensors to work against the black lines.
The code that I ended up using was the same code from the line following example that was provided with the zumo examples.

Following through the maze follower example, i was able to get the border detection method working, however, it did not work straight away.
As i had the left most sensor to detect first and then the right most sensor, the ~Zumo would never detect a wall and would just turn insteaf of stopping like the psec said.
This was resolved by placing the wall detecting code first which uses the middle sensors detect when they sense a black line.

-changed the loop to incorperate enum
- gui connection
- manual mode
- 


* [GUI Event Buttons](http://www.lagers.org.uk/g4p/ref/classg4p__controls_1_1_g_button.html)

Using this resource, i was able to change button clicks so that they worked on press instead of on click, which allows for a greater precision.

```
  if(source == btnW && event == GEvent.PRESSED) {
    myPort.write('w'); 
  } else if (source == btnW && event != GEvent.PRESSED) {
    myPort.write('x');
  }
  //when the W button is initially pressed, it sends the forward command to the zumo,
  //once any other event is executed, it sends an end of command function, telling the zumo that
  // the command has stopped and it should stop.
```


## To Add

- corridor and room functionality
- automated return

- p, x, w, a, s, d, c, m, @, r, o