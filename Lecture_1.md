## 2. Embedded Systems
These are Everywhere 
- Hidden Computers that preform tasks/ designated purpose

2.2. Microprocessor
- Intel: 4004, ..8080, ..x86
Freescale: 6800
ARM, DEC,SPARC, MIPS, PowerPC, National Semiconductor 

2.3 Microcontroller: Processor + Memory + I/O Port (interfaces)
- Processors = Instruction Set + Memory + Accelerators
Memory
*Non-Volatile 
- ROM
-EEPROM, EPROM 
Volatile
- RAM(DRAM, SRAM)
Interfaces: 
- Hardware: Ports
- Software: Device Driver
- Parallel(MULTIPLE BITS), Serial (Cheaper, less wires (ONE BIT)), Analog
I/O
- Memory-mapped vs. I/O-instructions (I/O-mapped) 

## 3. Reactive vs. Real-Time Systems 

3.1  A ***reactive system*** continuously...

- Accepts inputs
- Preform calculations
- Generates outputs
- Interacts with the physical environments

3.2 A ***real-time*** system ...

- Does everything a reactive system does, but also...
- Specifies an upper bound on the time required to perform the input/calculation/output in reaction to external events

## 4. Product Life Cycle 
- 4.1. Analysis (What is the problem?)
Translate requirements into specifications.
- 4.2. Design (How do we solve the problem?)
Translate specifications into the engineering design.
High-level design; design block diagrams, algorithms, data structures, interfacing, …
- 4.3. Development/Implementation (Implement the design)
- 4.4. Testing (Does it work? How well does it work?)\n
Test both the hardware and software.
Validation testing: Testing for correctness.
Performance testing: Testing for efficiency.
- 4.5. Deployment and Maintenance (Monitor in the field)
Ensure the product operates correctly.
Provide maintenance and improvements.

## 5. Full Design Process Example
**Conduct market survey, profit estimate.**
**Determine overall function, specifications.**
**Create data flow chart (test it).**
**Create flowchart (test it).**
**Create software (test it).**
**Create simulation, prototype (test it).**
-**Build it (test it).**

## 6. Software Design Process Example
Create a function table (pin X input, pin Y output).
Determine how to test it (switch input, LED output).
Create a data flow graph.
Create a flow chart.
Write pseudocode.
Write source code or assembly.
Simulate it.
Test it on the hardware.

## 7. Common Algorithm Constructs
7.1. **Sequential**
Perform one task after another in a sequence.
7.2. Conditional (If-Then-Else)
Make a decision out of two choices.
Iterate for multiple decisions.
7.3. Iterative (Loop)
Repeat until condition is satisfied.
For and while loops check condition at the beginning of the loop.
May iterate 0, 1, multiple, or many times.
do-while loops check condition at the end of the loop.
Always runs at least once.
May iterate 1, multiple, or many times.

## 8. Running in "Parallel"
8.1. **Parallel Programming**
Allows the processor to execute multiple threads at the same time.
create or fork: 2+ threads will be executed in parallel.
join: 2+ threads will be combined into one.
8.2. **Concurrent Programming**
Allows the processor to execute multiple threads but only one at a time.
E.g., interrupts, running multiple threads on a single-core processor, etc.
8.3. **Distributed Programming**
Complex system where each processor runs its own software as part of a larger task/application.

## 9. System Design
9.1. **Questions to consider when creating the design.**
What does being in a state mean?
List state parameters.
What is the starting state of the system?
Define the initial state.
What information do we need to collect?
List the input data.
What information do we need to generate?
List the output data.
How do we move from one state to another?
Determine the actions we must do.
What is the desired ending state?
Define the ultimate goal.
9.2. **Decomposition or Successive Refinement**
Start with a task and decompose the task into a set of simpler subtasks.
Subtasks are decomposed into even simpler sub-subtasks.
Each subtask is simpler than the task itself.
Make design decisions
Document decisions and subtask requirements.
Ultimately, subtask is so simple, it can be converted to software.
9.3. **Four building blocks:**
**Sequential:**
do A then do B
do A and B in either order (parallel)
**Conditional:**
if A, then do B
if A, then do B, else do C
**Iterative:**
for each A, do B
do A until B
repeat A over and over, forever (condition always true)
**Interrupt:**
on external event do B
every t msec do B

10. ## Debugging (a.k.a., Testing, Diagnostics, Verification)
10.1. **Debugging Actions**
Functional debugging
Check I/O values.
Performance debugging
Check I/O values with time.
Tracing
Measure sequence of operations.
Profiling
Measure percentage for tasks.
Time relationship between tasks.
Performance measurement
How fast it executes.
10.2. Optimization: Make trade-offs for overall good
Improve speed
Improve accuracy
Reduce memory
Reduce power
Reduce size
Reduce cost
10.3. Typical Debugging Aids
Breakpoints
Single Step, Step Over, Step Out, Run, Run to Cursor, etc.
Viewing Registers
Memory and Watch Windows
Profiling
Plotting
10.4. Instrumentation
Code we add to the system that aids in debugging.
E.g., print statements.
Good practice
Define instruments with specific pattern in their names.
Use instruments that test a run time global flag.
Leaves a permanent copy of the debugging code.
Causes it to suffer a runtime overhead.
Simplifies "on-site" customer support.
Use conditional compilation or conditional assembly (if available).
Easy to remove all instruments.
10.5. Visualization
How the debugging information is displayed.
10.6. Debugging intrusiveness
Intrusive debugging
Degree of perturbation caused by the debugging itself.
How much the debugging slows down execution.
Non-intrusive debugging
Characteristic or quality of a debugger.
Allows system to operate as if debugger did not exist.
E.g., logic analyzer, JTAG.
Minimally intrusive
Negligible effect on the system being debugged.
E.g., dumps (scan point), monitors.
Highly intrusive
Print statements, breakpoints, and single-stepping.

## ---------------------------------------------------------------------------------------

reference for C vs C++ and Embedded C(file:///C:/Users/taraf/Downloads/02-CvsCpp-450.html)

