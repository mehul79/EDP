const int ledPin = 9;
const int trigPin = 13;
const int echoPin = 12;
const int gantryPin = 4;  // IR sensor for gantry detection
long duration;
int x = 1;
int distanceCm, distanceInch;

long st = millis();
int count = 0;
int flag = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motor control pins
  for (int i = 5; i < 9; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(A0, INPUT); // Left IR sensor
  pinMode(A1, INPUT); // Right IR sensor
  pinMode(gantryPin, INPUT); // Gantry IR sensor

  Serial.begin(9600);
}

// Motor control functions
void stopp() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void forward() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void backward() {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void left() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void right() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void clockwise() {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void counterclockwise() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void loop() {
  // ---------- Gantry Detection ----------
  if (digitalRead(gantryPin) > 0) {
    int value = pulseIn(gantryPin, HIGH);
    Serial.print("Value = ");
    Serial.println(value);

    if (value > 1000 && value < 2000) {
      Serial.println("Gantry 1 Crossed");
      stopp();
      delay(1000);
    } 
    else if (value > 2500 && value < 3000) {
      Serial.println("Gantry 2 Crossed");
      stopp();
      delay(1000);
    } 
    else if (value > 500 && value < 1000) {
      Serial.println("Gantry 3 Crossed");
      stopp();
      delay(1000);
    }
  }

  // ---------- Navigation and Obstacle Avoidance ----------
  if (x == 1 || flag == 1) {
    flag = 1;

    // Ultrasonic measurement
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distanceCm = (duration * 0.034) / 2;
    distanceInch = (duration * 0.0133) / 2;

    if (distanceCm > 30) {
      int leftIR = digitalRead(A0);
      int rightIR = digitalRead(A1);

      if (leftIR == 1 && rightIR == 1) {
        forward();
      } 
      else if (leftIR == 1 && rightIR == 0) {
        left();
      } 
      else if (leftIR == 0 && rightIR == 1) {
        right();
      } 
      else {
        long endt = millis();
        if (endt - st > 500) {
          count++;
          Serial.print("Group 3 count = ");
          Serial.println(count);
          st = millis();
        }

        // ---------- Predefined Path Sequence ----------
        switch (count) {
          case 0:
          case 1:
            forward();
            break;
          case 2:
            right();
            delay(500);
            break;
          case 3:
          case 4:
            forward();
            break;
          case 5:
            right();
            delay(600);
            break;
          case 6:
            forward();
            break;
          case 7:
            stopp();
            delay(10000);  // Final halt
            flag = 0;
            break;
          default:
            stopp();
        }
      }
    } else {
      // Obstacle too close
      stopp();
      delay(1000);
    }
  }
}