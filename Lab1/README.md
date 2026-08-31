EGEC 450 Lab 1: Introduction to Embedded C and FreeRTOS
Table of Contents
1. Assignment Value, Submission, and Academic Integrity/Intellectual Property Reminders
2. Objectives
3. Lab Description
3.1. Install and initialize the Arduino IDE
3.2. Examining BasicMultiThreading.ino
4. Recommended Schedule of Work
5. Lab Questions
1. Assignment Value, Submission, and Academic Integrity/Intellectual Property Reminders
3 points possible

Submit via Canvas by 11:59 PM on Wednesday, September 9, 2026. To receive credit, this assignment and all code must be typed and submitted via Canvas using the following template.

You may not distribute/post this assignment without written permission from Dr. Mike Turi, Electrical and Computer Engineering Department, California State University, Fullerton.

You may discuss this assignment with others, but this assignment must be completed individually by you. Completing this assignment with a group of students and turning in copies of group work is not permitted.

Recall that intellectual property infringement and academic dishonesty will not be tolerated. By submitting this assignment, you understand penalties will be assessed if you submit work for credit that is not your own.

2. Objectives
Objectives:
Gain experience with Arduino IDE.
Learn how to read and modify embedded C code.
3. Lab Description
All software in this lab must be developed in C. You will examine a sample program, written in embedded C, which uses FreeRTOS.

3.1. Install and initialize the Arduino IDE
First, download and install Arduino IDE. Then select the "Boards Manager," either from the "Tools" menu or the sidebar on the left, and search for "Espressif." Then install "esp32 by Espressif Systems."

Next, open the example code from the following menu:

File –> Examples –> ESP32 –> FreeRTOS –> BasicMultiThreading

Carefully examine this code and the associated README.md. Before you can upload and run this code, you must select a board and port. In this course, select "ESP32 Dev Module" as your board and select the USB port where you have connected your board.

3.2. Examining BasicMultiThreading.ino
Carefully examine and test BasicMultiThreading.ino. I also encourage you to carefully read the associated README.md. Complete the lab questions below.

4. Recommended Schedule of Work
Week of August 31: Install Arduino IDE and experiment with BasicMultiThreading.ino.
Week of September 7: Complete the lab questions and submit this assignment; this is due on Wednesday, September 9 by 11:59 PM.
5. Lab Questions
Complete the questions below; you must use the following template and submit your assignment on Canvas to receive credit.

For each question, use IEEE-style citations 1 to reference and show where you used information from all sources, websites, AI, and students consulted.

(1 point possible) In your own words, explain the operation of the initial program, BasicMultiThreading.ino. What are the two threads doing?
(1 point possible) How often does the LED blink (e.g., the LED blinks once per second, twice per second, etc.)? What integer value must you use for the delay to cause the LED to blink once every two seconds?
(1 point possible) How often is the analog value printed to the serial monitor (e.g., printed once every 10 ms, 100 ms, etc.)? Provide some sample values read from the analog pin.
Footnotes:
1 IEEE, "Reference Guide," ieee.org, Accessed: Aug. 18, 2025. [Online]. Available: https://journals.ieeeauthorcenter.ieee.org/wp-content/uploads/sites/7/IEEE_Reference_Guide.pdf
Author: Dr. Mike Turi, Electrical and Computer Engineering Department, California State University, Fullerton

Created: 2026-08-28 Fri 10:32

Validate
