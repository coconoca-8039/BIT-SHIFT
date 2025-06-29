#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// define
const unsigned long INTERVAL_100MS = 100;
const unsigned long INTERVAL_10SEC = 2000;
unsigned long last100ms = 0;
unsigned long last10sec = 0;
const uint8_t SLAVE_ADDR = 0x08;
Adafruit_BME280 bme;
uint16_t globalTempInt = 0;
uint16_t globalHumidInt = 0;
uint16_t globalPressInt = 0;
const int toggle_timer = 100;

void setup() {
  Wire.begin();                
  Serial.begin(115200);
  while (!Serial);             
  
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("BME280: Init OK!");
}

void loop() {
  unsigned long now = millis();
  static int displayToggleTimer = 0;
  char buf[6];                 // 最大4桁 + 終端文字
  int len = 0;

  // 0.1秒周期
  if (now - last100ms >= INTERVAL_100MS) {
    last100ms = now;

    displayToggleTimer++;
    if(displayToggleTimer == toggle_timer){
      displayToggleTimer = 0;
    }

    readBME280Data();
    
    if(displayToggleTimer <= toggle_timer / 2){
      len = sprintf(buf, "%d", globalTempInt);
    }else{
      len = sprintf(buf, "%d", globalHumidInt);
    }
    
    // スレーブへ送信（ヌル文字は含めず、文字数分だけ送る)
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write((uint8_t*)buf, len);
    Wire.endTransmission();

    // 送った内容をシリアルに表示
    Serial.print("Sent: ");
    Serial.println(buf);
  }

  if (now - last10sec >= INTERVAL_10SEC) {
    last10sec = now;

    // readBME280Data();
    // Serial.print("temp: ");
    // Serial.print(globalTempInt);
    // Serial.println(" ℃");
    // Serial.print("humi: ");
    // Serial.print(globalHumidInt);
    // Serial.println(" %");
    // Serial.print("press: ");
    // Serial.print(globalPressInt);
    // Serial.println(" hPa");
  }
}

void readBME280Data() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;  // hPaに変換

  globalTempInt = (uint16_t)(temperature);
  globalHumidInt = (uint16_t)(humidity);
  globalPressInt = (uint16_t)(pressure);
}