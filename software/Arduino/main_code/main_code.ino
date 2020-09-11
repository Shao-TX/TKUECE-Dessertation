#define A1_A 13
#define A1_B 11
#define A2_A 12
#define A2_B 10
#define A3_A 8
#define A3_B 9
#define A4_A 7
#define A4_B 6
#define A5_A 4
#define A5_B 5
#define A6_A 2
#define A6_B 3

void motor_stop();
void motor_action(int key);

void setup() {
  Serial.begin(9600);

  // PIN 設定
  pinMode(A1_A,OUTPUT);
  pinMode(A1_B,OUTPUT);
  pinMode(A2_A,OUTPUT);
  pinMode(A2_B,OUTPUT);
  pinMode(A3_A,OUTPUT);
  pinMode(A3_B,OUTPUT);
  pinMode(A4_A,OUTPUT);
  pinMode(A4_B,OUTPUT);
  pinMode(A5_A,OUTPUT);
  pinMode(A5_B,OUTPUT);
  pinMode(A6_A,OUTPUT);
  pinMode(A6_B,OUTPUT);

  // PIN 初始
  digitalWrite(A1_A,LOW);
  digitalWrite(A1_B,LOW);
  digitalWrite(A2_A,LOW);
  digitalWrite(A2_B,LOW);
  digitalWrite(A3_A,LOW);
  digitalWrite(A3_B,LOW);
  digitalWrite(A4_A,LOW);
  digitalWrite(A4_B,LOW);
  digitalWrite(A5_A,LOW);
  digitalWrite(A5_B,LOW);
  digitalWrite(A6_A,LOW);
  digitalWrite(A6_B,LOW);
}

void loop() {

  motor_stop();
  
  if(Serial.available()){         
    int x = Serial.parseInt();
    if(x == 20){
      motor_action(x);
      }
    motor_forward(x);
    motor_back(x);
    Serial.println(x);
   }
}


void motor_stop(){
  digitalWrite(A1_A,LOW);
  digitalWrite(A1_B,LOW);
  digitalWrite(A2_A,LOW);
  digitalWrite(A2_B,LOW);
  digitalWrite(A3_A,LOW);
  digitalWrite(A3_B,LOW);
  digitalWrite(A4_A,LOW);
  digitalWrite(A4_B,LOW);
  digitalWrite(A5_A,LOW);
  digitalWrite(A5_B,LOW);
  digitalWrite(A6_A,LOW);
  digitalWrite(A6_B,LOW);
}


void motor_forward(int key1){
  int delay_time = 300;
  switch(key1){
    case 1 :
     Serial.println("A1往前");
     analogWrite(A1_A,255);
     digitalWrite(A1_B,LOW);
     delay(delay_time);
     break;
    case 2 :
     Serial.println("A2往前");
     analogWrite(A2_A,255);
     digitalWrite(A2_B,LOW);
     delay(delay_time);
     break;
    case 3 :
     Serial.println("A3往前");
     analogWrite(A3_A,255);
     digitalWrite(A3_B,LOW);
     delay(delay_time);
     break;
    case 4 :
     Serial.println("A4往前");
     analogWrite(A4_A,255);
     digitalWrite(A4_B,LOW);
     delay(delay_time);
     break;
    case 5 :
     Serial.println("A5往前");
     analogWrite(A5_A,255);
     digitalWrite(A5_B,LOW);
     delay(delay_time);
     break;
    case 6 :
     Serial.println("A6往前");
     analogWrite(A6_A,255);
     digitalWrite(A6_B,LOW);
     delay(delay_time);
     break;
    }
}

void motor_back(int key2){
  int delay_time = 300;
  switch(key2){
    case 7 :
     Serial.println("A1往後");
     analogWrite(A1_A,LOW);
     digitalWrite(A1_B,255);
     delay(delay_time);
     break;
    case 8 :
     Serial.println("A2往後");
     analogWrite(A2_A,LOW);
     digitalWrite(A2_B,255);
     delay(delay_time);
     break;
    case 9 :
     Serial.println("A3往後");
     analogWrite(A3_A,LOW);
     digitalWrite(A3_B,255);
     delay(delay_time);
     break;
    case 10 :
     Serial.println("A4往後");
     analogWrite(A4_A,LOW);
     digitalWrite(A4_B,255);
     delay(delay_time);
     break;
    case 11 :
     Serial.println("A5往後");
     analogWrite(A5_A,LOW);
     digitalWrite(A5_B,255);
     delay(delay_time);
     break;
    case 12 :
     Serial.println("A6往後");
     analogWrite(A6_A,LOW);
     digitalWrite(A6_B,255);
     delay(delay_time);
     break;
    }
}

void motor_action(int key){
   int delay_time = 200;
   analogWrite(A1_A,255);
   digitalWrite(A1_B,LOW);
   delay(delay_time);
   analogWrite(A1_A,LOW);
   digitalWrite(A1_B,255);
   delay(delay_time);
   
   analogWrite(A2_A,255);
   digitalWrite(A2_B,LOW);
   delay(delay_time);
   analogWrite(A2_A,LOW);
   digitalWrite(A2_B,255);
   delay(delay_time);

   analogWrite(A3_A,255);
   digitalWrite(A3_B,LOW);
   delay(delay_time);
   analogWrite(A3_A,LOW);
   digitalWrite(A3_B,255);
   delay(delay_time);

   analogWrite(A4_A,255);
   digitalWrite(A4_B,LOW);
   delay(delay_time);
   analogWrite(A4_A,LOW);
   digitalWrite(A4_B,255);
   delay(delay_time);

   analogWrite(A5_A,255);
   digitalWrite(A5_B,LOW);
   delay(delay_time);
   analogWrite(A5_A,LOW);
   digitalWrite(A5_B,255);
   delay(delay_time);

   analogWrite(A6_A,255);
   digitalWrite(A6_B,LOW);
   delay(delay_time);
   analogWrite(A6_A,LOW);
   digitalWrite(A6_B,255);
   delay(delay_time);
}
