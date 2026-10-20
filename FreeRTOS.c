#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// TASK CREATION
xTaskCreate()                  // Create task
xTaskCreateStatic()            // Static task
xTaskCreatePinnedToCore()      // ESP32 core task
xTaskCreateStaticPinnedToCore()// Static core task

// TASK CONTROL
vTaskDelete()                  // Delete task
vTaskSuspend()                 // Pause task
vTaskResume()                  // Resume task
vTaskPrioritySet()             // Set priority
taskYIELD()                    // Give up CPU
vTaskDelay()                   // Delay task
vTaskDelayUntil()              // Periodic delay

// TASK INFORMATION
xTaskGetCurrentTaskHandle()    // Current handle

// QUEUE CREATION
xQueueCreate()                 // Create queue
xQueueCreateStatic()           // Static queue

// QUEUE OPERATIONS
xQueueSendToBack()             // Add to back
xQueueSendToFront()            // Add to front
xQueueReceive()                // Read and remove
xQueuePeek()                   // Read without removal
xQueueOverwrite()              // Replace mailbox item

// QUEUE MANAGEMENT
vQueueDelete()                 // Delete queue
xQueueReset()                  // Empty queue
uxQueueMessagesWaiting()       // Count items
uxQueueSpacesAvailable()       // Count free spaces

// INTERRUPT QUEUE OPERATIONS
xQueueSendToBackFromISR()      // Send from ISR
xQueueReceiveFromISR()         // Receive from ISR
// TIMER CREATION
xTimerCreate()          // Create dynamic timer
xTimerCreateStatic()    // Create static timer

// TIMER CONTROL
xTimerStart()           // Start timer
xTimerStop()            // Stop timer
xTimerReset()           // Restart countdown
xTimerChangePeriod()    // Change timer interval
xTimerDelete()          // Delete timer

// TIMER INFORMATION
vTimerSetTimerID()      // Set timer ID
pvTimerGetTimerID()     // Get timer ID
xTimerIsTimerActive()   // Check timer status
xTimerGetPeriod()       // Get timer period
xTimerGetExpiryTime()   // Get expiry tick
pcTimerGetName()        // Get timer name

// TIME CONVERSION
pdMS_TO_TICKS()         // Milliseconds to ticks

// TASK TIMING
vTaskDelay()            // Delay a task
vTaskDelayUntil()       // Periodic task delay
xTaskGetTickCount()     // Current tick count
