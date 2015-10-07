#include <FN605.h>

// Instantiate FN605 object with dataPin 11 and busyPin 12
FN605 FN605(11,12);

void setup()
{
}

void loop()
{
  // Loop and play file 0001.mp3 and 0002.mp3
  for (int x=1; x<=2; x++)
  {
    FN605.volume(4);
    FN605.play(x);
    delay(1000);
  }
}
