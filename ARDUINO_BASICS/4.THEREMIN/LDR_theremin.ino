 /* Quasi-theremin instrument

Connect the photoresistor one leg to pin 0, and pin to +5V
Connect a resistor (around 10k is a good value, higher
values gives higher readings) from pin 0 to GND.

----------------------------------------------------

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin A0 o-----------
 Pin A5 o-------/\/\/--------o GND
              Piezo Buzzer
----------------------------------------------------
*/

int lightPin = A0;   //define a pin for Photo resistor
long brightness; //the reading from the photoresistor
int maxBrightness; //the ambient light at start up to use as 'max calibration'
// introduce mapped variable "myTone"
int myTone = 0;
int speakerPin = A5;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 457};
int numTones = 11; //How many tones are we using?
String notes[]={"mid C","C#","D","D#","E","E#","F","F#","G","G#","A"};

void setup()
{
  Serial.begin(9600);  //Begin serial communcation
  pinMode(speakerPin, OUTPUT);
  //setting a calibration brightness of the current room
  delay(100);
  maxBrightness = (analogRead(lightPin));
  Serial.println('calibration value: '+ brightness);
}
void loop()
{  
  // Read LDR & then Write the value of the photoresistor to the serial monitor to debug.
  brightness = (analogRead(lightPin));
  Serial.println(brightness);
  myTone = map(brightness, 50, maxBrightness, 0, 10); //force the values (myTone) to 'cover' the range of the chosen tones - from tones[0] to tones[10]
  delay(100); //short delay for faster response to light.
  if (brightness > 50) {
      tone(speakerPin, tones[myTone]);
      Serial.println(notes[myTone]);
      delay(10);
    }
  else noTone(speakerPin);
    Serial.println('playing tone: '+ myTone);            // Print to serial port
    delay(200);                          //pause for 200 millis
}

