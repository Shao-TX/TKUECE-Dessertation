#define MOTOR_NUM 6

struct Motor{
  byte A,B,LS;
};

Motor motor[MOTOR_NUM];
byte motor_pins[MOTOR_NUM*2] = {13,12,11,10,9,8,7,6,5,4,3,2};
byte motor_limitSwitch[MOTOR_NUM] = {A0,A1,A2,A3,A6,A7};
int control = 0;

void setup(){
  //pinMode(A0,INPUT_PULLUP); // limited switch
  // put your setup code here, to run once:
  for(int i=0;i<MOTOR_NUM;i++){
    motor[i].A = motor_pins[i*2];
    motor[i].B = motor_pins[i*2+1];
    motor[i].LS = motor_limitSwitch[i];
    pinMode(motor[i].A,OUTPUT);
    pinMode(motor[i].B,OUTPUT);
    pinMode(motor[i].LS,INPUT_PULLUP);
    digitalWrite(motor[i].A,LOW);
    digitalWrite(motor[i].B,LOW);   
  }
  Serial.begin(9600); 
}

void loop() {
  Serial.println("connected!");
  up(control);
  delay(300);
  stop_(control);
  delay(300);
  down(control);
  delay(300);
  stop_(control);
  delay(300);
  control++;
  if(control==6){
    control=0;
  }
}

void up(byte index){
  digitalWrite(motor[index].A,HIGH);
  digitalWrite(motor[index].B,LOW);
}

void down(byte index){
  digitalWrite(motor[index].A,LOW);
  digitalWrite(motor[index].B,HIGH);
}


void reset(byte index){
  // limited switch
  while(!digitalRead(motor[index].LS)){
    down(index);
  }
  stop_(index);
}

void stop_(byte index){
  digitalWrite(motor[index].A,LOW);
  digitalWrite(motor[index].B,LOW);
}
