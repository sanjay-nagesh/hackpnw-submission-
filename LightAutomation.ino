// Variable to track occupancy
int people = 0;
// false is off, true is on
bool light = false;
// variable for while loops
bool cont = true;

// ULTRASONIC SETUP
const int TRIG_PIN = 6; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 7; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int TRIG_PIN2 = 10; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN2 = 11; // Arduino pin connected to Ultrasonic Sensor's ECHO pin

// Maximum distance for ultrasonic sensor to track within
const int DISTANCE_THRESHOLD = 10;// centimeters

// LED SETUP
const int ledPin = 3;

// Variables to Track ultrasonic sensor distance
float duration_us, distance_cm, duration_us2, distance_cm2;

void setup() {
  // put your setup code here, to run once:
  // Setup for serial port to help with debugging
  Serial.begin(9600);
  // Declaring Arduino pins as input or output
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  pinMode(TRIG_PIN2, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN2, INPUT);  // set arduino pin to input mode
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Getting time of reflection for outwards ultrasonic sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Getting time of reflection for inwards ultrasonic sensor
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration_us2 = pulseIn(ECHO_PIN2, HIGH);

  // Calculating the distance from return time of ultrasonic waves
  distance_cm = 0.021 * duration_us;
  distance_cm2 = 0.021 * duration_us2;

  // If outside ultrasonic sensor detects a person
  if(distance_cm < DISTANCE_THRESHOLD){
    while(cont){
      // Calculating the distance from return time of ultrasonic waves
      digitalWrite(TRIG_PIN2, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN2, LOW);
      duration_us2 = pulseIn(ECHO_PIN2, HIGH);
      distance_cm2 = 0.021 * duration_us2;
      // and second sensor detects person
      if(distance_cm2 < DISTANCE_THRESHOLD){
        // Turn on the light if needed
        if(people == 0){
          light = true;
        }
        // increase occupancy
        people+=1;
        // delay to avoid errors
        delay(1000);
        // break loop to continue code
        cont = false;
      }
    }
  // If inside ultrasonic sensor detects a person
  }else if(distance_cm2 < DISTANCE_THRESHOLD){
    while(cont){
      // Calculating the distance from return time of ultrasonic waves
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      duration_us = pulseIn(ECHO_PIN, HIGH);
      distance_cm = 0.021 * duration_us;
      // and second sensor detects person
      if(distance_cm < DISTANCE_THRESHOLD){
        // turn off the lights if last person leaves the room
        if(people == 1){
          light = false;
        }
        // Decrease the occupancy
        if(people>=0){
          people-=1;
        }
        // Delay to avoid errors
        delay(1000);
        // Break loop to continue code
        cont = false;
      }
    }
  }
  
  // Turn on or off light depending on veriable state
  if(light){
    digitalWrite(ledPin, HIGH);
  }else if(!light){
    digitalWrite(ledPin, LOW);
  }

  // Output measured distances and occupancy for debugging
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  Serial.print("distance2: ");
  Serial.print(distance_cm2);
  Serial.println(" cm");
  Serial.println(people);
  // Delay for serial output
  delay(100);

  // Allowing while loops to run in next iteration of loop
  cont = true;
}