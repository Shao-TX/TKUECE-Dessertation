#include <Wire.h>
#include <EEPROM.h>


#define SLAVE_ADDRESS 0x08
#define MOTOR_NUM 6
#define POS_MEM 0x00
#define HEI_MEM 0x06


int motorPin[MOTOR_NUM*2]  = {13,12,11,10,9,8,7,6,5,4,3,2};
int limitSwitchPin[MOTOR_NUM] = {A0,A1,A2,A3,A6,A7};
int receive_Data[MOTOR_NUM] = {0}; 

typedef struct{
  int mpA,mpB;
  int lsp;
  byte start;
  int countDown;
  int nowTime;
  byte reset;
  int pos;
}Pin;


static float ms_per_mm = 5.285;
//static float ms_per_mm = 7;
static int btnGap = 100;
int moving;
int testData[MOTOR_NUM] = {30,30,30,30,30,30};
Pin pin[MOTOR_NUM];
int getData;
int standby=0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("I2C setup...");
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("I2C success...");
  //delay(1000);
  
  for(int i=0;i<MOTOR_NUM;i++){
    pin[i].mpA = motorPin[i*2];
    pinMode(pin[i].mpA,OUTPUT);
    digitalWrite(pin[i].mpA,LOW);
    pin[i].mpB = motorPin[i*2 + 1];
    pinMode(pin[i].mpB,OUTPUT);
    digitalWrite(pin[i].mpB,LOW);
    pin[i].lsp = limitSwitchPin[i];
    pinMode(pin[i].lsp,INPUT_PULLUP);
    pin[i].reset=0;
  }
  
  
  motorReset();
  
  getData=0;
  Serial.println("setup end");
  standby = 1;
}


int time_stamp,time_stamp2;
int use_time;


void loop(){
  /*
  for(int i=0;i<MOTOR_NUM;i++){
    Serial.print("P");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(analogRead(pin[i].lsp));
  }
  
  Serial.print('\n');
  */
  if(getData){
    //Serial.println("getData");
    for(int i=0;i<MOTOR_NUM;i++){
      testData[i]=EEPROM.read(POS_MEM+i);
    }
    new_motorMove(testData);
    getData=0;
  }
  
  //pinTest(5);
}

void pinTest(int p){
  //up down
  int T = 800;
  Move(pin[p],1);
  delay(T);
  Stop(pin[p]);
  delay(T);
  Move(pin[p],0);
  delay(T);
  Stop(pin[p]);
  delay(T);
  
}

void receiveData(int bytecount)
{
  Wire.read();
  for(int i=0;Wire.available()&&i<MOTOR_NUM;i++){

    EEPROM.write(POS_MEM+i,Wire.read());
    
    getData=1;
  }
  
}

void sendData()
{
  for(int i=0;i<MOTOR_NUM;i++){
    Wire.write(EEPROM.read(HEI_MEM+i));
  }
}

int lspCheck(){
  for(int i=0;i<MOTOR_NUM;i++){
    if(analogRead(pin[i].lsp)<btnGap){
      //有按下去
      pin[i].reset=1;
      continue;
    }else{
      if(pin[i].reset){
        continue;
      }
      return 0;
    }
  }
  return 1;
}

void motorReset(){
  int val;
  Serial.println("reset start...");
  delay(500);
  while(!lspCheck()){
    
    for(int i=0;i<MOTOR_NUM;i++){
      if((val=analogRead(pin[i].lsp))<btnGap){
        Stop(pin[i]);
        pin[i].reset=1;
      }else{
        if(!(pin[i].reset)){
          Move(pin[i],0);
        }
      }
      
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(val);
      Serial.print(", ");
      Serial.print(pin[i].reset);
      Serial.print(", ");
      
    }
    Serial.println(" ");
  }
  
  for(int i=0;i<MOTOR_NUM;i++){
    Stop(pin[i]);
    pin[i].reset=0;
    pin[i].pos=0;
    EEPROM.write(HEI_MEM+i,pin[i].pos);
  }
  
  Serial.println("reset end...");
}

void singleMotorReset(Pin pin){
  while(analogRead(pin.lsp)>btnGap) Move(pin,0);
  Stop(pin);
}


void motorMove(int *distance){
  
  //歸位
  motorReset();

  //計算要上升的距離時間
  // 70mm 370ms -> 1mm 5.285ms

  for(int i=0;i<MOTOR_NUM;i++){
    if(distance[i]==0){
      continue;
    }
    Move(pin[i],1);
    delay(distance[i]*ms_per_mm);
    Stop(pin[i]);
  }

}

void new_motorMove(int *distance){
  for(int i=0;i<MOTOR_NUM;i++){

    if(distance[i]==0 && analogRead(pin[i].lsp)>btnGap){
      //singleMotorReset(pin[i]);
    }else if(pin[i].pos>distance[i]){
      Move(pin[i],0);
      delay((pin[i].pos-distance[i])*ms_per_mm);
      Stop(pin[i]);
    }else if((pin[i].pos<distance[i])*ms_per_mm){
      Move(pin[i],1);
      delay((distance[i]-pin[i].pos)*ms_per_mm);
      Stop(pin[i]);
    }else{
      continue;
    }
    pin[i].pos=distance[i];
    EEPROM.write(HEI_MEM+i,pin[i].pos);
  }
}

void Move(Pin input,int way){
  moving=1;
  if(way==0){
    digitalWrite(input.mpA,HIGH);
    digitalWrite(input.mpB,LOW);
  }else{
    digitalWrite(input.mpB,HIGH);
    digitalWrite(input.mpA,LOW);
  }
}

void Stop(Pin input){
  moving=0;
  digitalWrite(input.mpA,LOW);
  digitalWrite(input.mpB,LOW);
}
