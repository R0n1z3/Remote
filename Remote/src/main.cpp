#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(10, 9,  4000000); //CE, CSN (You have to change these numbers to the digtal output your using for CE, CSN.)
const byte address[6] = "00001";
int Xanalog_input;
int Yanalog_input;
int Xjoystick = A0;
int Yjoystick = A1;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  }

void loop() {
  int Xanalog_input = analogRead(Xjoystick);
  int Yanalog_input = analogRead(Yjoystick);
  Xanalog_input = map(Xanalog_input, 0, 1023, 0, 200);
  Yanalog_input = map(Yanalog_input, 0, 1023, -255, 255); 
  int data[] = 
  {
    Xanalog_input, Yanalog_input
  };
  radio.write(data, sizeof(int)*2);
  Serial.print("Y Value ");
  Serial.println(data[1]);
  Serial.print("X Value ");
  Serial.println(data[0]);
  
}
