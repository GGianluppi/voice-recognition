# Voice Recognition

This prototype is part of my Graduation Final Project I, which proposes the development of a home automation device responsible for controlling household appliances and interacting with people with physical disabilities within an environment through voice commands.

## Schematic of the Prototype

In the figure below, we can observe the schematic of the completed prototype.

<p align="center">
<img src="https://user-images.githubusercontent.com/104764600/192167224-593d079e-52f8-46c5-a864-a57df2a56924.JPG" width="550" height="350">
</p>

## Operation for Equipment Activation

The system operates in two modes. The first mode keeps the module in standby mode, where the system waits for an individual to say a predefined word. The second mode is activated after the keyword “Arduino” is spoken, which starts the device. At this moment, the system enters “listening” mode, with a blue LED lighting up for 10 seconds. If the user decides to cancel the command, the system returns to standby mode. This operational mode allows the user to choose the function of turning equipment on or off. The following figure provides a better understanding of this process.

<p align="center">
<img src="https://user-images.githubusercontent.com/104764600/192166906-7e927cc8-2565-454e-8ea9-de7d8b0bec5f.png" width="600" height="200">
</p>

## Voice Recognition Prototype in Operation

Next, it is possible to observe the prototype in action, where the lamp and the fan are activated, represented by the yellow and white LEDs, respectively.

<p align="center"><img src = "https://user-images.githubusercontent.com/104764600/192167120-bc335077-3857-4d31-9b72-95982f9cf9a0.png" width="400" height="250" /> <img src = "https://user-images.githubusercontent.com/104764600/192167246-9f403898-8f04-4c8c-a84c-648205fa2f0c.jpg" width="400" height="250" /></p>
