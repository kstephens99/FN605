/*
  FN605.h - Library for Flyrontech FN605-M01
  Created by Kevin Stephens, October 6, 2015.
  Released into the public domain.
*/
#ifndef FN605_h
#define FN605_h

#include "Arduino.h"

class FN605
{
  public:
    FN605(int dataPin);
    FN605(int dataPin, int busyPin);
    void play();
    void play(int fileNumber);
    void play(int fileNumber, boolean ifNotBusy);
    void playNext();
    void playNext(boolean ifNotBusy);
    void playPrev();
    void playPrev(boolean ifNotBusy);
    void playRandom();
    void playRandom(boolean ifNotBusy);
    void singleLoopPlay();
    void loopPlay();
    void loopPlayCancel();
    void pause();
    void stop();
    void mute();
    void volume(int level);
    boolean isBusy();
  private:
    void sndCmd(uint16_t sndCmdCode);
    void sndCmd(uint16_t sndCmdCode, boolean ifNotBusy);
    int _dataPin;
    int _busyPin;
};

#endif