int inches = 0;
int cm = 0;

const int trigPinHand = 9;    // hand position ultrasonic sensor Trig
const int echoPinHand = 10;   // hand position ultrasonic sensor Echo
const int trigPinBall = 4;    // ball position ultrasonic sensor Trig
const int echoPinBall = 7;    // ball position ultrasonic sensor Echo
const int fanPin = 3;         // PWM output for motor control


long readUltrasonicDistance(int triggerPin, int echoPin) {
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
}

void setup() { Serial.begin(9600); }

void loop() {
    // measure the ping time in cm
    cm = 0.01723 * readUltrasonicDistance(7, 7);
    // convert to inches by dividing by 2.54
    inches = (cm / 2.54);
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.println("cm");
    delay(100);  // Wait for 100 millisecond(s)
}
