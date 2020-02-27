#include <SPI.h>
#include <SD.h>
#include <DS3232RTC.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>

const int chipSelect = 10;
int rec_pin = 2;

//String t = "";
float shuntvoltage_mV = 0;
float current_mA = 0;
int log_flag = 0;
int print_flag = 0;
String data = "";


Adafruit_INA219 ina219(0x40);
LiquidCrystal_I2C lcd(0x27, 16, 2);
File myFile;

void setup() {
  Serial.begin(115200);
  pinMode(rec_pin, INPUT);


  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }

  ina219.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TBRD");

}

void loop() {
lcd.setCursor(0, 0);
  lcd.print("TBRD");
  log_flag = digitalRead(rec_pin);
  //  t = String(year()) + "/" + String(month()) + "/" + String(day()) + "_" + String(hour()) + "-" + String(minute()) + "-" + String(second());

  shuntvoltage_mV = ina219.getShuntVoltage_mV();
  current_mA = ina219.getCurrent_mA();

  data = String(year()) + "/" + String(month()) + "/" + String(day()) + "," + String(hour()) + ":" + String(minute()) + ":" + String(second()) + "," +
         String(shuntvoltage_mV) + "," + String(current_mA);

  //  Serial.println(data);

  if (!SD.begin(chipSelect)) {
    Serial.println("is a card inserted?");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("No SD Card!   ");
  }
  else {
    Serial.println("SD is OK!");
    lcd.setCursor(7, 0);
    lcd.print("Ready!");
    if (log_flag == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Logging ....");
      Serial.println("Logging ...");

      myFile = SD.open("log.txt", FILE_WRITE);
      if (myFile) {
        if (print_flag == 0) {
          myFile.println("--------------------------------------------------------");
          myFile.println("DATA,TIME,VOLTAGE,CURRENT");
          print_flag = 1;
        }
        myFile.println(data);
        myFile.close();
      }
      else {
        Serial.println("error opening data_log file");
        lcd.setCursor(7, 0);
        lcd.print("ERR:OPN");
      }
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("Logger = OFF");
      Serial.println("recording stopped!");
      if (SD.exists("log.txt")) {
        Serial.println("logging is sucessfull");
      }
      else {
        Serial.println("No log file!");
      }
      print_flag = 0;
    }
  }


}
