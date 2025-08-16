#include <TimeClock.h>                            // Библиотека

#define SERIAL_SPEED 9600                         // Скорость передачи данных
#define RANDOM_PIN A0                             // Пин seed
#define MIN_RAND 1                                // Минимальная задержка
#define MAX_RAND 5                                // Максимальная задержка

void setup() {                                    // Настроика порта
  Serial.begin(SERIAL_SPEED);                     // Serial
  randomSeed(digitalRead(RANDOM_PIN));            // Получить число
}                                                 // Для seed

void loop() {                                     // Главный цикл         
  uint16_t rnd = random(MIN_RAND, MAX_RAND);      // Случайное число
  Serial.print(TimeClock.seconds());              // Секунды
  Serial.write('.');                              // Разделитель
  Serial.print(TimeClock.milliseconds());         // Время 
  Serial.write('.');                              // С запуска 
  Serial.print(TimeClock.microseconds());         // Программы
  Serial.print(F(" -> "));                        // Разделитель
  Serial.print(rnd);                              // Число
  Serial.println(F(" sec."));                     // Секунд
  delay(rnd * 1000ul);                            // Подождать
}                                                 // Конец цикла

void yield() { TimeClock.tick(); }                // Тикер
