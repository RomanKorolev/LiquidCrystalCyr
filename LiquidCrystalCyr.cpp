#include "LiquidCrystalCyr.h"

//КОНСТАНТЫ В PROGMEM Кодировка выводимых на экран строк должна быть такой же как указана в LCD_CHARSET (либо CP1251, либо CP866)
const unsigned char LCDKirillicRecodingMap [] PROGMEM= {//таблица перекодировки кириллических символов	
	0x41, 0x00, 0x42, 0x01, 0x02, 0x45, 0x03, 0x04,				//АБВГДЕЖЗ
	0x05, 0x06, 0x4b, 0x07, 0x4d, 0x48, 0x4f, 0x08,				//ИЙКЛМНОП
	0x50, 0x43, 0x54, 0x09, 0x0a, 0x58, 0x0b, 0x0c,				//РСТУФХЦЧ
	0x0d, 0x0e, 0x0f, 0x10, 0x62, 0x11, 0x12, 0x13				//ШЩЪЫЬЭЮЯ
};

const unsigned char LCDKirillicFont [] PROGMEM= {//битовый массив кириллических символов
	0b11111,0b10001,0b10000,0b11110,0b10001,0b10001,0b11110,0b00000,	//Б (0)
	0b11111,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b00000,	//Г (1)
	0b01111,0b00101,0b00101,0b01001,0b10001,0b11111,0b10001,0b10001,	//Д (2)
	0b10101,0b10101,0b10101,0b01110,0b10101,0b10101,0b10101,0b00000,	//Ж (3)
	0b11110,0b00001,0b00001,0b00110,0b00001,0b00001,0b11110,0b00000,	//З (4)
	0b10001,0b10001,0b10011,0b10101,0b11001,0b10001,0b10001,0b00000,	//И (5)
	0b00100,0b10101,0b10001,0b10011,0b10101,0b11001,0b10001,0b00000,	//Й (6)
	0b01111,0b00101,0b00101,0b00101,0b00101,0b10101,0b01001,0b00000,	//Л (7)
	0b11111,0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b00000,	//П (8)
	0b10001,0b10001,0b10001,0b01010,0b00100,0b01000,0b10000,0b00000,	//У (9)
	0b01110,0b10101,0b10101,0b10101,0b01110,0b00100,0b00100,0b00000,	//Ф (10)
	0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b11111,0b00001,	//Ц (11)
	0b10001,0b10001,0b10001,0b01111,0b00001,0b00001,0b00001,0b00000,	//Ч (12)
	0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00000,	//Ш (13)
	0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00001,	//Щ (14)
	0b11000,0b01000,0b01000,0b01110,0b01001,0b01001,0b01110,0b00000,	//Ъ (15)
	0b10001,0b10001,0b10001,0b11001,0b10101,0b10101,0b11001,0b00000,	//Ы (16)
	0b01110,0b10001,0b00101,0b01011,0b00001,0b10001,0b01110,0b00000,	//Э (17)
	0b10010,0b10101,0b10101,0b11101,0b10101,0b10101,0b10010,0b00000,	//Ю (18)
	0b01111,0b10001,0b10001,0b01111,0b00101,0b01001,0b10001,0b00000		//Я (19)
};

