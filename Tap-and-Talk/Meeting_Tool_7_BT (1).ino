
#include <Bounce.h>

int queue[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // store the speakers' queue
int speakerState[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int speakerStateImmediate[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int s;
int k; // pedal

static char input_BT[16];
static uint8_t l;
char c_BT;
int number_BT;

int g = 0;
int g_old = 0;

int buzz[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Bounce speakButtonA = Bounce(2, 10);
Bounce speakButtonB = Bounce(3, 10);
Bounce speakButtonC = Bounce(4, 10);
Bounce speakButtonD = Bounce(5, 10);
Bounce speakButtonE = Bounce(6, 10);
Bounce speakButtonF = Bounce(7, 10);
Bounce speakImmediateButtonA = Bounce(8, 10);
Bounce speakImmediateButtonB = Bounce(9, 10);
Bounce speakImmediateButtonC = Bounce(10, 10);
Bounce speakImmediateButtonD = Bounce(11, 10);
Bounce speakImmediateButtonE = Bounce(12, 10);
Bounce speakImmediateButtonF = Bounce(14, 10);

elapsedMillis timer;
elapsedMillis blinkTimer;
int blinking = 0;

void setup() {
  Serial1.begin(38400);
  for (int i = 2; i < 15; i++) {
    if (i != 13) {
      pinMode(i, INPUT_PULLUP); // speaker 1-6 push botton & immergency push botton
    }
  }
  pinMode(13, OUTPUT);
  for (int i = 15; i < 21; i++) {
    pinMode(i, OUTPUT); // speaker i buzzer
  }
  delay(1000);

  speakButtonA.update();
  speakButtonB.update();
  speakButtonC.update();
  speakButtonD.update();
  speakButtonE.update();
  speakButtonF.update();
  speakImmediateButtonA.update();
  speakImmediateButtonB.update();
  speakImmediateButtonC.update();
  speakImmediateButtonD.update();
  speakImmediateButtonE.update();
  speakImmediateButtonF.update();

  delay(1000);
  speakerALL();
  //  Serial1.println(1); // End of Message
  //  Serial1.flush();
}

void loop() {
  speakButtonA.update();
  speakButtonB.update();
  speakButtonC.update();
  speakButtonD.update();
  speakButtonE.update();
  speakButtonF.update();
  speakImmediateButtonA.update();
  speakImmediateButtonB.update();
  speakImmediateButtonC.update();
  speakImmediateButtonD.update();
  speakImmediateButtonE.update();
  speakImmediateButtonF.update();

  // Read device output if available.
  if ( Serial1.available () > 0 ) { // listen to the BT device (Speaker G)
    c_BT = Serial1.read ();
    if ( c_BT != '\r' && l < 15 ) 
      input_BT[l++] = c_BT;

    else
    {
      input_BT[l] = '\0';
      l = 0;

      g = atoi( input_BT );
      // Serial.println(g);
      if (g == 11) {
        digitalWrite(13, HIGH);
      }
      if (g == 10) {
        digitalWrite(13, LOW);
      }
    }
  }

  /////////////////SPEAKER A ////////////  START ///////////
  if (speakButtonA.fallingEdge()) { // speaker A pressed the button
    s = 1;
    speakerState[s] = 1;
    addSpeaker(s);
    trafficLights();
    Serial.println("speakerA gets added to the queue");
    printQueue ();
  }

  if (speakButtonA.risingEdge()) { // speaker A released the button
    s = 1;
    speakerState[s] = 0;
    subtractSpeaker(s);
    trafficLights();
    Serial.println("speakerA gets subtracted from the queue");
    printQueue ();
  }

  if (speakImmediateButtonA.fallingEdge()) { // speaker A pressed the immediate button
    s = 1;
    speakerStateImmediate[s] = 1;
    addSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerA gets added to the queue on 2nd position");
    printQueue ();
  }

  if (speakImmediateButtonA.risingEdge()) { // speaker A released the immediate button
    s = 1;
    speakerStateImmediate[s] = 0;
    subtractSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerA gets subtracted from the queue");
    printQueue ();
  }
  /////////////////SPEAKER A ////////////  END ///////////

  /////////////////SPEAKER B ////////////  START ///////////
  if (speakButtonB.fallingEdge()) { // speaker B pressed the button
    s = 2;
    speakerState[s] = 1;
    addSpeaker(s);
    trafficLights();
    Serial.println("speakerB gets added to the queue");
    printQueue ();
  }

  if (speakButtonB.risingEdge()) { // speaker B released the button
    s = 2;
    speakerState[s] = 0;
    subtractSpeaker(s);
    trafficLights();
    Serial.println("speakerB gets subtracted from the queue");
    printQueue ();
  }

  if (speakImmediateButtonB.fallingEdge()) { // speaker B pressed the immediate button
    s = 2;
    speakerStateImmediate[s] = 1;
    addSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerB gets added to the queue on 2nd position");
    printQueue ();
  }

  if (speakImmediateButtonB.risingEdge()) { // speaker B released the immediate button
    s = 2;
    speakerStateImmediate[s] = 0;
    subtractSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerB gets subtracted from the queue");
    printQueue ();
  }
  /////////////////SPEAKER B ////////////  END ///////////

  /////////////////SPEAKER C ////////////  START ///////////
  if (speakButtonC.fallingEdge()) { // speaker C pressed the button
    s = 3;
    speakerState[s] = 1;
    addSpeaker(s);
    trafficLights();
    Serial.println("speakerC gets added to the queue");
    printQueue ();
  }

  if (speakButtonC.risingEdge()) { // speaker C released the button
    s = 3;
    speakerState[s] = 0;
    subtractSpeaker(s);
    trafficLights();
    Serial.println("speakerC gets subtracted from the queue");
    printQueue ();
  }

  if (speakImmediateButtonC.fallingEdge()) { // speaker C pressed the immediate button
    s = 3;
    speakerStateImmediate[s] = 1;
    addSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerC gets added to the queue on 2nd position");
    printQueue ();
  }

  if (speakImmediateButtonC.risingEdge()) { // speaker C released the immediate button
    s = 3;
    speakerStateImmediate[s] = 0;
    subtractSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerC gets subtracted from the queue");
    printQueue ();
  }
  /////////////////SPEAKER C ////////////  END ///////////

  /////////////////SPEAKER D ////////////  START ///////////
  if (speakButtonD.fallingEdge()) { // speaker D pressed the button
    s = 4;
    speakerState[s] = 1;
    addSpeaker(s);
    trafficLights();
    Serial.println("speakerD gets added to the queue");
    printQueue ();
  }

  if (speakButtonD.risingEdge()) { // speaker D released the button
    s = 4;
    speakerState[s] = 0;
    subtractSpeaker(s);
    trafficLights();
    Serial.println("speakerD gets subtracted from the queue");
    printQueue ();
  }

  if (speakImmediateButtonD.fallingEdge()) { // speaker D pressed the immediate button
    s = 4;
    speakerStateImmediate[s] = 1;
    addSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerD gets added to the queue on 2nd position");
    printQueue ();
  }

  if (speakImmediateButtonD.risingEdge()) { // speaker D released the immediate button
    s = 4;
    speakerStateImmediate[s] = 0;
    subtractSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerD gets subtracted from the queue");
    printQueue ();
  }
  /////////////////SPEAKER D ////////////  END ///////////

  /////////////////SPEAKER E ////////////  START ///////////
  if (speakButtonE.fallingEdge()) { // speaker E pressed the button
    s = 5;
    speakerState[s] = 1;
    addSpeaker(s);
    trafficLights();
    Serial.println("speakerE gets added to the queue");
    printQueue ();
  }

  if (speakButtonE.risingEdge()) { // speaker E released the button
    s = 5;
    speakerState[s] = 0;
    subtractSpeaker(s);
    trafficLights();
    Serial.println("speakerE gets subtracted from the queue");
    printQueue ();
  }

  if (speakImmediateButtonE.fallingEdge()) { // speaker E pressed the immediate button
    s = 5;
    speakerStateImmediate[s] = 1;
    addSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerE gets added to the queue on 2nd position");
    printQueue ();
  }

  if (speakImmediateButtonE.risingEdge()) { // speaker E released the immediate button
    s = 5;
    speakerStateImmediate[s] = 0;
    subtractSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerE gets subtracted from the queue");
    printQueue ();
  }
  /////////////////SPEAKER E ////////////  END ///////////

  /////////////////SPEAKER F ////////////  START ///////////
  if (speakButtonF.fallingEdge()) { // speaker F pressed the button
    s = 6;
    speakerState[s] = 1;
    addSpeaker(s);
    trafficLights();
    Serial.println("speakerF gets added to the queue");
    printQueue ();
  }

  if (speakButtonF.risingEdge()) { // speaker F released the button
    s = 6;
    speakerState[s] = 0;
    subtractSpeaker(s);
    trafficLights();
    Serial.println("speakerF gets subtracted from the queue");
    printQueue ();
  }

  if (speakImmediateButtonF.fallingEdge()) { // speaker F pressed the immediate button
    s = 6;
    speakerStateImmediate[s] = 1;
    addSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerF gets added to the queue on 2nd position");
    printQueue ();
  }

  if (speakImmediateButtonF.risingEdge()) { // speaker F released the immediate button
    s = 6;
    speakerStateImmediate[s] = 0;
    subtractSpeakerImmediate(s);
    trafficLights();
    Serial.println("speakerF gets subtracted from the queue");
    printQueue ();
  }
  /////////////////SPEAKER F ////////////  END ///////////

  /////////////////SPEAKER G ////////////  START ///////////
  if (g != g_old) {
    g_old = g;
    if (g == 11) { // speaker G pressed the button
      s = 7;
      speakerState[s] = 1;
      addSpeaker(s);
      trafficLights();
      Serial.println("speakerG gets added to the queue");
      printQueue ();
    }

    if (g == 10) { // speaker G released the button
      s = 7;
      speakerState[s] = 0;
      subtractSpeaker(s);
      trafficLights();
      Serial.println("speakerG gets subtracted from the queue");
      printQueue ();
    }

    if (g == 21) { // speaker G pressed the immediate button
      s = 7;
      speakerStateImmediate[s] = 1;
      addSpeakerImmediate(s);
      trafficLights();
      Serial.println("speakerG gets added to the queue on 2nd position");
      printQueue ();
    }

    if (g == 20) { // speaker G released the immediate button
      s = 7;
      speakerStateImmediate[s] = 0;
      subtractSpeakerImmediate(s);
      trafficLights();
      Serial.println("speakerG gets subtracted from the queue");
      printQueue ();
    }
  }
  /////////////////SPEAKER G ////////////  END ///////////

  if (timer < 100) {
    trafficLights();
  }
  if (queue[1] != 0) { // blinking in case someone else is in the queue
    blinkingLights();
  }
}

void blinkingLights() { // blinking behaviour
  if (blinking == 0 && blinkTimer < 2000) { // on phase
    trafficLights();
  }
  else {
    speakerOFF();
    if (blinkTimer > 2500) { // off phase (value - on value)
      blinkTimer = 0;
    }
  }
}

void printQueue () {
  for (int i = 0; i < 16 ; i++) {
    Serial.print(queue[i]); Serial.print(", ");
  }
  Serial.println("");
}

void trafficLights() {
  if (queue[0] == 0) {
    speakerALL();
  }
  if (queue[0] == 1) {
    speakerA();
  }
  if (queue[0] == 2) {
    speakerB();
  }
  if (queue[0] == 3) {
    speakerC();
  }
  if (queue[0] == 4) {
    speakerD();
  }
  if (queue[0] == 5) {
    speakerE();
  }
  if (queue[0] == 6) {
    speakerF();
  }
  if (queue[0] == 7) {
    speakerG();
  }
}

void addSpeakerImmediate(int speaker) { // adding speaker to 2nd position
  if (queue[0] != speaker && queue[1] != speaker) {
    if (queue[0] != 0) {
      for (int i = 15; i > 1; i--) {
        queue[i] = queue[i - 1];
      }
      queue[1] = speaker;
    }
    else {
      queue[0] = speaker;
    }

  }
}

void subtractSpeakerImmediate(int speaker) { // subtract speaker from the queue
  for (int i = 0; i < 15; i++) {
    if (queue[i] == speaker) {
      for (int j = i; j < 15; j++) {
        queue[j] = queue[j + 1];
      }
      break;
    }
  }
}

void addSpeaker(int speaker) { // adding speaker to the queue
  for (int i = 0; i < 15; i++) {
    if (queue[i] == 0) {
      if (queue[i - 1] != speaker) {
        queue[i] = speaker;
      }
      break;
    }
  }
}

void subtractSpeaker(int speaker) { // subtract speaker from the queue
  for (int i = 0; i < 15; i++) {
    if (queue[i] == speaker) {
      for (int j = i; j < 15; j++) {
        queue[j] = queue[j + 1];
      }
      break;
    }
  }
}

void speakerSelect(int speaker) { // select who's turn it is & adding speaker to the queue
  if (queue[0] == speaker) {
    for (int i = 0; i < 15; i++) {
      queue[i] = queue[i + 1];
    }
  }
  else {
    for (int i = 0; i < 16; i++) {
      if (queue[i] == 0) {
        if (queue[i - 1] != speaker) {
          queue[i] = speaker;
        }
        break;
      }
    }
  }
}

void speakerOFF() {

}

void speakerALL() {
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerA() { // this happens when it's speaker A's turn

  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerB() { // this happens when it's speaker B's turn
  digitalWrite(15, LOW);
  digitalWrite(16, HIGH);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerC() { // this happens when it's speaker C's turn
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerD() { // this happens when it's speaker D's turn
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, HIGH);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerE() { // this happens when it's speaker E's turn
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  digitalWrite(20, LOW);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerF() { // this happens when it's speaker F's turn
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, HIGH);
  Serial1.println(0); // no buzz speaker G
  Serial1.flush();
}

void speakerG() { // this happens when it's speaker G's turn
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, LOW);
  Serial1.println(1); // Speaker G wants to talk
  Serial1.flush();
}
