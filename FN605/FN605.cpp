/*
  FN605.h - Library for Flyrontech FN605-M01
  Created by Kevin Stephens, October 6, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "FN605.h"

const int VOLUMES[16] = {0xFFE0,0xFFE1,0xFFE2,0xFFE3,0xFFE4,0xFFE5,0xFFE6,0xFFE7,
                         0xFFE8,0xFFE9,0xFFEA,0xFFEB,0xFFEC,0xFFED,0xFFEE,0xFFEF};
  
/*
  You can instaniate the object with just the Arduino pin number connected to the 
  dataPin ( pin 8 ) of the FN605-M01 or you can also send the Arduino pin number
  connected to the busyPin ( pin 5 ) of the FN605-M01 to prevent playing over the
  top of already playing commands.
*/                       
FN605::FN605(int dataPin)
{
  pinMode(dataPin, OUTPUT);
  _dataPin = dataPin;
  _busyPin = -1;
}
// Use the busyPin
FN605::FN605(int dataPin, int busyPin)
{
  pinMode(dataPin, OUTPUT);
  if ( busyPin >= 0 )
  {
    pinMode(busyPin, INPUT);
  }
  _dataPin = dataPin;
  _busyPin = busyPin;
}

/*
  play();                 // Play the current file
  play(fileNumber);       // Play a specific file number ( 1 - 3584 )
  play(fileNumber,true);  // Play a specific file number if not already playing a file
*/
void FN605::play()
{
  play(0,false);
}
void FN605::play(int fileNumber)
{
  play(fileNumber,false);
}
void FN605::play(int fileNumber, boolean ifNotBusy)
{
  uint16_t cmd;
  if ( fileNumber >= 1 )
  {
    cmd = (uint16_t) fileNumber;
  } else {
    cmd = 0xFFF0; // Default back to just play if no file number
  }
  sndCmd(cmd,ifNotBusy);
}

/*
  playNext();     // Play next file
  playNext(true); // Play next file if not already playing a file
*/
void FN605::playNext()
{
  playNext(false);
}

void FN605::playNext(boolean ifNotBusy)
{
  sndCmd(0xFFF4,ifNotBusy);
}

/*
  playPrev();     // Play previous file
  playPrev(true); // Play previous file if not already playing a file
*/
void FN605::playPrev()
{
  playPrev(false);
}

void FN605::playPrev(boolean ifNotBusy)
{
  sndCmd(0xFFF5,ifNotBusy);
}

/*
  playRandom();     // Play random loop
  playRandom(true); // Play random loop if not already playing a file
*/
void FN605::playRandom()
{
  playRandom(false); 
}

void FN605::playRandom(boolean ifNotBusy)
{
  sndCmd(0xFFF7,ifNotBusy); 
}

/*
  singleLoopPlay(); // Loop playing all files one time through
  loopPlay();       // Loop playing all files endlessly
  loopPlayCancel(); // Cancel playing a loop
*/
void FN605::singleLoopPlay()
{
  sndCmd(0xFFF2); 
}

void FN605::loopPlay()
{
  sndCmd(0xFFF6); 
}

void FN605::loopPlayCancel()
{
  sndCmd(0xFFF3); 
}

/*
  pause(); // Pause playing
  stop();  // Stop playing
*/
void FN605::pause()
{
  sndCmd(0xFFF1); 
}

void FN605::stop()
{
  sndCmd(0xFFFE); 
}

/*
  mute();        // Set volume to level 0
  volume(level); // Set volume to level passed in ( 0 - 15 )
*/
void FN605::mute()
{
  volume(0);
}

void FN605::volume(int level)
{
  int cmd = VOLUMES[level];
  sndCmd(cmd);
}

/*
  isBusy(); // If the busyPin was defined it will check if the FN605-M01 is busy
*/
boolean FN605::isBusy()
{
  if ( _busyPin >= 0 )
  {
    return digitalRead(_busyPin);
  } else {
    return false;
  }
}

/*
  sndCmd(cmdCode);           // Send command without checking for busy
  sndCmd(cmdCode,ifNotBusy); // Send command and check busy based on ifNotBusy parameter
*/
void FN605::sndCmd(uint16_t sndCmdCode)
{
  sndCmd(sndCmdCode,false);
}
void FN605::sndCmd(uint16_t sndCmdCode, boolean ifNotBusy)
{
  if ( ifNotBusy && isBusy() )
  {
    return;
  }
  digitalWrite(_dataPin, LOW);
  delay(5);
  
  for(int i=0;i<16;i++)
  { 
    digitalWrite(_dataPin,HIGH);
    if( sndCmdCode &0x8000) {
      delayMicroseconds(600);
      digitalWrite(_dataPin,LOW);
      delayMicroseconds(200);
    } else { 
      delayMicroseconds(200);
      digitalWrite(_dataPin,LOW);
      delayMicroseconds(600);
    }
    sndCmdCode <<=1;
  } 
  digitalWrite(_dataPin,HIGH);
  delay(40);
}
