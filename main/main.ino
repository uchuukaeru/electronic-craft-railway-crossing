#include<Servo.h>

//サーボモータ用ピン
#define MPIN 6
Servo myservo;

//警告灯LED用ピン
#define LA_1 9
#define LA_2 10

//方向指示LED用ピン
#define LB_1 11
#define LB_2 12

//緊急停止ボタン用ピン
//通常時　LOW,押されたとき　HIGH
#define STOP 7

//制御基板用ピン
//通常時　LOW,押されたとき　HIGH
#define SW1 14  //実行・停止ボタン
#define SW2 15  //方向指示LED1の点滅制御
#define SW3 16  //方向指示LED2の点滅制御
#define SW4 17  //

//電源・動作確認用LED
#define LED 25

//状態保持変数
bool State=0;  //本体が動作しているかどうか  0(false):停止中,1(true):動作中
bool lb1=0; //方向指示LED1の状態 0(false):点灯しない,1(true):点灯する
bool lb2=0; //方向指示LED2の状態 0(false):点灯しない,1(true):点灯する
bool MState=1;  //遮断機の状態  0(false):遮断機が上がっている,1(true):遮断機が下がっている


//core0
void setup() {
  //動作指示
  myservo.attach(MPIN);
  ber(0);
  
  pinMode(LA_1,OUTPUT);
  pinMode(LA_2,OUTPUT);
  pinMode(LB_1,OUTPUT);
  pinMode(LB_2,OUTPUT);
  pinMode(STOP,INPUT);
  
  Serial.begin(115200);
  Serial.println("Hello");
}

void loop() {
  //core0で動作を操作する
  if(Serial.available()){
    int mode=(bool)Serial.read();
    Serial.println(mode);
    ber(mode);
  }

}


//core1
void setup1(){
  //制御系
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(SW3,INPUT);
  pinMode(SW4,INPUT);

  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
}

void loop1(){
  //core1で制御系のスイッチ（入力）
  if(digitalRead(SW2)==HIGH){
    State=!State;
    delay(1000);
  }
  if(digitalRead(SW2)==HIGH){
    lb1=!lb1;
    delay(1000);
  }
  if(digitalRead(SW3)==HIGH){
    lb2=!lb2;
    delay(1000);
  }
  if(digitalRead(SW4)==HIGH){
    
  }
}


//function
void ber(bool mode){
  Serial.println("ber");
  if(mode==MState){
    ;
  }else{
    MState=!MState;
    if(mode==0){//上げる
      for(int n=90;n>=0;n-10){
        Serial.println(n);
        myservo.write(n);
        delay(100);
      }
    }else if(mode==1){//下す
      for(int n=0;n<=90;n+5){
        Serial.println(n);
        myservo.write(n);
        delay(200);
      }
    }
  }
}
