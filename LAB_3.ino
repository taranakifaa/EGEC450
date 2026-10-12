
#include <Arduino.h>
#include "esp_timer.h"

#define DATA_PIN 23
#define CLOCK_PIN 18
#define LATCH_PIN 19

// Transistor base GPIO pins
#define D1_PIN 13
#define D2_PIN 14
#define D3_PIN 16
#define D4_PIN 17

// Button GPIO pins
#define START_BTN 32
#define STOP_BTN 33
#define INC_BTN 25
#define RESET_BTN 26

const int digitPins[4] = {
  D1_PIN, D2_PIN, D3_PIN, D4_PIN
};

const int buttonPins[4] = {
  START_BTN, STOP_BTN, INC_BTN, RESET_BTN
};

// Common-cathode seven-segment patterns
// Q0=A, Q1=B, Q2=C, Q3=D
// Q4=E, Q5=F, Q6=G, Q7=DP
const byte numbers[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Shared stopwatch variables
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint16_t totalMilliseconds = 0;
volatile bool running = false;

// Button interrupt events
volatile bool startEvent = false;
volatile bool stopEvent = false;
volatile bool incrementEvent = false;
volatile bool resetEvent = false;

// Prevent repeated interrupts while held
volatile bool buttonLocked[4] = {
  false, false, false, false
};

// Track stable button releases
unsigned long releaseStart[4] = {
  0, 0, 0, 0
};

const unsigned long debounceMs = 40;

// Stopwatch timer
esp_timer_handle_t stopwatchTimer;

// Display multiplexing
int currentDigit = 0;
unsigned long lastRefresh = 0;

// ------------------------------------------------
// BUTTON INTERRUPTS
// ------------------------------------------------

void ARDUINO_ISR_ATTR startISR() {
  if (!buttonLocked[0]) {
    buttonLocked[0] = true;
    startEvent = true;
  }
}

void ARDUINO_ISR_ATTR stopISR() {
  if (!buttonLocked[1]) {
    buttonLocked[1] = true;
    stopEvent = true;
  }
}

void ARDUINO_ISR_ATTR incrementISR() {
  if (!buttonLocked[2]) {
    buttonLocked[2] = true;
    incrementEvent = true;
  }
}

void ARDUINO_ISR_ATTR resetISR() {
  if (!buttonLocked[3]) {
    buttonLocked[3] = true;
    resetEvent = true;
  }
}

// ------------------------------------------------
// STOPWATCH TIMER CALLBACK
// Runs every 1 millisecond
// ------------------------------------------------

void stopwatchCallback(void *arg) {
  portENTER_CRITICAL(&timerMux);

  if (running) {
    totalMilliseconds++;

    if (totalMilliseconds >= 10000) {
      totalMilliseconds = 0;
    }
  }

  portEXIT_CRITICAL(&timerMux);
}

// ------------------------------------------------
// SHIFT REGISTER
// ------------------------------------------------

void sendSegments(byte pattern) {
  digitalWrite(LATCH_PIN, LOW);

  shiftOut(
    DATA_PIN,
    CLOCK_PIN,
    MSBFIRST,
    pattern
  );

  digitalWrite(LATCH_PIN, HIGH);
}

// ------------------------------------------------
// TURN OFF ALL FOUR DIGITS
// ------------------------------------------------

void disableDigits() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);
  }
}

// ------------------------------------------------
// MULTIPLEX FOUR-DIGIT DISPLAY
// Format: S.mmm
// ------------------------------------------------

void refreshDisplay() {
  unsigned long now = micros();

  // Refresh one digit every 1000 us
  if (now - lastRefresh < 1000) {
    return;
  }

  lastRefresh = now;

  uint16_t value;

  portENTER_CRITICAL(&timerMux);
  value = totalMilliseconds;
  portEXIT_CRITICAL(&timerMux);

  int digits[4] = {
    value / 1000,
    (value / 100) % 10,
    (value / 10) % 10,
    value % 10
  };

  // Prevent ghosting
  disableDigits();

  byte pattern = numbers[digits[currentDigit]];

  // Decimal point after first digit
  if (currentDigit == 0) {
    pattern |= 0b10000000;
  }

  sendSegments(pattern);

  // Enable only the selected digit
  digitalWrite(digitPins[currentDigit], HIGH);

  currentDigit++;

  if (currentDigit >= 4) {
    currentDigit = 0;
  }
}

// ------------------------------------------------
// BUTTON RELEASE DEBOUNCING
// One press = one event
// ------------------------------------------------

void checkButtonReleases() {
  unsigned long now = millis();

  for (int i = 0; i < 4; i++) {

    if (!buttonLocked[i]) {
      releaseStart[i] = 0;
      continue;
    }

    // HIGH means released (INPUT_PULLUP)
    if (digitalRead(buttonPins[i]) == HIGH) {

      if (releaseStart[i] == 0) {
        releaseStart[i] = now;
      }

      // Require stable release for 40 ms
      if (now - releaseStart[i] >= debounceMs) {
        buttonLocked[i] = false;
        releaseStart[i] = 0;
      }
    }
    else {
      // Still pressed
      releaseStart[i] = 0;
    }
  }
}

// ------------------------------------------------
// PROCESS BUTTON EVENTS
// ------------------------------------------------

void processButtons() {
  bool startPressed;
  bool stopPressed;
  bool incrementPressed;
  bool resetPressed;

  // Copy and clear pending events atomically
  noInterrupts();

  startPressed = startEvent;
  stopPressed = stopEvent;
  incrementPressed = incrementEvent;
  resetPressed = resetEvent;

  startEvent = false;
  stopEvent = false;
  incrementEvent = false;
  resetEvent = false;

  interrupts();

  portENTER_CRITICAL(&timerMux);

  // Reset has highest priority
  if (resetPressed) {
    running = false;
    totalMilliseconds = 0;
  }
  else {
    if (stopPressed) {
      running = false;
    }

    if (incrementPressed && !running) {
      totalMilliseconds =
        (totalMilliseconds + 1) % 10000;
    }

    if (startPressed) {
      running = true;
    }
  }

  portEXIT_CRITICAL(&timerMux);
}

// ------------------------------------------------
// SETUP
// ------------------------------------------------

void setup() {
  Serial.begin(115200);

  // Shift register pins
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  // Digit transistor pins
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);
  }

  // Button pins
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  sendSegments(0);

  // Button interrupts
  attachInterrupt(
    digitalPinToInterrupt(START_BTN),
    startISR,
    FALLING
  );

  attachInterrupt(
    digitalPinToInterrupt(STOP_BTN),
    stopISR,
    FALLING
  );

  attachInterrupt(
    digitalPinToInterrupt(INC_BTN),
    incrementISR,
    FALLING
  );

  attachInterrupt(
    digitalPinToInterrupt(RESET_BTN),
    resetISR,
    FALLING
  );

  // Configure 1 ms stopwatch timer
  esp_timer_create_args_t timerArgs = {};
  timerArgs.callback = &stopwatchCallback;
  timerArgs.name = "stopwatch";

  esp_err_t err = esp_timer_create(
    &timerArgs,
    &stopwatchTimer
  );

  if (err != ESP_OK) {
    Serial.println("Timer creation failed");
    return;
  }

  err = esp_timer_start_periodic(
    stopwatchTimer,
    1000
  );

  if (err != ESP_OK) {
    Serial.println("Timer start failed");
    return;
  }

  Serial.println("Stopwatch ready");
}

// ------------------------------------------------
// MAIN LOOP
// ------------------------------------------------

void loop() {
  refreshDisplay();

  processButtons();

  checkButtonReleases();
}
