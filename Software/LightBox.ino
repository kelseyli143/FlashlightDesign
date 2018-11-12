// Author: Kelsey Li

// there are only 4 Arduino pins that can be PWM pins
int OperatingMode = 0; // could make it go from 0 to 4 for each of the operating modes
                        //operating modes: 0 = off, 1 = bright, 2 = mid-bright, 3 = dim, 4 = flashing
// bool ButtonPushed = FALSE; //making this variable global because the variable state needs to be shared between setup, loop, function, etc.
                     // could also do this as bool ButtonPushed = TRUE; which is a smaller memory variable
int ledState = LOW; //blinking LED state
int LEDpin = 5;       //pin for the LED
int ButtonPin = 2;    //pin for the button, only 2 and 3 are digital pins usable for interrupts on the arduino 
int PWMout = 0;
unsigned long prevButtonTime = 0;
unsigned long prevLEDtime = 0;

// explicitly initialize the variables
// unsigned long: float (non-integer) that is positive (unsigned)
// defining the variables allows you to save memory if possible

void setup() {
  // when done executing, 'void' shows that it won't return any values
  // interrupts are for very rapid event detection - MUST BE IN SETUP
  // Serial.begin(9600); for testing serial monitor in lab
    pinMode(ButtonPin,INPUT);
    pinMode(LEDpin,OUTPUT);
    attachInterrupt(digitalPinToInterrupt(ButtonPin), set_Operating_Mode, FALLING);
    // FALLING means sensitive to something changing from the HIGH to LOW state, could also be RISING
    // when falling state is detected, execute the function set_Operating_Mode
}

void loop() {
  set_Operating_Mode();
  
  set_LED_output_mode(); 
}

  void set_Operating_Mode(){
    if (millis()-prevButtonTime>200){ // makes sure no double detection of button press, 0.2 s 
    OperatingMode = OperatingMode + 1;
    //set operating mode
    //reset previous button press state, i.e. interrupt, catch, etc.
  prevButtonTime=millis();
  if (OperatingMode>=5) {
    OperatingMode = 0;
      }
    }
 // ButtonPushed = FALSE; 
  }

  void set_LED_output_mode(){
  switch (OperatingMode) {
    // operating modes: 0 = off, 1 = bright, 2 = mid-bright, 3 = dim, 4 = flashing
  case 0:
    PWMout = 0; //off 
    shine_LED();
    break;
    
  case 1:
  PWMout = 255; //brightest
  shine_LED();
    break;
    //maximum because it's 8 bit microcontroller, not transferrable to microcontrollers with other bit depths 
  
  case 2:
  PWMout = 128; //medium brightness
  shine_LED();
    break;
  
  case 3:
  PWMout = 64; //dim
  shine_LED();
    break;
  
  case 4:
    flashing_light(); //flashing at 2 Hz
    break;
    }
  
  }
  
  void shine_LED(){
  analogWrite(LEDpin,PWMout);
   }
  
  void flashing_light(){
        unsigned long currLEDtime = millis();        //built in Arduinotimes
        if (currLEDtime - prevLEDtime >=500){        // 500ms delay = 2Hz blinking rate
        if (ledState == LOW) {                       //if LED state off
        ledState = HIGH;                             //then set LED state on
      } 
      else {                                         //else LED state on
        ledState = LOW;                              //then set LED state off
      }
  digitalWrite(LEDpin,ledState);  
    }
    prevLEDtime = currLEDtime;
  }


// extra unneeded function, from class
// void button_pushed() {
//  ButtonPushed = TRUE; //or ButtonPushed = TRUE if using as a boolean;
//  }
  
