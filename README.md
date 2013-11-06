DMXProjectionManager
====================

DMX Projection Manager for Microcontroller

This is the software for an Arduino Leonardo configured to act as a projection management interface. The hardware receives instructions from a lighting desk via DMX. One channel of DMX sets the value of a servo allowing the device to physicaly dowse the output of a projector. The other channel of DMX allows the lighting board operator to send keyboard instructions to a PC which is providing a slide show. 

Lighting Desk ---> (DMX) ---> Arduino ---> Direct Connection to Servo
                                      \--> USB Keyboard Emulation to Slideshow Computer
                                      
This system allows a lighting desk to smoothly control all aspects of a power-point-style projection. See code comments for more details.

This project is based off examples from the DMXSerial project and Code by D. Seltzer and A. Elias.

Project built for Staples High School, Staples Players.
