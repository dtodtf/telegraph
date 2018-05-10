#include <Keyboard.h>

const int letterPin = 6;
const int spacePin = 0;

unsigned long startPressedLetter;
unsigned long endPressedLetter;
unsigned long timeHeldLetter;
int buttonStateLetter = 0;
int lastButtonStateLetter = 0;

const unsigned long cutoff = 300;
String morseLetter = "";

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  pinMode(letterPin, INPUT);
  pinMode(spacePin, OUTPUT);
}

void loop() {
  //all about the letter button
  buttonStateLetter = digitalRead(letterPin); //Did the letter button state change?
  if (buttonStateLetter != lastButtonStateLetter) { //if button is pressed or released:
    if (buttonStateLetter == HIGH) { //if it was pressed
      startPressedLetter = millis(); //save the time when it was pressed
    } else { //if it was released
      endPressedLetter = millis(); //save the time it was released
      timeHeldLetter = endPressedLetter - startPressedLetter; //calculate how long it was held down for
      //Serial.println(timeHeldLetter);
      //Serial.println(dash(timeHeldLetter));
      morseLetter += isDash(timeHeldLetter); //this will be the morse code for a single letter
      Serial.println(morseLetter);
    }
  }
  lastButtonStateLetter = buttonStateLetter; //the current button state is now the old one too;
  checkSpace();
}

void checkSpace(){
  if (digitalRead(spacePin) == HIGH) { //if space button pressed down
    Keyboard.print(determineLetter());
    delay(500);
    morseLetter = "";
  }
}

char determineLetter() { //why is it inserting a space after each char?
  if (morseLetter == "01") {
    return 'A';
  } else if (morseLetter == "1000") {
    return 'B';
  } else if (morseLetter == "1010") {
    return 'C';
  } else if (morseLetter == "100") {
    return 'D';
  } else if (morseLetter == "0") {
    return 'E';
  } else if (morseLetter == "0010") {
    return 'F';
  } else if (morseLetter == "110") {
    return 'G';
  } else if (morseLetter == "0000") {
    return 'H';
  } else if (morseLetter == "00") {
    return 'I';
  } else if (morseLetter == "0111") {
    return 'J';
  } else if (morseLetter == "101") {
    return 'K';
  } else if (morseLetter == "0100") {
    return 'L';
  } else if (morseLetter == "11") {
    return 'M';
  } else if (morseLetter == "10") {
    return 'N';
  } else if (morseLetter == "111") {
    return 'O';
  } else if (morseLetter == "0110") {
    return 'P';
  } else if (morseLetter == "1101") {
    return 'Q';
  } else if (morseLetter == "010") {
    return 'R';
  } else if (morseLetter == "000") {
    return 'S';
  } else if (morseLetter == "1") {
    return 'T';
  } else if (morseLetter == "001") {
    return 'U';
  } else if (morseLetter == "0001") {
    return 'V';
  } else if (morseLetter == "011") {
    return 'W';
  } else if (morseLetter == "1001") {
    return 'X';
  } else if (morseLetter == "1011") {
    return 'Y';
  } else if (morseLetter == "1100") {
    return 'Z';
  } else if (morseLetter == "") {
    return ' ';
  } else if (morseLetter == "010101") {
    return '.';
  } else if (morseLetter == "110011") {
    return ',';
  } else if (morseLetter == "001100") {
    return '?';
  } else if (morseLetter == "10010") {
    return '/';
  } else if (morseLetter == "011010") {
    return '@';
  } else if (morseLetter == "01111") {
    return '1';
  } else if (morseLetter == "00111") {
    return '2';
  } else if (morseLetter == "00011") {
    return '3';
  } else if (morseLetter == "00001") {
    return '4';
  } else if (morseLetter == "00000") {
    return '5';
  } else if (morseLetter == "10000") {
    return '6';
  } else if (morseLetter == "11000") {
    return '7';
  } else if (morseLetter == "11100") {
    return '8';
  } else if (morseLetter == "11110") {
    return '9';
  } else if (morseLetter == "11111") {
    return '0';
  } else {
    Serial.println("That's not Morse.");
  }
}

boolean isDash(long input) { //true means dash, false means dot
  if (input < cutoff) {
    return false;
  } if (input >= cutoff) {
    return true;
  }
}