//Реализован только один вариант конструктора для самого сокращенного варианта подключения 4х битный режим
LiquidCrystalCyr::LiquidCrystalCyr(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : LiquidCrystal(rs, enable, d0, d1, d2, d3){
  _x = _y = 0;
}

//Переопределяем метод установки курсора
void LiquidCrystalCyr::setCursor(uint8_t x, uint8_t y){
  if(y < _numrows){
    _y = y;
  }
  if(x < _numcols){
    _x = x;
  }
}

void LiquidCrystalCyr::begin(uint8_t cols, uint8_t rows, uint8_t charsize){
  LiquidCrystal::begin(cols, rows, charsize);
  _numrows = (rows < LCD_ROWS) ? rows : LCD_ROWS;
  _numcols = (cols < LCD_COLS) ? cols : LCD_COLS;
  clear();
}

//Переопределяем метод LiquidCrystal::write
//Пишем во внутренний в буфер вместо LCD
size_t LiquidCrystalCyr::write(uint8_t ch){
  if(lcd_buf[_y][_x] != ch){
    _flag_refresh = 1;
    lcd_buf[_y][_x] = ch;
  }
  _x++;
  if(_x >=  _numcols){
    if(_y < _numrows - 1){
      _y++;
      _x = 0;
    }else{
      _x = _numcols - 1;
    }
  }
  return 1;
}

//Метод показывает текст, который был подготовлен с помощью методов print
void LiquidCrystalCyr::show(){
  //Если нет никаких изменений, то ничего не выводим на экран
  if(!_flag_refresh){
    return;
  }
  _flag_refresh = 0;
  uint8_t loaded_map[LCD_USER_CHARS];
  uint8_t loaded_chars_cnt = 0;
  //Загружаем текст из буфера в памяти в LCD
  for(uint8_t y = 0; y < _numrows; y++){
    LiquidCrystal::setCursor(0, y);
    for(uint8_t x = 0; x < _numcols; x++){
      uint8_t ch = lcd_buf[y][x];
#if LCD_CHARSET == CP866
      if(ch >= 0x80 && ch < 0xA0){
#endif
#if LCD_CHARSET == CP1251
      if(ch >= 0xA0 && ch < 0xC0){
#endif
        uint8_t found = 0;
        for(uint8_t i = 0; i < loaded_chars_cnt; i++){
          if(ch == loaded_map[i]){
            found = 1;
            ch = i;
            break;
          }
        }
        //Если символ еще не находится в массиве загружаемых пользователем
        if(!found){
          PGM_P p = reinterpret_cast<PGM_P>(LCDKirillicRecodingMap + ch - 0x80);
          ch = pgm_read_byte(p);
          if(ch <= 0x13){
            if(loaded_chars_cnt >= LCD_USER_CHARS){
              ch = '?'; //Если все доступные 8 пользовательских символов уже использованы
            }else{
              loaded_map[loaded_chars_cnt] = ch;
              ch = loaded_chars_cnt++;
            }
          }
        }
      }
      //Реально пишем символ в LCD
      LiquidCrystal::write(ch);
    }
  }

  // Загружаем шрифты
  // К сожалению метод LiquidCrystal::createChar, вызывает LiquidCrystalCyr::write
  // поэтому пришлось колхозить на низком уровне, загружаем сразу все символы
  command(LCD_SETCGRAMADDR);
  for(uint8_t k = 0; k < loaded_chars_cnt; k++){
    PGM_P p = reinterpret_cast<PGM_P>(LCDKirillicFont + loaded_map[k] * BYTES_PER_SYMBOL);
    for(uint8_t i = 0; i < BYTES_PER_SYMBOL; i++){
      LiquidCrystal::write(pgm_read_byte(p++));
      //send(pgm_read_byte(p++), 1);
    }
  }
  /*
  for(uint8_t k = 0; k < loaded_chars_cnt; k++){
    uint8_t p = loaded_map[k] * BYTES_PER_SYMBOL;
    uint8_t buf[BYTES_PER_SYMBOL];
    for(uint8_t i = 0; i < BYTES_PER_SYMBOL; i++){
      buf[i] = read_font_byte(p++);
    }
    createChar(k, buf);
  }
  */
  //Авто перевод курсора, хотя возможно это лишнее
  //В любом случае после загрузки пользовательских символов нужно выйти из этого режима
  //Т.е. послать команду
  setCursor(0, 0);
}

void LiquidCrystalCyr::clear(){
  LiquidCrystal::clear();
  clear_buf();
}

void LiquidCrystalCyr::clear_buf(){
  _x = _y = 0;
  for(uint8_t y = 0; y < _numrows; y++){
    for(uint8_t x = 0; x < _numcols; x++){
      lcd_buf[y][x] = ' ';
    }
  }
  _flag_refresh = 1;
}

void LiquidCrystalCyr::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    LiquidCrystal::write(charmap[i]);
  }
  command(LCD_SETDDRAMADDR);  //Костыль чтобы выйти из этого режима
}

