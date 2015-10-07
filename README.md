# FN605

Arduino library for Flyron Technology FN605-M01

This is an Arduino library for use with the Flyron Technology FN605-M01 Flash Memory Based Mini Embedded MP3 Sound Module ( http://flyrontech.com/eproducts/104.html )

This library uses one pin of the Arduino to control the FN605 via one-line serial control mode. You can also use an optional second pin of the Arduino to monitor the busy status of the module. The library provides methods to play current file, play a specific file number, play next, play previous, play random loop, play single loop, play loop, cancel loop play, pause, stop, mute and volume control.

I am not affiliated with Flyron Technology in any way. I wrote this library for my own use of the FN605 and decided to share it to make it easy for others to use. The FN605 is an extremely easy module to use to add sound to a project.

Please see: <a href="http://www.sitena.me/">www.sitena.me</a> for examples of my work.

# How to use

In order to use this library with Arduino you will need to download the FN605 directory and save it to the "libraries" in your Arduino installation. Once installed you can look at the examples or start using it by adding:

#include <FN605.h>

to your Arduino sketch.

