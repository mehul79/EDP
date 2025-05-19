void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}
int count = 0;
int flag = 0;


void forward(){
  digitalWrite(5, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

  void backward(){
  digitalWrite(5, LOW);
  digitalWrite(8, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  }

   void left(){
  digitalWrite(5, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  }

     void right(){
  digitalWrite(5, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  }

     void stop(){
  digitalWrite(5, LOW);
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  }

   void clockwise(){
  digitalWrite(5, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  }

   void anticlockwise(){
    digitalWrite(5, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
}

void loop() {
  int l = digitalRead(A0);
  int r = digitalRead(A1);
  if(l == 1 && r == 1){
    if(flag == 1){
      count++;
      flag = 0;
    }
    forward();
  }
  else if(l == 1 && r == 0){
    right();
  }
  else if(l == 0 && r == 1){
    left();
  }
  else {
    flag = 1;
    if(count == 1){
      anticlockwise();
      delay(1100);
    }
    if(count == 3){
      stop();
      delay(1000000000);
    }
   }
   Serial.println(count);
}


