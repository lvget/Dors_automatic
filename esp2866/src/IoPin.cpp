 #include "IoPin.h"

void Input::init(){  
      pinMode(pin, INPUT_PULLUP);
      value = digitalRead(pin);
      lastRawValue = value;
      lastDebounceTime = millis();
      change = NONE;
}

void Input::read() {
      uint8_t v = digitalRead(pin);
      if (v != lastRawValue) {
            lastRawValue = v;
            lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) >= debounceDelay && lastRawValue != value) {
            value = lastRawValue;
            change = value == ON?UP:DOWN;
            Serial.print(pin);
            Serial.print(" change = ");
            Serial.println(change);
      }
      else {
            change = NONE;
      }
}

void Input::setMode(uint8_t mode){
      if(mode != AUTO)
            change = (value == ON? UP : DOWN);

      this->mode = mode;
}

void Output::init(){  
      pinMode(pin, OUTPUT);
      value = OFF;
      digitalWrite(pin, value);
}

void Output::write(int v){
      value = v;
      if(mode == AUTO){
            digitalWrite(pin, value);
      }
}

void Output::setMode(uint8_t mode){
      if(mode == AUTO){
            digitalWrite(pin, value);
      }
      else{
            digitalWrite(pin, mode);
      }
      this->mode = mode;
}
