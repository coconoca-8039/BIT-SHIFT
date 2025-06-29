#include <Wire.h>

const uint8_t MY_ADDR = 0x08;
volatile char rxBuf[5] = {'0','0','0','0','\0'};
volatile bool newData = false;

const int segPins[8] = {11, 7, 4, 2, 13, 10, 5, 3};
const int digitPins[4] = {12, 9, 8, 6};

int value = 0;

const int numbers[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}  // 9
};

// I2Cの受信処理
void receiveEvent(int bytes) {
  int i = 0;
  while (Wire.available() && i < 5) {
    char c = Wire.read();
    if ((c >= '0' && c <= '9') || c == '.') {
      rxBuf[i++] = c;
    }
  }
  rxBuf[i] = '\0';
  newData = true;
}

// LCDを全消灯させる関数
void turnoffLCD() {
  for (int i = 0; i < 4; i++) {
      digitalWrite(digitPins[i], HIGH);  
    }
}

void setup() {
  // ピンの初期設定
  for (int i = 0; i < 8; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }

  pinMode(7, OUTPUT); // テスト用

  // I2Cの設定
  Serial.begin(115200);
  while (!Serial);
  Wire.begin(MY_ADDR);
  Wire.onReceive(receiveEvent);

}

void loop() {
  char buf[5];
  noInterrupts();
  memcpy(buf, rxBuf, sizeof(rxBuf));
  interrupts();

  if(newData == true){
      value = atof(buf);
      Serial.print("Tx value: ");
      Serial.println(value);
  }

  // 配列に格納
  int digits[4] = {0, 0, 0, 0};
  digits[0] = value / 1000;          // 千の位
  digits[1] = (value / 100) % 10;    // 百の位
  digits[2] = (value / 10) % 10;     // 十の位
  digits[3] = value % 10;            // 一の位

  bool leadingZero = false;

  if((digits[0] == 0) && (digits[1] == 0)){
    leadingZero = true;
    digitalWrite(7, HIGH);
  }else{
    digitalWrite(7, LOW);
  }

  // デバッグ用
  if(newData == true){
      Serial.print("digits: ");
      for (int i = 0; i < 4; i++) {
      Serial.print(digits[i]);
      if (i != 3) {
          Serial.print(", ");
      }
      }
      Serial.println();
  }

  newData = false;
  
  for (int d = 0; d < 4; d++) {

      // 全消灯
      turnoffLCD();

      for (int s = 0; s < 8; s++) {
        if (numbers[digits[d]][s] == 1) { 
            digitalWrite(segPins[s], HIGH);
        } else {
            digitalWrite(segPins[s], LOW);
        }
      }

      // 不要なピンの消灯
      digitalWrite(digitPins[d], LOW);

      delay(5);  // ミリ秒 1000ms=1s
  }
  
}
