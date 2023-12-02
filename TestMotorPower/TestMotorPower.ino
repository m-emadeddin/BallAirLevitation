int inches = 0;
int cm = 0;

const int trigPinHand = 9;    // hand position ultrasonic sensor Trig
const int echoPinHand = 10;   // hand position ultrasonic sensor Echo
const int trigPinBall = 4;    // ball position ultrasonic sensor Trig
const int echoPinBall = 7;    // ball position ultrasonic sensor Echo
const int fanPin = 3;         // PWM output for motor control
double power = 5;

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

void setup() {
    pinMode(trigPinBall, OUTPUT);  // Sets the trigPin as an Output for Ball position sensor
    pinMode(echoPinBall, INPUT);  // Sets the echoPin as an Input for Ball position sensor
    pinMode(trigPinHand, OUTPUT);  // Sets the trigPin as an Output for Hand postion sensor
    pinMode(echoPinHand, INPUT);  // Sets the echoPin as an Input for Hand position sensor
    pinMode(fanPin, OUTPUT);   
    Serial.begin(9600); 
}

void loop() {
    // measure the ping time in cm
    cm = 0.01723 * readUltrasonicDistance(7, 7);
    // convert to inches by dividing by 2.54
    inches = (cm / 2.54);
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.println("cm");
    delay(200);  // Wait for 100 millisecond(s)
    if(cm < 30 && power <= 100){
        power += 5;
        motorPower(fanPin, power);
    }
    Serial.println(power);
}


void motorPower(int motorPin, double power) {
    // Function that writes the values of the desired power on the pin of the motor. 
    // The inputs are the pin to which the motor is attached and the
    // desired power (number 0-100).

    double powerOut = (int)((power / 100) * 255);  // gets the fraction of power in input, number between 0 and 1
    analogWrite(motorPin, powerOut);  
    // gives the voltage to the motor, an integer 0-255,
    // proportional to the fraction of the power in input, 20 mV each step
}