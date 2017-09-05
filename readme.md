# LiquidCrystalCyr

Библиотека предназначена для работы с LCD дисплеями на базе совместимого контроллера HD44780,
в которых нет поддержки русских символов ВООБЩЕ.
В основе данной библиотеки стандартная библиотека LiquidCrystal из комплекта Arduino.
Библиотека предполагает, что русские символы, выводимые на экран при помощи метода print
находятся в кодировке указанной в константе LCD_CHARSET (по умолчанию windows-1251/cp1251).
Это несколько неудобно, т.к. в среде Arduino IDE работа с файлами идет исключительно в 
кодировке UTF-8. Но при желании, можно использовать перекодировку из UTF-8 в LCD_CHARSET, 
в том числе и налету, если это позволяют ресурсы МК.

Arduino module LiquidCrystalCyr with Cyrillic symbols

Shield like this one http://blog.rchip.ru/obzor-lcd-modulya-keypad/

WARNING! TOP SECRET! THIS IS VERY ULTRA HIGH TOP SECRET GALACTIC SCALE WORK! ALL WHO READ THIS TEXT IS DEAD!
USE IT ON YOUR OWN RISK!
