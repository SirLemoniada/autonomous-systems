int motor1pin1 = 5;
int motor1pin2 = 4;
int motor2pin1 = 3;
int motor2pin2 = 2;
String command;

void right_back(){
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
}

void right_stop(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
}

void left_stop(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void right_front(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
}

void left_back(){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void left_front(){
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void front(){
  right_front();
  left_front();
}

void back(){
  right_back();
  left_back();
}

void turn_left(){
  right_front();
  left_back();
}

void turn_right(){
  right_back();
  left_front();
}

void stop(){
  left_stop();
  right_stop();
}

void setup() {
  Serial.begin(9600); 
  Serial.setTimeout(1); 
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT);

  analogWrite(9, 100); // speed 0-255
  analogWrite(10, 100); // speed 0-255
}

void loop() {
  while (!Serial.available());{
    command = Serial.readString();
    Serial.print(command);

    // forward
    if (command == "f"){
      front();
      delay(3000);
      stop();
    }
    
    // backwards
    if (command == "b"){
      back();
      delay(3000);
      stop();
    }

    // left
    if (command == "l"){
      turn_left();
      delay(700);
      stop();
    }

    // right
    if (command == "r"){
      turn_right();
      delay(700);
      stop();
    }

    command="";
  }
}
