#include <Keypad.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const uint8_t RELAY_PIN = 11; 
const byte ROWS = 4;
const byte COLS  = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte row_pins[ROWS]    = {2,3,4,5};
byte column_pins[COLS] = {6,7,8,9};

Keypad keypad_key = Keypad(makeKeymap(hexaKeys), row_pins, column_pins, ROWS, COLS);
char entered[4];   
char stored[4];    
char temp_buf[4];  

uint8_t i = 0;
char key_pressed = 0;
const byte EEPROM_MAGIC_ADDR = 10;
const byte EEPROM_MAGIC_VAL  = 0x42; 
inline void lockDoor()   { digitalWrite(RELAY_PIN, HIGH); } 
inline void unlockDoor() { digitalWrite(RELAY_PIN, LOW);  } 

void loadStoredPIN() {
  for (uint8_t j = 0; j < 4; j++) stored[j] = (char)EEPROM.read(j);
}
void writeDefaultIfFirstBoot() {
  if (EEPROM.read(EEPROM_MAGIC_ADDR) != EEPROM_MAGIC_VAL) {
    EEPROM.write(0, '1');
    EEPROM.write(1, '2');
    EEPROM.write(2, '3');
    EEPROM.write(3, '4');
    EEPROM.write(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_VAL);
  }
}
void initPIN() {
  writeDefaultIfFirstBoot();
  loadStoredPIN();
}
void readFourDigitsRaw(char *dst) {
  uint8_t idx = 0;
  while (idx < 4) {
    char k = keypad_key.getKey();
    if (k >= '0' && k <= '9') {
      dst[idx++] = k;
      lcd.print('*');
    }
  }
}
void change() {
  lcd.clear(); lcd.print("Current Password");
  lcd.setCursor(0,1);
  readFourDigitsRaw(temp_buf);
if (memcmp(temp_buf, stored, 4) != 0) {   
    lcd.clear(); lcd.print("Wrong Password");
    lcd.setCursor(0,1); lcd.print("Try Again");
    delay(1000);
    lcd.clear(); lcd.print("Enter Password");
    lcd.setCursor(0,1);
    return;
  }
  lcd.clear(); lcd.print("New Password:");
  lcd.setCursor(0,1);
  readFourDigitsRaw(temp_buf);
  for (uint8_t j = 0; j < 4; j++) {
    EEPROM.write(j, temp_buf[j]); 
    stored[j] = temp_buf[j];
  }

  lcd.clear(); lcd.print("Pass Changed");
  delay(1000);
  lcd.clear(); lcd.print("Enter Password");
  lcd.setCursor(0,1);
}
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  lockDoor();

  lcd.begin();
  lcd.backlight();
  lcd.print(" Jiwon's Creation ");
  lcd.setCursor(0,1);
  lcd.print("Electronic Lock ");
  delay(3000);

  lcd.clear(); lcd.print("Enter Password");
  lcd.setCursor(0,1);

  initPIN(); 
  i = 0;
}
void loop() {
  lockDoor();  

  key_pressed = keypad_key.getKey();

  if (key_pressed == '#') {
    change();
    i = 0;
    return;
  }
  if (key_pressed >= '0' && key_pressed <= '9' && i < 4) {
    entered[i++] = key_pressed;
    lcd.print('*'); 
  }

  if (i == 4) {
    loadStoredPIN();
    if (memcmp(entered, stored, 4) == 0) {
      lcd.clear(); lcd.print("Pass Accepted");
      unlockDoor();
      delay(2000);
    } else {
      lcd.clear(); lcd.print("Wrong Password");
      lcd.setCursor(0,1); lcd.print("Press # to change");
      delay(1500);
    }
    lockDoor();
    lcd.clear(); lcd.print("Enter Password");
    lcd.setCursor(0,1);
    i = 0;
  }
}

