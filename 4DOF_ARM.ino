#include <ESP32Servo.h>

Servo myServo;

const int potPin = 34;   // Potentiometer wiper
const int servoPin = 18; // Servo signal pin

// Buttons
const int recordBtn = 25;
const int playBtn = 26;

const int maxSteps = 500;  // ~10 sec of recording at 20ms intervals
int recordedAngles[maxSteps];
int stepIndex = 0;
bool isRecording = false;
bool isPlaying = false;

void setup() {
  Serial.begin(115200);

  // Allocate PWM timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400);

  pinMode(recordBtn, INPUT_PULLUP);
  pinMode(playBtn, INPUT_PULLUP);

  Serial.println("ESP32 Pot + Servo + Record/Play Ready");
}

void loop() {
  // Start recording if button pressed and not playing
  if (digitalRead(recordBtn) == LOW && !isRecording && !isPlaying) {
    Serial.println("Recording started...");
    stepIndex = 0;
    isRecording = true;
    delay(200); // debounce
  }

  // Start playback if button pressed and we have data recorded
  if (digitalRead(playBtn) == LOW && !isRecording && stepIndex > 0) {
    Serial.println("Playback started...");
    isPlaying = true;
    playMotion();
    isPlaying = false;
    Serial.println("Playback finished.");
    delay(200); // debounce
  }

  // Modes
  if (isRecording) {
    recordMotion();
  } else if (!isPlaying) {
    liveControl();
  }
}

void liveControl() {
  int raw = analogRead(potPin);
  int angle = map(raw, 0, 4095, 0, 180);
  myServo.write(angle);
  delay(20);
}

void recordMotion() {
  int raw = analogRead(potPin);
  int angle = map(raw, 0, 4095, 0, 180);
  myServo.write(angle);

  if (stepIndex < maxSteps) {
    recordedAngles[stepIndex++] = angle;
  }

  if (digitalRead(recordBtn) == HIGH) {
    Serial.print("Recording stopped. Steps recorded: ");
    Serial.println(stepIndex);
    isRecording = false;
  }

  delay(20);
}

void playMotion() {
  for (int i = 0; i < stepIndex; i++) {
    myServo.write(recordedAngles[i]);
    delay(20);
  }
}
