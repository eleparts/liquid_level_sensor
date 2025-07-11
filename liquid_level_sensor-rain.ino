#define liquid_level A0

#include <Wire.h>                       // 1602 LCD 라이브러리 세팅
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                   // 시리얼 포트 시작
  pinMode(liquid_level, INPUT);         // 수위센서 입력 모드 지정

  lcd.init();                           // LCD 초기화
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  int water = analogRead(liquid_level); // water 변수에 수위센서 아날로드 값을 저장
  Serial.println(water);

  lcd.clear();                          // lcd에 센서값 출력
  lcd.setCursor(0,0);
  lcd.print("sensor : ");
  lcd.setCursor(9,0);
  lcd.print(water);
  
  lcd.setCursor(0,1);                   // 비 감지 후 날씨(비 여부) 출력
  lcd.print("Weather : ");
  lcd.setCursor(10, 1);

  if(water > 300){
    lcd.print("Rainy");
  }else {
    lcd.print("Sunny");
  }

  delay(1000);                          // 1초 동작 지연
}
