// Anonymous Fox Is Watching YOU!

int buttonPin[4] = { 36, 35, 34, 33 };
int ledPin[4] = { 23, 22, 21, 20 };
boolean lastButtonState[4] = { LOW, LOW, LOW, LOW };
boolean buttonState[4] = { LOW, LOW, LOW, LOW };
boolean stepState[4] = { false, false, false, false };

int tempo = 0;

int currentStep = 0;
unsigned long lastStepTime = 0;


void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPin[i], INPUT);
  }
  Serial.begin(9600);
}

void sequence() {

  tempo = analogRead(A5);

  if (millis() > lastStepTime + tempo) {   //if its time to go to the next step...
//    digitalWrite(ledPin[currentStep], LOW);  //turn off the current led
    currentStep = currentStep + 1;         //increment to the next step
    if (currentStep > 3) {
      currentStep = 0;
    }
    if (stepState[currentStep] == HIGH) {
      usbMIDI.sendNoteOn(60, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(60, 127, 1);
    }
//    digitalWrite(ledPin[currentStep], HIGH); //turn on the new led
    lastStepTime = millis();               //set lastStepTime to the current time
  }
}

void checkButtons() {
  for (int i = 0; i < 4; i++) {
    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPin[i]);
    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      if (stepState[i] == false) {
        stepState[i] = true;
      } else if (stepState[i] == true) {
        stepState[i] = false;
      }
    }
  }
}

//void setLeds() {
//  for (int i = 0; i < 4; i++) {
//    if (stepState[i] == true) {
//      digitalWrite(ledPin[i], HIGH);
//    } else if (stepState[i] == false) {
//      digitalWrite(ledPin[i], LOW);
//    }
//  }
//}

//setLeds();

void setLeds() {
  for (int i = 0; i < 4; i++) {
    if (ledPin[i] == ledPin[currentStep]) {
      analogWrite(ledPin[i], 255);
    }
    else if (stepState[i] == true) {
      analogWrite(ledPin[i], 15);
    } else {
      analogWrite(ledPin[i], 0);
    }
  }
}

void loop() {
  checkButtons();
  setLeds();
  sequence();
}
