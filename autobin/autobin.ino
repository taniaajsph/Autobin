#include <reg51.h>

/* ========= Pin Assignments ========= */

// Ultrasonic Sensor 1 – hand/object detection
sbit trig1 = P2^0;
sbit echo1 = P2^1;

// Ultrasonic Sensor 2 – waste level monitoring
sbit trig2 = P1^4;
sbit echo2 = P1^5;

// Motor driver control (L293D)
sbit motor1 = P2^4;  // Lid open direction
sbit motor2 = P2^5;  // Lid close direction

// RGB LED indicators (common cathode)
sbit redLED    = P1^0;  // Full bin alert
sbit yellowLED = P1^2;  // Moderate fill
sbit greenLED  = P1^1;  // Low fill

/* ========= Utility Functions ========= */

// Simple delay (~1ms per unit at 12MHz)
void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1275; j++);
}

/* Measure distance from Ultrasonic Sensor 1 (cm) */
unsigned int measureDistance1() {
    unsigned int time = 0;

    trig1 = 1; delay(1); trig1 = 0;
    while (!echo1); // wait for echo start
    while (echo1 && time < 30000) time++;

    return time / 58; // convert to cm
}

/* Measure distance from Ultrasonic Sensor 2 (cm) */
unsigned int measureDistance2() {
    unsigned int time = 0;

    trig2 = 1; delay(1); trig2 = 0;
    while (!echo2); // wait for echo start
    while (echo2 && time < 30000) time++;

    return time / 58; // convert to cm
}

/* ========= Main Control Loop ========= */

void main() {
    unsigned int distance1, distance2;
    bit lidOpen = 0;  // 0 = closed, 1 = open

    // Initial states
    trig1 = trig2 = 0;
    motor1 = motor2 = 0;
    redLED = yellowLED = 0;
    greenLED = 1;

    while (1) {
        // For simulation testing — replace with actual ultrasonic reads
        // distance1 = measureDistance1();
        // distance2 = measureDistance2();
        distance1 = 15;  // Simulated hand distance
        distance2 = 5;   // Simulated waste level

        /* Lid control — open if hand detected and lid is closed */
        if (distance1 > 0 && distance1 <= 20 && !lidOpen) {
            motor1 = 1; motor2 = 0;     // open lid
            delay(1000);
            motor1 = 0;
            lidOpen = 1;

            delay(2000);                // wait before closing
            motor2 = 1; delay(1000);    // close lid
            motor2 = 0;
            lidOpen = 0;
        }

        /* Waste level indication via RGB LED */
        if (distance2 > 30) {           // Low fill
            redLED = 0; yellowLED = 0; greenLED = 1;
        } 
        else if (distance2 > 10) {      // Moderate fill
            redLED = 0; yellowLED = 1; greenLED = 0;
        } 
        else {                          // Full bin
            redLED = 1; yellowLED = 0; greenLED = 0;
        }
    }
}
