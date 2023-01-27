// Arduino synth library absolute frequency example

/*
 python3
 import serial
 arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
 arduino.write(bytes([]))

 import mido
 port = mido.open_input('wavetable', virtual=True)
 for message in port:
  print(message)

"ctrl + c"

  for message in port:
    if message.type == "note_on":
      arduino.write(bytes([message.note]))
    if message.type == "note_off":
      arduino.write(bytes([128]))
 */

//Hardware connections:

//                    +10µF 
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND


#include <synth.h>

synth edgar;    //-Make a synth

void setup() {

  edgar.begin();                                //-Start it up
  edgar.setupVoice(0,SQUARE,60,ENVELOPE1,127,64);  //-Set up voice 0
  
  Serial.begin(9600);
}

void serialEvent() {

  float pitch;
  
  while(Serial.available()) {
      int option = (int)Serial.read();

      Serial.println(option);

      if (option < 128) {  
        pitch = 440.0 * pow(2.0, ((float)option - 69.0) / 12.0);
        edgar.setFrequency(0, pitch);
        edgar.trigger(0);
      }
      else {
        edgar.setFrequency(0, 0.0);
        edgar.trigger(0);
      }
   }
}

void loop()
{
   
}
