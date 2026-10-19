
#include <Arduino.h>
#include <SPI.h>

// =====================================================
// EGEC 450 - FREERTOS STOPWATCH
// Four-digit seven-segment display
// 74HC595 shift register + 2N2222 transistors
// =====================================================

// SHIFT REGISTER PINS
#define DATA_PIN 23
#define CLOCK_PIN 18
#define LATCH_PIN 19

// DIGIT CONTROL PINS
#define D1_PIN 13
#define D2_PIN 14
#define D3_PIN 16
#define D4_PIN 17

// BUTTON PINS
#define START_BTN 32
#define STOP_BTN 33
#define INC_BTN 25
#define RESET_BTN 26

// FREERTOS SETTINGS
#define STOPWATCH_PERIOD_US 1000
#define DISPLAY_PERIOD_US 1000
#define DEBOUNCE_MS 40

// =====================================================
// GLOBAL VARIABLES
// =====================================================

// Stopwatch range: 0 to 9999 milliseconds
volatile uint16_t totalMilliseconds = 0;

// false = stopped, true = running
volatile bool running = false;

// Protect shared stopwatch variables
portMUX_TYPE stopwatchMux = portMUX_INITIALIZER_UNLOCKED;

// Button interrupt lockout
volatile bool buttonLocked[4] = {
  false, false, false, false
};

// Button release debounce
uint32_t releaseStart[4] = {
  0, 0, 0, 0
};

// Digit GPIO array
const int digitPins[4] = {
  D1_PIN, D2_PIN, D3_PIN, D4_PIN
};

// Button GPIO array
const int buttonPins[4] = {
  START_BTN, STOP_BTN, INC_BTN, RESET_BTN
};

// Common-cathode segment patterns
// Q0=A, Q1=B, Q2=C, Q3=D
// Q4=E, Q5=F, Q6=G, Q7=DP
const uint8_t numbers[10] = {
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

// FreeRTOS task handles
TaskHandle_t stopwatchTaskHandle = NULL;
TaskHandle_t displayTaskHandle = NULL;

// ESP32 FreeRTOS software timers
TimerHandle_t stopwatchTimer = NULL;

// =====================================================
// BUTTON INTERRUPT SERVICE ROUTINES
// =====================================================

// START
void ARDUINO_ISR_ATTR startISR() {

  if (buttonLocked[0]) return;

  buttonLocked[0] = true;

  portENTER_CRITICAL_ISR(&stopwatchMux);

  if (!running) {
    running = true;
  }

  portEXIT_CRITICAL_ISR(&stopwatchMux);
}

// STOP
void ARDUINO_ISR_ATTR stopISR() {

  if (buttonLocked[1]) return;

  buttonLocked[1] = true;

  portENTER_CRITICAL_ISR(&stopwatchMux);

  if (running) {
    running = false;
  }

  portEXIT_CRITICAL_ISR(&stopwatchMux);
}

// INCREMENT
void ARDUINO_ISR_ATTR incrementISR() {

  if (buttonLocked[2]) return;

  buttonLocked[2] = true;

  portENTER_CRITICAL_ISR(&stopwatchMux);

  if (!running) {
    totalMilliseconds =
      (totalMilliseconds + 1) % 10000;
  }

  portEXIT_CRITICAL_ISR(&stopwatchMux);
}

// RESET
void ARDUINO_ISR_ATTR resetISR() {

  if (buttonLocked[3]) return;

  buttonLocked[3] = true;

  portENTER_CRITICAL_ISR(&stopwatchMux);

  running = false;
  totalMilliseconds = 0;

  portEXIT_CRITICAL_ISR(&stopwatchMux);
}

// =====================================================
// FREERTOS STOPWATCH TIMER CALLBACK
// =====================================================

void stopwatchTimerCallback(TimerHandle_t timer) {

  portENTER_CRITICAL(&stopwatchMux);

  if (running) {

    totalMilliseconds++;

    if (totalMilliseconds >= 10000) {
      totalMilliseconds = 0;
    }
  }

  portEXIT_CRITICAL(&stopwatchMux);
}

// =====================================================
// SEVEN-SEGMENT DEVICE DRIVER
// =====================================================

// Send one byte to 74HC595 using hardware SPI
void sendSegments(uint8_t pattern) {

  digitalWrite(LATCH_PIN, LOW);

  SPI.transfer(pattern);

  digitalWrite(LATCH_PIN, HIGH);
}

// Turn OFF all four digit transistors
void disableDigits() {

  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);
  }
}

