//Arduino Uno (Mega328) + Arduino Keypad + LCD 1602 Shield 

//Нужно здесь подключить LiquidCrystal.h чтобы он был доступен при компиляции
#include <LiquidCrystal.h>
#include "LiquidCrystalCyr.h"

#define LCD_RS  8
#define LCD_EN  9
#define LCD_D0  4
#define LCD_D1  5
#define LCD_D2  6
#define LCD_D3  7

LiquidCrystalCyr lcd(LCD_RS, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3);

void setup(){
  //Инициализируем работу с дисплеем 1602 (16х2)
  lcd.begin(16, 2);
  //Подготавливаем информацию к выводу
  //Устанавливаем курсор в левый верхний угол
  lcd.setCursor(0, 0);
  //Т.к. Arduino IDE работает в кодировке UTF-8 то приходится писать текст через ESC последовательсности (кодировка 866)
  //В принципе можно вынести строки с текстом в отдельный файл и редактировать его другим редактором
  lcd.print("\x8B\x85\x83\x8A\x8E\x20\x8F\x88\x98\x85\x8C\x20\x8D\x80\x20\x20");
  //Устанавливаем курсор в начало второй строки
  lcd.setCursor(0, 1);
  lcd.print("\x90\x8E\x84\x8D\x8E\x8C\x20\x90\x93\x91\x91\x8A\x8E\x8C\x21");
  //Выводи все и формируем недостающий символы
  lcd.show();
}
void loop(){
  
}

