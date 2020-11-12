#ifndef __PUSH_BUTTON_H__
#define __PUSH_BUTTON_H__

#include <Arduino.h>

#define DEFAULT_STATE_LOW     true
#define DEFAULT_STATE_HIGH    false


class PushButton{
public:
     PushButton(int pin, unsigned long delay, bool defaultState);
     bool isPressed();
     bool longPress();
     int dualFunction();
     int state();

private:
     int _pin;
     bool _logic;
     unsigned long _delay;
     int _lastButtonState;
     unsigned long _lastDebounceTime;
     unsigned int _longDelay;
};

#endif