// This is 06-TimersFreeRTOS-450 
// These commands may be used on Lab 1

xTimerCreateStatic() // 1. 

xTimerCreate() // 2.

// Returns a timer handle (TimerHandle_t).
// Prefer to create a static timer (versus a dynamically-created timer) so that the memory required for the timer object is guaranteed to exist.

pdMS_TO_TICKS() 

pdFALSE()
pdTRUE()

StaticTimer_t 

xTimerSetID()

pvTimerGetTimerID() // this is using (void*) 

pvTimerGetTimerID()

xTimerStart()

xTimerReset()

TimerHandle_t
TickType_t

xTimerStart()
xTimerReset()

portMAX_DELAY 

configTIMER_QUEUE_LENGTH

xTimerChangePeriod()

xTimerStop()
