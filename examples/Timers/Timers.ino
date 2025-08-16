#include <LongPeriodTimer.h>                   // Библиотека

#define SERIAL_SPEED 9600                      // Скорость передачи данных 

LongPeriodTimer tmr1;                          // Таймеры (Можно сделать static)
LongPeriodTimer tmr2;                          // В loop()
LongPeriodTimer tmr3;                          // Период по умолчанию - 1 секунда

typedef LongPeriodTimer ltmr;                  // Короткое название
ltmr tmr4;                                     // Еще таймер

void func_tmr_1(mode_t type) {                 // Обработчик (имя аргумента - произвольное)
  Serial.println(F("Period!!!"));              // Периодический
  type = TMR_PERIOD;                           // TMR_PERIOD - Режим периода (По умолчанию)
}                                              // Вывод данных

void func_tmr_2(mode_t _T) {                   // Обработчик
  Serial.println(F("Timer!!!"));               // Режим таймера
  _T = TMR_TIMER;                              // TMR_TIMER - Режим таймера
}                                              // Сработает один раз

void func_tmr_3(mode_t mode_tmr) {             // Прошло 10 секунд после запуска
  mode_tmr = TMR_LOOP;                         // TMR_LOOP - После периода - крутиться в цикле
  static ltmr tmr; static bool flag;           // Статический таймер и флаг
  if (tmr)                                     // Условие таймера
    digitalWrite(LED_BUILTIN, flag = !flag);   // Инвертируем пин
}                                              // Со светодиодом

void setup() {                                 // Вывод в порт
  Serial.begin(SERIAL_SPEED);                  // Подключаем
  pinMode(LED_BUILTIN, OUTPUT);                // Настраиваем
  tmr1.attach(func_tmr_1);                     // Таймер 1
  tmr1.setPeriod(5);                           // Период - в секундах
  tmr2.attach(func_tmr_2);                     // Максимум - 136 лет
  tmr2.setPeriod(2);                           // Таймеры работают в
  tmr3.attach(func_tmr_3);                     // Обработчиках
  tmr3.setPeriod(10);                          // Через 10 секунд после запуска
}                                              // Начнем моргать светодиодом

void loop() {                                  // В главном цикле - только тикер
  tmr1.tick();                                 // Тикер
  tmr2;                                        // Или так
  if (tmr4) Serial.println(F("Hello!!!"));     // Можно по условию
}                                              // Тикер автоматический
