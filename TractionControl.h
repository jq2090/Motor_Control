#ifndef TractionControl_h
#define TractionControl_h
#include "Arduino.h"

class TractionControl
{
  public:
    TractionControl(int _buttonPin, int _val);
    
    void process();
    void pressHandler(void (*f)(int));
    void (*pressCallback)(int);

    int val;
    int buttonPin;
    bool buttonState;
    bool lastButtonState;

  private:
};

#endif
