#define A_1A 10
#define A_1B 11
int val;
bool red_led = false;
bool green_led = false;

void setup() {
  Serial.begin(9600);
  pinMode(A_1A,OUTPUT);
  pinMode(A_1B,OUTPUT);
  digitalWrite(A_1A,LOW); // pin 初始
  digitalWrite(A_1B,LOW); // pin 初始
    
  pinMode(3,INPUT);
  pinMode(6,OUTPUT); // pin 到達底部 : 紅燈
  pinMode(7,OUTPUT); // pin 可移動 : 綠燈

  digitalWrite(6,LOW); // LED(紅) 初始
  digitalWrite(7,LOW); // LED(綠) 初始
}

void loop() {
  val = digitalRead(3); // 判定微動開關狀態
  if(green_led) Serial.println("繼續");
  if(red_led) Serial.println("停止");
 
  if(Serial.available()){   
  char x = Serial.read();
  Serial.println(x);
  
  if(val == 0){
    green_led = true;
    red_led = false;
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    }else{
      green_led = false;
      red_led = true;
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
      }
  
  if(x == 'f'){
    // pin 往上
    analogWrite(A_1A,255);
    digitalWrite(A_1B,LOW);
    delay(250);
  }else if(x == 'r'){
    // pin 往下
    digitalWrite(A_1A,LOW);
    analogWrite(A_1B,255);
    delay(300);
    if(val == 1){
      // 觸發微動開關 : pin 到達底部
      Serial.println("停止觸發成功");
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(A_1A,LOW);
      digitalWrite(A_1B,LOW);
      }
    }else{
      digitalWrite(A_1A,LOW);
      digitalWrite(A_1B,LOW);
    }
  }
}
/*
void test(){
if(Serial.available()){
  char x = Serial.read();
  if(x == 'F'){
    analogWrite(A_1A,255);
    digitalWrite(A_1B,LOW);
    delay(5000);
  }else if(x == 'R'){
    digitalWrite(A_1A,LOW);
    analogWrite(A_1B,255);
    delay(5000);
    }else{
      digitalWrite(A_1A,LOW);
      digitalWrite(A_1B,LOW);
      delay(3000);
      }
     }
    }*/