// Refresh one digit
void refreshDisplay() {

  static uint8_t currentDigit = 0;

  uint16_t value;

  portENTER_CRITICAL(&stopwatchMux);
  value = totalMilliseconds;
  portEXIT_CRITICAL(&stopwatchMux);

  // S.mmm format
  uint8_t digits[4] = {
    (uint8_t)(value / 1000),
    (uint8_t)((value / 100) % 10),
    (uint8_t)((value / 10) % 10),
    (uint8_t)(value % 10)
  };

  // Turn off digits before changing segments
  disableDigits();

  uint8_t pattern = numbers[digits[currentDigit]];

  // Decimal point after seconds digit
  if (currentDigit == 0) {
    pattern |= 0b10000000;
  }

  // Send number through shift register
  sendSegments(pattern);

  // Activate selected transistor
  digitalWrite(digitPins[currentDigit], HIGH);

  // Select next digit
  currentDigit++;

  if (currentDigit >= 4) {
    currentDigit = 0;
  }
}

// =====================================================
// FREERTOS DISPLAY TASK
// =====================================================

void displayTask(void *parameter) {

  TickType_t lastWakeTime = xTaskGetTickCount();

  while (true) {

    refreshDisplay();

    // Approximately 1 ms per digit if RTOS tick = 1 ms
    vTaskDelayUntil(
      &lastWakeTime,
      pdMS_TO_TICKS(1)
    );
  }
}

// =====================================================
// FREERTOS BUTTON DEBOUNCE TASK
// =====================================================

void buttonTask(void *parameter) {

  while (true) {

    uint32_t now = millis();

    for (int i = 0; i < 4; i++) {

      if (!buttonLocked[i]) {
        releaseStart[i] = 0;
        continue;
      }

      // HIGH means button released
      if (digitalRead(buttonPins[i]) == HIGH) {

        if (releaseStart[i] == 0) {
          releaseStart[i] = now;
        }

        if (now - releaseStart[i] >= DEBOUNCE_MS) {

          buttonLocked[i] = false;
          releaseStart[i] = 0;
        }
      }
      else {
        releaseStart[i] = 0;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // Shift register
  pinMode(LATCH_PIN, OUTPUT);
  digitalWrite(LATCH_PIN, HIGH);

  // Digit transistor GPIOs
  for (int i = 0; i < 4; i++) {

    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);
  }

  // Button GPIOs
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Hardware SPI
  SPI.begin(CLOCK_PIN, -1, DATA_PIN, -1);

  sendSegments(0);

  // Attach GPIO interrupts
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

  // Create FreeRTOS software timer
  stopwatchTimer = xTimerCreate(
    "StopwatchTimer",
    pdMS_TO_TICKS(1),
    pdTRUE,
    NULL,
    stopwatchTimerCallback
  );

  if (stopwatchTimer == NULL) {
    Serial.println("Timer creation failed");
    return;
  }

  if (xTimerStart(stopwatchTimer, 0) != pdPASS) {
    Serial.println("Timer start failed");
    return;
  }

  // Display multiplexing task
  xTaskCreate(
    displayTask,
    "DisplayTask",
    4096,
    NULL,
    2,
    &displayTaskHandle
  );

  // Button debounce task
  xTaskCreate(
    buttonTask,
    "ButtonTask",
    2048,
    NULL,
    1,
    NULL
  );

  Serial.println("FreeRTOS stopwatch ready!");
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // Tasks and software timer handle the system.
  vTaskDelay(pdMS_TO_TICKS(1000));
}
