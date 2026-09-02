## 2. Real-Time Operating System (RTOS)
# 2.1. Need for a RTOS
- Could create a program to handle I/O for sensors and actuators.
* The program may be complex if interfacing with many I/O.
- Would likely be simpler to split this program into independently executing subprograms.
* Can run each of these as a task in a RTOS.
* Tasks are scheduled to run; e.g., round-robin scheduler.
* An important or high-priority task can preempt/interrupt a lower-priority task.
This is preemptive scheduling.

- A periodic timer at some known interval

## 2.2. Real-time definitions
- Real-time and Hard Real-time:
* System with small and bounded interface latency; the time difference between a request and its service.
* We will focus on these systems; these use RTOSes.
- Soft Real-time:
* System with priority.
* E.g., Windows, Mac OS, Unix/Linux, etc.
- Not Real-time:
Does not guarantee when tasks will actually be run.

## 2.3. Time jitter
- In a real-time system, latency must be small and bounded.
- Time jitter (δt) is the difference between when a task is supposed to be run, and when it is actually run.
* If tn is the time the task is actually run and nΔt is the time it was supposed to be run (assume Δ=1/f, the period of a periodic task), then:
The time-jitter at sample n is: δtn = tn - nΔt
Or, it can be important to control the time difference between periodic events.
If Δtn is the actual time difference between two events and if Δt is the desired time, then:
The time-jitter at sample n is: δtn = Δtn - Δt
A real-time system with periodic tasks must be able to place an upper bound, k, on the time-jitter:
-k ≤ δtn ≤ +k for all n
