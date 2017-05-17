#define REDPIN 5
#define BLUEPIN 6
#define GREENPIN 3

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete



void setup() {

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);


 digitalWrite(REDPIN, HIGH);
      digitalWrite(GREENPIN, HIGH);
      digitalWrite(BLUEPIN, HIGH);
  
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}



void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    if(inputString == "ON\r\n") {
      digitalWrite(REDPIN, HIGH);
      digitalWrite(GREENPIN, HIGH);
      digitalWrite(BLUEPIN, HIGH);
    }

    if(inputString == "OFF\r\n") {
      digitalWrite(REDPIN, LOW);
      digitalWrite(GREENPIN, LOW);
      digitalWrite(BLUEPIN, LOW);
    }

    if(inputString[0] == 'C') { 
      // we got 'C' parameter
      long long number = strtol( &inputString[6], NULL, 16);

      // Split them up into r, g, b values
      int r = number >> 16;
      int g = number >> 8 & 0xFF;
      int b = number & 0xFF;

      analogWrite(REDPIN, r);
      analogWrite(GREENPIN, g);
      analogWrite(BLUEPIN, b);
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
