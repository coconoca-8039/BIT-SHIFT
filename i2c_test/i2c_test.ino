#include <Wire.h>

const uint8_t SLAVE_ADDR = 0x08;  // スレーブのアドレス

void setup() {
  Wire.begin();                
  Serial.begin(115200);
  while (!Serial);             // シリアルモニタが開くまで待機
  randomSeed(analogRead(A0));  // 未接続ピンから乱数シード取得
}

void loop() {
  // 1～9999 の乱数を生成
  int rnd = random(1, 10000);

  // 可変長の文字列に変換
  char buf[6];                 // 最大4桁 + 終端文字
  int len = sprintf(buf, "%d", rnd);

  // スレーブへ送信（ヌル文字は含めず、文字数分だけ送る）
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write((uint8_t*)buf, len);
  Wire.endTransmission();

  // 送った内容をシリアルに表示
  Serial.print("Sent: ");
  Serial.println(buf);

  delay(1000);  // １秒待つ（必要に応じて調整してね）
}
