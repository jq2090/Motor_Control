#include "Arduino.h"
#include "TractionControl.h"

TractionControl::TractionControl(int _buttonPin, int _val)
{
  buttonPin = _buttonPin;
  val = _val;
  pinMode(buttonPin, INPUT);
}

void TractionControl::process()
{
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);

  if (lastButtonState == LOW && buttonState == HIGH) {
    pressCallback(val);
    delay(5);
  }
  if (lastButtonState == HIGH && buttonState == LOW) {
    delay(5);
  }
}

void TractionControl::pressHandler(void (*f)(int))    //button down
{
  pressCallback = *f;
}
