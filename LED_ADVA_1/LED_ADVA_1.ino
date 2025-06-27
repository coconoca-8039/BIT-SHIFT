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

// // 小数の位置を探す関数
// int getDpIndex(float value) {
//     if (value >= 1000) {
//         return 3;
//     } else if (value >= 100) {
//         return 3;
//     } else if (value >= 10) {
//         return 2;
//     } else {
//         return 0;
//     }
// }

void setup() {
  // ピンの初期設定
  for (int i = 0; i < 8; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }

  // I2Cの設定
  Serial.begin(115200);
  while (!Serial);
  Wire.begin(MY_ADDR);
  Wire.onReceive(receiveEvent);

}

void loop() {
  // I2Cのデバッグ用
  // if (newData) {
  //   char buf[5];
  //   noInterrupts();
  //   memcpy(buf, rxBuf, sizeof(rxBuf));
  //   interrupts();

  //   value = atof(buf);

  //   Serial.print("Received: ");
  //   Serial.println(buf);

  //   Serial.print("Tx value: ");
  //   Serial.println(value);

  //   newData = false;
  // }

    // // 小数点探し
    // int dpIndex = 0;
    // dpIndex = getDpIndex(value);

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
    // int scaledValue = (int)(value * 10 + 0.5);  // 四捨五入付き 小数点第1位まで見せる
    // digits[0] = (scaledValue / 1000) % 10;
    // digits[1] = (scaledValue / 100) % 10;
    // digits[2] = (scaledValue / 10) % 10;
    // digits[3] = scaledValue % 10;
    digits[0] = value / 1000;          // 千の位
    digits[1] = (value / 100) % 10;    // 百の位
    digits[2] = (value / 10) % 10;     // 十の位
    digits[3] = value % 10;            // 一の位

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

        // // 小数点の点灯
        // if (d == dpIndex) {
        // digitalWrite(segPins[7], HIGH);
        // } else {
        // digitalWrite(segPins[7], LOW);
        // }

        // 不要なピンの消灯
        digitalWrite(digitPins[d], LOW);

        delay(5);  // ミリ秒 1000ms=1s
    }
  
}
