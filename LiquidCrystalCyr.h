#ifndef __LIQUIDCRYSTALCYR_H
#define __LIQUIDCRYSTALCYR_H

#include <LiquidCrystal.h>

//Указать под свой дисплей в данном случае указано для 1602
//Число символов в строке на экране LCD
#define LCD_COLS          16
//Число строк на экране LCD
#define LCD_ROWS          2

////////////////////////////////////////////////////////////////
//Число байт на 1 символ шрифта
#define BYTES_PER_SYMBOL  8
//Число пользовательских символов (зависит от самого дисплея)
#define LCD_USER_CHARS    8

class LiquidCrystalCyr : public LiquidCrystal{
  uint8_t lcd_buf[LCD_ROWS][LCD_COLS];
  uint8_t buf[BYTES_PER_SYMBOL];
  uint8_t _numrows;
  uint8_t _numcols;
  uint8_t _flag_refresh;
  
public:
  uint8_t _x, _y;
  LiquidCrystalCyr(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
  void show();
  void setCursor(uint8_t, uint8_t); 
  virtual size_t write(unsigned char);
  //using Print::write;
  //using LiquidCrystal::write;
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  //virtual size_t write(const uint8_t *buffer, size_t size);
  void clear();
  void createChar(uint8_t location, uint8_t charmap[]);
};

#endif

