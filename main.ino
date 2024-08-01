/*H********************************************************************************************
** FILENAME :        main.ino
** Version  :        1.0.0
** DESCRIPTION :
**       function to make a hard restart by button at the front of the norvi agent one
**       
** PUBLIC FUNCTIONS :
**      void getLED_Signal(string selection, int repetation, int delayDuration)
**      void getGreenLED_Signal(int delayTime) 
**      void delayLED(int delayTime)
**
** NOTES :
** ToDos :
**
** AUTHOR :            Tjark Ziehm        START DATE :    01 August 2024
** Copyright&Licence:  Tjark Ziehm, 2024
** Convention:         <major>.<minor>.<patch>
** CHANGES :
**
*********************************************************************************************H*/
#include "Wire.h"

// Digital IO pin connected to the button. This will be driven with a
// pull-up resistor so the switch pulls the pin to ground momentarily.
// On a high -> low transition the button press logic will execute.
#define BUTTON_PIN 35  // Button at the top of norvi agent 1 device

boolean oldState = HIGH;
boolean preStartPhase = false;

void getStateRestartButton(){
  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low(button press).
  if ((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW && preStartPhase == true) {
      Serial.println("Reboot");
      ESP.restart();
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;

  //set the preStartPhase after first llop run to true to avoid a permanent 
  //loop by wrong digital signal in start phase of esp32
  preStartPhase = true;
}


void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
}

void loop() {
  checkStateRestartButton();
}
