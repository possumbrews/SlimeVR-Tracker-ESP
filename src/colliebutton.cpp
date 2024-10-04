// //=============================================
// //   ----- Tyroie's Backup code -----
// //=============================================

// In defines.h:
// // Does this use Collie's fancy push-button?
// #define COLLIE_BUTTON true



// In main.cpp
// #include "colliebutton.h"

// down in setup() somewhere, add...
// #if COLLIE_BUTTON == true
//     collieButton::setup();
// #endif

// and down in loop() somewhere, add...
// #if COLLIE_BUTTON == true
//     collieButton::update();
// #endif



// in colliebutton.h, a brand new file:
//  #ifndef COLLIEBUTTON_H_
//  #define COLLIEBUTTON_H_

//  namespace collieButton {
//      void setup();
//      void update();
//  }

//  #endif // COLLIEBUTTON_H_



// in colliebutton.cpp, a brand new file:

#include "colliebutton.h"


int currentTime = 10000;

namespace collieButton {

                                           // These variables are remembered across loops
    bool button_FirstRelease = true;          // We'll ignore the first release of button
     int button_IsDown = true;            // So we'll know if the button state is changed
    long button_TimeWhenPressedDown = 0;         // So we'll know how long it was pressed

    void setup() {
        pinMode(BUTTON_PIN, INPUT_PULLUP);                     // Sets button pin as input
        digitalWrite(BUTTON_PIN, HIGH);                        // Holds button power on
        pinMode(LED_PIN, OUTPUT);                              // Sets LED pin as output
        digitalWrite(LED_PIN, HIGH);                           // Turns the LED off
        pinMode(LED_2_PIN, OUTPUT);                            // Sets LED pin as output
        digitalWrite(LED_2_PIN, LOW);                          // Turns the LED ???
    }

    void update() {        // In main's loop, this is the colliebutton::update() we call!

                                                   // These variables are reset each loop
            currentTime = millis();
        int buttonState = digitalRead(BUTTON_PIN);
        
        if (currentTime > STARTUP_DELAY) {           // Button is 100% ignored for first 2 seconds
            if (buttonState != button_IsDown) {       // If button's state has changed...
                if (button_FirstRelease == true) {            // Ignore the first release
                    button_FirstRelease = false;
                } 
                else {
                    button_IsDown = buttonState;             // Record the button's state
                    if (button_IsDown == HIGH) {               // If button is pressed...
                        button_TimeWhenPressedDown = millis();   // Record the press time
                    } 
                    else {                            // Else, if button is released...
                        if ((currentTime - button_TimeWhenPressedDown) >= SHUTDOWN_TRIGGER) {      // If button was held for more than 3 seconds...
                                                          
                                          // INSERT SHUTDOWN CODE HERE c:

                          while (69 == 69) {                                                  // Enter SHUTDOWN !!!
                            buttonState = digitalRead(BUTTON_PIN);                            // Check if button is pressed
                            digitalWrite(LED_PIN, LOW);                                       //==========================================
                            delay(69);                                                        //===============FLASH======================
                            digitalWrite(LED_PIN, HIGH);                                      //================LED=======================
                            delay(69);                                                        //==========================================
                            if (buttonState == HIGH) {                                        // Check if button is relesed
                              delay(1000);
                              pinMode(BUTTON_PIN, OUTPUT);                                    // Set output to turn off inturnal pull up resistor.
                              digitalWrite(BUTTON_PIN, LOW);                                  // Turn off device
                              delay(3000);                                                    // Delay to alow caps to drain
                              break;                                                          // EXIT SUTDOWN if ESP is still receving power                               
                            }
                          } 
                        }
                      }
                  }
            }
        }
    }
}
// //=============================================
// //   ----- end / Tyroie's Backup code -----
// //=============================================