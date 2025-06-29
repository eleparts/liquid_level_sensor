#define liquid_level A0

#include <Wire.h>                       // 1602 LCD 라이브러리 세팅
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "Arduino_LED_Matrix.h"         // 아두이노 R4 WiFi 라이브러리 세팅

ArduinoLEDMatrix matrix;

int minWater = 400, maxWater = 700;     // 센서 값 최솟값과 최댓값 구하여 지정

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                   // 시리얼 포트 시작
  pinMode(liquid_level, INPUT);         // 수위센서 입력 모드 지정

  lcd.init();                           // LCD 초기화
  lcd.backlight();
  lcd.clear();
    
  matrix.begin();                       // LED 매트릭스 시작
}

const uint32_t lines_0[] = {            // LedMatrix에 띄우기 위한 LedMatrix 패턴을 제작
  0x0,
  0x0,
  0x0
};

const uint32_t lines_1[] = {
  0x0,
  0x0,
  0xfff
};

const uint32_t lines_2[] = {
  0x0,
  0x0,
  0xffffff
};

const uint32_t lines_3[] = {
  0x0,
  0xf,
  0xffffffff
};

const uint32_t lines_4[] = {
  0x0,
  0xffff,
  0xffffffff
};

const uint32_t lines_5[] = {
  0x0,
  0xfffffff,
  0xffffffff
};

const uint32_t lines_6[] = {
  0xff,
  0xffffffff,
  0xffffffff
};

const uint32_t lines_7[] = {
  0xfffff,
  0xffffffff,
  0xffffffff
};

const uint32_t lines_8[] = {
  0xffffffff,
  0xffffffff,
  0xffffffff
};

void loop() {
  // put your main code here, to run repeatedly:
  int water = analogRead(liquid_level); // water 변수에 수위센서 아날로드 값을 저장
  Serial.println(water);

  lcd.clear();                          // lcd에 센서값 출력
  lcd.setCursor(0,0);
  lcd.print("sensor : ");
  lcd.setCursor(9,0);
  lcd.print(water);

  if(water < 400){                      // 최솟값보다 작아지거나, 최댓값보다 커지면 지정한 값으로 초기화
    water = 400;
  }else if(water > 700){
    water = 700;
  }

  // 숫자(변수)를 한 범위에서 다른 범위로 비례 변환하는 map() 함수를 이용
  int amount_of_water = map(water, minWater, maxWater, 0, 8);
  Serial.println(amount_of_water);
  
  lcd.setCursor(0,1);                   // 센서값을 8개의 범위로 나누어 어느정도 물이 찼는지 확인
  lcd.print("Amount : ");
  lcd.setCursor(9, 1);
  lcd.print(amount_of_water);
  lcd.setCursor(10,1);
  lcd.print(" / 8");

  switch(amount_of_water){              // 앞서 구한 8개의 범위에 맞춰 LedMatrix 동작
    case 0:
      matrix.loadFrame(lines_0);
      break;
    case 1:
      matrix.loadFrame(lines_1);
      break;
    case 2:
      matrix.loadFrame(lines_2);
      break;
    case 3:
      matrix.loadFrame(lines_3);
      break;
    case 4:
      matrix.loadFrame(lines_4);
      break;
    case 5:
      matrix.loadFrame(lines_5);
      break;
    case 6:
      matrix.loadFrame(lines_6);
      break;
    case 7:
      matrix.loadFrame(lines_7);
      break;
    case 8:
      matrix.loadFrame(lines_8);
      break;
  }

  delay(1000);
}
