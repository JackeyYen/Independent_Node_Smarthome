// 引用 LiquidCrystal & DHT1 Library
#include <LiquidCrystal.h>
#include <DHT.h>
 
// 建立 LiquidCrystal 的變數 LCD
// LCD 接腳: RS, Enable, D4, D5, D6, D7 
// 對應到 Arduino 接腳: 12, 11, 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 6           // 定義DHT22訊號輸出腳
#define DHTTYPE DHT22      // 定義DHT型號
DHT dht(DHTPIN, DHTTYPE); // 初始化感測器

const int PIRSensor = 8;   // 紅外線動作感測器連接的腳位
const int relayPin1 = 9;   // 繼電器1(Relay1)
const int relayPin2 = 10;  // 繼電器2(Relay2)
int sensorValue = 0;       // 紅外線動作感測器訊號變數
int relayState1 = 0;       // 繼電器1狀態
int relayState2 = 0;       // 繼電器2狀態

 
void setup() {
  Serial.begin(9600);
  pinMode(PIRSensor, INPUT); 
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
   
  // 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);

  dht.begin();
}

 
void loop() {
  //宣告並讀取攝氏溫度與溼度
  float t = dht.readTemperature();
  float h = dht.readHumidity();
   
  // 將游標設到 column 0, line 0  (第一行)
  lcd.setCursor(0, 0);
  lcd.print("TEMP. : ");
  lcd.print(t, 1);      // 顯示到小數點後一位
  lcd.print((char)223);      // 溫度符號(degree symbol)
  lcd.print("C");
 
  // 將游標設到 column 0, line 1  (第二行)
  lcd.setCursor(0, 1); 
  lcd.print("Humidity : ");
  lcd.print(h, 1);    // 顯示到小數點後一位
  lcd.print("%");

  sensorValue = digitalRead(PIRSensor);     // 讀取 PIR Sensor 的狀態

  if (sensorValue == HIGH) {
    if (t >= 25)
      relayState1 = 1;
    if (t <= 19)
      relayState1 = 0;
    digitalWrite(relayPin1, relayState1);    // 讓繼電器1作動, 切換開關
   
    if (h >= 60)
      relayState2 = 1;
    if (h <= 42)
      relayState2 = 0;
    digitalWrite(relayPin2, relayState2);    // 讓繼電器2作動, 切換開關 
   }

  if (sensorValue == LOW) {
    if (t >= 27)
      relayState1 = 1;
    if (t <= 23)
      relayState1 = 0;
    digitalWrite(relayPin1, relayState1);    // 讓繼電器1作動, 切換開關
   
    if (h >= 70)
      relayState2 = 1;
    if (h <= 50)
      relayState2 = 0;
    digitalWrite(relayPin2, relayState2);    // 讓繼電器2作動, 切換開關 
   }

   Serial.print("TEMP. : ");
   Serial.print(t);
   Serial.println("*C");
   Serial.print("Humidity : ");
   Serial.print(h);
   Serial.println("%");
   Serial.print("PIR Sensor : ");
   Serial.println(sensorValue);
   Serial.print("Fans relay-1 sate : ");
   Serial.println(relayState1);
   Serial.print("Dryers relay-2 sate : ");
   Serial.println(relayState2);
   Serial.println("---------------------------");

   delay(3000);
}

