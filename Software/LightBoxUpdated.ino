// Author: Kelsey Li

int OperatingMode = 0; // could make it go from 0 to 4 for each of the operating modes
//operating modes: 0 = off, 1 = bright, 2 = mid-bright, 3 = dim, 4 = flashing
bool ButtonPushed = false; //making this variable global because the variable state needs to be shared between setup, loop, function, etc.
// could also do this as bool ButtonPushed = TRUE; which is a smaller memory variable
int ledState = 0; //blinking LED state
int LEDpin = 9;       //pin for the LED
int ButtonPin = 3;    //pin for the button, only 2 and 3 are digital pins usable for interrupts on the arduino
int PWMout = 0;
unsigned long prevButtonTime = 0;
unsigned long prevLEDtime = 0;

void setup() {
  Serial.begin(9600); //for testing serial monitor in lab
  pinMode(ButtonPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ButtonPin), button_pushed, FALLING);
}

void loop() {
  set_Operating_Mode();

  set_LED_output_mode();

  shine_LED();

  Serial.print(PWMout);
  Serial.print('\n');
  //  Serial.print(ledState);
  //Serial.print('\n');
}

void button_pushed() {
  ButtonPushed = true; //or ButtonPushed = true if using as a boolean;
}

void set_Operating_Mode() {
  if (ButtonPushed == true) {

    if (millis() - prevButtonTime > 200) { // makes sure no double detection of button press, 0.2 s
      OperatingMode = OperatingMode + 1;
      prevButtonTime = millis();
      if (OperatingMode == 5) {
        OperatingMode = 0;
      }
    }
    ButtonPushed = false;
  }
}


void set_LED_output_mode() {
  switch (OperatingMode) {
    // operating modes: 0 = off, 1 = bright, 2 = mid-bright, 3 = dim, 4 = flashing
    case 0:
      PWMout = 0; //off
      break;

    case 1:
      PWMout = 255; //brightest
      break;

    case 2:
      PWMout = 128; //medium brightness
      break;

    case 3:
      PWMout = 64; //dim
      break;

    case 4:
      flashing_light(); //flashing at 2 Hz
      break;
  }

}

void flashing_light() {
  unsigned long currLEDtime = millis();        //built in Arduino times
  if (currLEDtime - prevLEDtime >= 500) {      // 500ms delay = 2Hz blinking rate
    prevLEDtime = currLEDtime;
    if (PWMout == 0) {                       //if LED state off
      PWMout = 255;                             //then set LED state on
    }
    else {                                         //else LED state on
      PWMout = 0;                              //then set LED state off
    }
  }

}

void shine_LED() {
  analogWrite(LEDpin, PWMout);
}

