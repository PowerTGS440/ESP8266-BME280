// █████████████████████████████████████████████████████
//
// ESP32/ESP8266 BlackBook by PowerTGS (2024)
//
// author : Tomasz Majcher 
// e-mail : powerTGS440@gmail.com
// phone  : +48 668 082121
//
// █████████████████████████████████████████████████████
//
// BME280 demo file
//
// source file      : sourcce/sensor/bme280/bme280.ino
// device           : esp32/esp2866/arduino uno/arduino nano/arduono mega
// code platform    : ArduinoIDE
// 
// █████████████████████████████████████████████████████
// M A K R O
// █████████████████████████████████████████████████████
                                    
#define SEALEVELPRESSURE_HPA  (1013.25)
#define SERIAL        true                         // SERIAL włączony
#define SERIAL_SPEED  115200                       // prędkość SERIAL
#define LOOP_DELAY    10000                        // opóźnienie pętli LOOP 

// █████████████████████████████████████████████████████
// B I B L I O T E K I
// █████████████████████████████████████████████████████                                                                                                                                                                                                                                          

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// █████████████████████████████████████████████████████
// O B I E K T   K L A S Y   B M E 2 8 0
// █████████████████████████████████████████████████████

Adafruit_BME280 bme; 

// █████████████████████████████████████████████████████
// Z M I E N N E   G L O B A L N E
// █████████████████████████████████████████████████████

float   temperatura = 0;
float   cisnienie = 0;
float   wilgotnosc = 0;
float   wysokosc = 0;

// █████████████████████████████████████████████████████
// D E K L A R A C J E   F U N K C J I
// █████████████████████████████████████████████████████

void Read_BME_280_Sensor (float &temp, float &pres, float &humi, float &alti);
void Show_BME_280_Sensor (float &temp, float &pres, float &humi, float &alti);

// █████████████████████████████████████████████████████
// S E T U P
// █████████████████████████████████████████████████████

void setup() 
{
  #if SERIAL
      Serial.begin(115200);
      Serial.println();Serial.println();
  #endif
  
  bool status = bme.begin(0x76);      // inicjalizacja czujnika BME230, jeśli podłączenie
                                      // jest poprawne zwróci wartość TRUE, w przeciwnym
                                      // wartość FALSE
  
  if (!status) 
  {     
      #if SERIAL
          Serial.println(F("Nie można odnaleźć czujnika BME280"));
          Serial.println(F("Sprawdź podłączenia do urządzenia!"));
      #endif
      
      while (1);
  }
  else
  {
      #if SERIAL
          Serial.println(F("Pomyślnie zainicjalizowano czujnik BME280"));          
      #endif
  }  
}

// █████████████████████████████████████████████████████
// L O O P
// █████████████████████████████████████████████████████

void loop() 
{ 
    Read_BME_280_Sensor(temperatura, cisnienie, wilgotnosc, wysokosc);
    Show_BME_280_Sensor(temperatura, cisnienie, wilgotnosc, wysokosc);
  
    delay(LOOP_DELAY);
}

// █████████████████████████████████████████████████████
// R E A D   B M E   2 8 0   S E N S O R
// █████████████████████████████████████████████████████
// funkcja odczytuje wartości z czujnika BME_280
// zwraca wartości temperatury, cisnienia, wilgotnosci, wysokosci
// na wejsciu otrzymuje adresy zmiennych globalnych
// █████████████████████████████████████████████████████

void Read_BME_280_Sensor (float &temp, float &pres, float &humi, float &alti)
{
    #if SERIAL
        Serial.println(F("[BME280_Sensor] Odczytuje wartosci z czujnika "));
    #endif
    
    temp = bme.readTemperature();
    pres = bme.readPressure() / 100.0F;
    humi = bme.readHumidity();
    alti = bme.readAltitude(SEALEVELPRESSURE_HPA);    
}

// █████████████████████████████████████████████████████
// S H O W   B M E   2 8 0   S E N S O R
// █████████████████████████████████████████████████████
// Funkcja wypisuje wartości z czujnika BME_280, na wejsciu otrzymuje adresy zmiennych 
// globalnych. 
// wartości są wyświetlane jeśli makro SERIAL jest true, w przypadku ustawienia false
// cała zawartość pomiędzy #if SERIAL ... #endif jest pomijana przy kompilacji szkicu
// i nie istnieje w pliku binarnym. To jeden ze sposobów na optymalizację kodu oraz
// oszczędność pamięci RAM I PROGMEM
// █████████████████████████████████████████████████████

void Show_BME_280_Sensor (float &temp, float &pres, float &humi, float &alti)
{
    #if SERIAL
        Serial.print(F("[BME280_Sensor] Temperatura = "));
        Serial.print(temp);
        Serial.println(F(" *C"));  
        Serial.print(F("[BME280_Sensor] Cisnienie = "));
        Serial.print(pres);
        Serial.println(F(" hPa"));
        Serial.print(F("[BME280_Sensor] Średnia wysokość = "));
        Serial.print(alti);
        Serial.println(F(" m"));
        Serial.print(F("[BME280_Sensor] Wilgotność = "));
        Serial.print(humi);
        Serial.println(F(" %"));
        Serial.println();    
    #endif
}

// █████████████████████████████████████████████████████
// END OF FILE : src/sensor/bme280/bme280.ino
// █████████████████████████████████████████████████████
