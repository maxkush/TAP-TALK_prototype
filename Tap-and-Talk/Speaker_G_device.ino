#include <SoftwareSerial.h>
#include <Bounce.h>

Bounce speakButton = Bounce(8, 20);
Bounce ImmediateSpeakButton = Bounce(9, 20);

long timer;
int counter = 0;

static char input_BT[16];
static uint8_t l;
char c_BT;
int number_BT;


void setup() {
  Serial1.begin(38400);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  timer = millis();
}

void loop() {
  speakButton.update();
  ImmediateSpeakButton.update();

  if ( Serial1.available () > 0 ) { // listen to the controller
    c_BT = Serial1.read ();
    if ( c_BT != '\r' && l < 15 ) 
      input_BT[l++] = c_BT;

    else
    {
      input_BT[l] = '\0';
      l = 0;

      number_BT = atoi( input_BT );
      Serial.println(number_BT);
      if (number_BT == 1) {
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
      }
      if (number_BT == 0) {
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
      }
    }
  }

  if (speakButton.fallingEdge()) {
    Serial1.println(11); // Speaker G wants to talk
    Serial1.flush();
  }
  if (speakButton.risingEdge()) {
    Serial1.println(10); // Speaker G doesn't want to talk
    Serial1.flush();
  }
  if (ImmediateSpeakButton.fallingEdge()) {
    Serial1.println(21); // Speaker G wants to talk immediately
    Serial1.flush();
  }
  if (ImmediateSpeakButton.risingEdge()) {
    Serial1.println(20); // Speaker G doesn't want to talk immediately
    Serial1.flush();
  }

}
