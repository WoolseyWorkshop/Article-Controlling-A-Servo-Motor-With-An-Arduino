/**
 * @mainpage Arduino Servo Motor Project
 *
 * @section description_main Description
 * An Arduino sketch that controls a servo motor.
 *
 * Includes routines for demonstrating different ways you can control your
 * servo, such as sweeping the servo through given angles and setting the
 * servo's position based on user input.
 *
 * @section circuit_main Circuit
 * - A servo motor's signal wire is connected to pin D9.
 *
 * @section notes_main Notes
 * - Use the Serial Monitor to view printed output.
 * - Use the Serial Monitor with the "No Line Ending" setting to input values.
 *
 * Copyright (c) 2023 Woolsey Workshop.  All rights reserved.
 */


/**
 * @file Servo_Basic.ino
 *
 * @brief The primary Arduino sketch implementation file.
 *
 * @section description_servo_basic_ino Description
 * The primary Arduino sketch implementation file.
 *
 * @section libraries_servo_basic_ino Libraries
 * - Servo Library (https://www.arduino.cc/reference/en/libraries/servo/)
 *   - Provides the ability to control a variety of servo motors.
 *
 * @section notes_servo_basic_ino Notes
 * - Comments are Doxygen compatible.
 *
 * @section todo_servo_basic_ino TODO
 * - None.
 *
 * @section author_servo_basic_ino Author(s)
 * - Created by John Woolsey on 01/31/2023.
 * - Modified by John Woolsey on 02/12/2023.
 *
 * Copyright (c) 2023 Woolsey Workshop.  All rights reserved.
 */


// Includes
#include <Servo.h>


// Defines
#define DEBUG 1                               ///< The mode of operation; 0 = normal, 1 = debug.
#define SERVO_A_0_DEGREES_PULSE_WIDTH 1000    ///< The 0 degrees pulse width in microseconds for servo A.
#define SERVO_A_180_DEGREES_PULSE_WIDTH 2000  ///< The 180 degrees pulse width in microseconds for servo A.


// Pin Mapping
uint8_t ServoA = 9;  ///< The pin connected to the signal wire of servo A.


// Global Instances
Servo servoA;  ///< The servo A instance.


/**
 * The standard Arduino setup function used for setup and configuration tasks.
 */
void setup() {
   // Serial Monitor
   Serial.begin(9600);  // initialize serial port
   while (!Serial);     // wait for serial connection

   // Servo configuration
   // servoA.attach(ServoA);  // connect and initialize servo A with default minimum (544) and maximum (2400) pulse widths
   // servoA.attach(ServoA, 1000, 2000);  // connect and initialize servo A with conservative minimum and maximum pulse widths
   servoA.attach(ServoA, SERVO_A_0_DEGREES_PULSE_WIDTH, SERVO_A_180_DEGREES_PULSE_WIDTH);  // connect and initialize servo A with specified minimum and maximum pulse widths
}


/**
 * The standard Arduino loop function used for repeating tasks.
 */
void loop() {
   // basicOperations();   // demonstrates basic servo operation
   userInputOperations();  // demonstrates setting of servo positions from user input
   // sweepOperations();   // demonstrates servo sweeping operations
}


/**
 * Demonstrates the basic operations of servo motors.
 */
void basicOperations() {
   servoA.write(90);   // center position
   delay(5000);
   servoA.write(0);    // farthest position on one side
   delay(5000);
   servoA.write(90);   // center position
   delay(5000);
   servoA.write(180);  // farthest position on the other side
   delay(5000);
}


/**
 * Demonstrates the setting of individual servo positions based on user input.
 *
 * Individual servo positions (angles) are entered via the Serial Monitor.
 * The Serial Monitor's "No Line Ending" setting is required for proper usage.
 *
 * Performs appropriate error checking of input values.
 *
 * Prints debugging information if DEBUG is set.
 */
