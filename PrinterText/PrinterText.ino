
#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
#define BUTTON_PIN 3 //Button pin
#define VCC_PIN 9 //Button pin

#define LinesLength 18

int delayTime = 8;
int PrintRepeats = 3;
int LineCounter = 0;

char* Lines[] = {"Did I just eat bacteria, am I \ngoing to get a disease?", 
"It leaves a stinky taste in your mouth.", 
"That smell's horrible.", 
"I'm not eating this.", 
"That smells like rotten eggs or  fish.", 
"Please don't tell me it tastes \nlike it smells.", 
"There's bacteria everywhere.", 
"It tasted like dish water.", 
"That smells like fart.",
"It tastes like stinky.",
"What is this, spider eggs?",
"It smells like paint and puke.",
"I don't want to eat this.",
"I'm not comfortable with this.",
"No, it's slimey, I'm not going \nto eat it.",
"Eeuw, eeuw, eeuw, eeuw, eeuw.",
"It tastes like a really, really, really old hamburger.",
"It taste like garbage smells."
};

char* clientText = "www.studio-h.co.za \nIG: @studio_h_";


//"www.studio-h.co.za    IG: @studio_h_";

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)

  pinMode(BUTTON_PIN, INPUT);
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);

  printer.setSize('S');
  printer.println("\n");
  delay(delayTime);
  printer.println("Startup test...");
  printer.println("\n");
}

void loop() {
  if (digitalRead(BUTTON_PIN)) {
    //    printer.wake();       // MUST wake() before printing again, even if reset
    PrintQuotes();
    printer.feed(2);
    //    printer.sleep();      // Tell printer to sleep
  }
}

void PrintQuotes() {
  printer.justify('C');
  printer.println("\n");
  delay(delayTime);
  printer.println(Lines[LineCounter]);
  printer.println("\n");
  delay(delayTime);
  printer.justify('C');
  printer.println(clientText);
  printer.println("\n");
  LineCounter++;
  if (LineCounter >= LinesLength) {
    LineCounter = 0;    //reset counter
  }
}
