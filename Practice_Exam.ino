
#include <Arduino.h>

// DEFINE LED
#define LED_PIN 23

// DEFINE BUTTONS
#define START_BTN 19
#define STOP_BTN 18

// FREERTOS SETTINGS
#define DISPLAY_LED_PERIOD_MS 500
#define DEBOUNCE_MS 40

// GLOBAL VARIABLES
volatile bool running = false;
volatile bool buttonLocked[2] = {false, false};

uint32_t releaseStart[2] = {0, 0};
const int buttonPins[2] = {START_BTN, STOP_BTN};

// Protect shared running variable
portMUX_TYPE stopwatchMux = portMUX_INITIALIZER_UNLOCKED;

// START INTERRUPT
void ARDUINO_ISR_ATTR startISR() {
  if (buttonLocked[0]) return;
  buttonLocked[0] = true;

  portENTER_CRITICAL_ISR(&stopwatchMux);
  running = true;
  portEXIT_CRITICAL_ISR(&stopwatchMux);
}

// STOP INTERRUPT
void ARDUINO_ISR_ATTR stopISR() {
  if (buttonLocked[1]) return;
  buttonLocked[1] = true;

  portENTER_CRITICAL_ISR(&stopwatchMux);
  running = false;
  portEXIT_CRITICAL_ISR(&stopwatchMux);
}

// BUTTON DEBOUNCE TASK
void Debounce(void *parameter) {
  while (true) {
    uint32_t now = millis();

    for (int i = 0; i < 2; i++) {
      if (!buttonLocked[i]) {
        releaseStart[i] = 0;
        continue;
      }

      if (digitalRead(buttonPins[i]) == HIGH) {
        if (releaseStart[i] == 0) {
          releaseStart[i] = now;
        }

        if (now - releaseStart[i] >= DEBOUNCE_MS) {
          buttonLocked[i] = false;
          releaseStart[i] = 0;
        }
      } else {
        releaseStart[i] = 0;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

// LED BLINKING TASK
void toggleLED(void *parameter) {
  while (true) {
    bool shouldRun;

    portENTER_CRITICAL(&stopwatchMux);
    shouldRun = running;
    portEXIT_CRITICAL(&stopwatchMux);

    if (shouldRun) {
      digitalWrite(LED_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(DISPLAY_LED_PERIOD_MS));

      portENTER_CRITICAL(&stopwatchMux);
      shouldRun = running;
      portEXIT_CRITICAL(&stopwatchMux);

      if (shouldRun) {
        digitalWrite(LED_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(DISPLAY_LED_PERIOD_MS));
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    } else {
      digitalWrite(LED_PIN, LOW);
      vTaskDelay(pdMS_TO_TICKS(10));
    }
  }
}

// SETUP
void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  for (int i = 0; i < 2; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

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

  xTaskCreate(
    toggleLED,
    "LED Task",
    2048,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    Debounce,
    "Debounce Task",
    2048,
    NULL,
    1,
    NULL
  );
}

// MAIN LOOP
void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