void userInputOperations() {
   while (Serial.available()) {  // check if serial data is available for parsing
      int angle = Serial.parseInt();  // read angle value from Serial Monitor

      // Error checking of input values
      if (angle < 0 || angle > 180) {  // check angle limits
         Serial.print(F("ERROR: The angle value of "));
         Serial.print(angle);
         Serial.println(F(" is out of range."));
         return;
      }

      // Show operation description
      if (DEBUG) {
         Serial.print(F("Setting angle to "));
         Serial.print(angle);
         Serial.println(F(" degrees."));
      }

      // Perform operation
      servoA.write(angle);  // library enforces 0-180 degree safeguards
   }
}


/**
 * Sweeps the servo from one position (angle) to another.
 *
 * Performs appropriate error checking of input values.
 *
 * Prints debugging information if DEBUG is set.
 *
 * @param startAngle  The value of the starting angle, 0-180 degrees.
 * @param stopAngle   The value of the stopping angle, 0-180 degrees.
 * @param stepAngle   The value of the stepping angle, 1-180 degrees; defaults to 1.
 * @param stepTime    The value of the stepping time in milliseconds; defaults to 15.
 */
void servoSweep(uint8_t startAngle, uint8_t stopAngle, uint8_t stepAngle = 1, unsigned long stepTime = 15) {
   // Error checking of input values
   if (startAngle > 180) {  // check startAngle limits
      Serial.print(F("ERROR: The startAngle value of "));
      Serial.print(startAngle);
      Serial.println(F(" is out of range."));
      return;
   }
   if (stopAngle > 180) {  // check stopAngle limits
      Serial.print(F("ERROR: The stopAngle value of "));
      Serial.print(stopAngle);
      Serial.println(F(" is out of range."));
      return;
   }
   if (stepAngle < 1 || stepAngle > abs(stopAngle - startAngle)) {  // check stepAngle limits
      Serial.print(F("ERROR: The stepAngle value of "));
      Serial.print(stepAngle);
      Serial.println(F(" is out of range."));
      return;
   }

   // Show operation description
   if (DEBUG) {
      Serial.print(F("Sweeping angle from "));
      Serial.print(startAngle);
      Serial.print(F(" to "));
      Serial.print(stopAngle);
      Serial.print(F(" degrees in increments of "));
      Serial.print(stepAngle);
      Serial.print(F(" degree(s) with a "));
      Serial.print(stepTime);
      Serial.println(F(" ms step time."));
   }

   // Perform operation
   if (startAngle < stopAngle) {  // increasing angle
      for (int angle = startAngle; angle <= stopAngle; angle += stepAngle) {
         if (DEBUG) {
            Serial.print(F("Setting angle to "));
            Serial.print(angle);
            Serial.println(F(" degrees."));
         }
         servoA.write(angle);  // library enforces 0-180 degree safeguards
         delay(stepTime);
      }
   } else {  // decreasing angle
      for (int angle = startAngle; angle >= stopAngle; angle -= stepAngle) {
         if (DEBUG) {
            Serial.print(F("Setting angle to "));
            Serial.print(angle);
            Serial.println(F(" degrees."));
         }
         servoA.write(angle);  // library enforces 0-180 degree safeguards
         delay(stepTime);
      }
   }
}


/**
 * Demonstrates a variety of servo sweeping operations.
 */
void sweepOperations() {
   servoSweep(0, 180);             // sweep from 0 to 180 in 1 degree (default) increments with 15 ms (default) delays in between
   delay(5000);
   servoSweep(180, 0);             // sweep from 180 to 0 in 1 degree (default) increments with 15 ms (default) delays in between
   delay(5000);
   servoSweep(45, 135, 15, 1000);  // sweep from 45 to 135 in 15 degree increments with 1 second delays in between
   delay(5000);
   servoSweep(180, 0, 45, 1000);   // sweep from 180 to 0 in 45 degree increments with 1 second delays in between
   delay(5000);
}
