#include "DigiKeyboard.h"


#define PIN_LED 1
#define IR_PIN 2
#define DATA_SIZE 20
#define START_BIT 4000

#define KEY_ARROW_UP        45
#define KEY_ARROW_DOWN      39
#define KEY_ARROW_LEFT      32
#define KEY_ARROW_RIGHT     40
#define KEY_SPACE     43
#define KEY_WIN_D     47
#define KEY_WIN_D_SPACE     37
#define KEY_VOLUME_UP   42
#define KEY_VOLUME_DOWN   35




void setup()
{
  pinMode(IR_PIN, INPUT);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, 0);
}

int resultIR();

void loop()
{
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);

  int result = resultIR();

  if (result != 0) {
    
    //DigiKeyboard.println(result);
    
    switch (result) {
      case KEY_ARROW_UP:
        DigiKeyboard.sendKeyStroke (82);
        break;
      case KEY_ARROW_DOWN:
        DigiKeyboard.sendKeyStroke (81);
        break;
      case KEY_ARROW_LEFT:
        DigiKeyboard.sendKeyStroke (80);
        break;
      case KEY_ARROW_RIGHT:
        DigiKeyboard.sendKeyStroke (79);
        break;
      case KEY_SPACE:
        DigiKeyboard.sendKeyStroke (44);
        break;
      case KEY_WIN_D:
        DigiKeyboard.sendKeyStroke (7, MOD_GUI_LEFT);
        break;
      case KEY_WIN_D_SPACE:
        DigiKeyboard.sendKeyStroke (44);
        DigiKeyboard.sendKeyStroke (7, MOD_GUI_LEFT);
        break;
      case KEY_VOLUME_UP:
        DigiKeyboard.sendKeyStroke (128);
        break;
      case KEY_VOLUME_DOWN:
        DigiKeyboard.sendKeyStroke (129);
        break;
      default :
        break;
    }

    
    digitalWrite(PIN_LED, 1);
    DigiKeyboard.delay(20);
    digitalWrite(PIN_LED, 0);
  }
}


int resultIR() {
  if (pulseIn(IR_PIN, HIGH) > START_BIT)
  {
    int data[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
      data[i] = pulseIn(IR_PIN, HIGH);
    }

    int result = 0;
    for (int i = 12; i < DATA_SIZE; i++) {
      if (data[i] > 1000) {
        result |= (1 << (DATA_SIZE - 1 - i));
      }
    }
    return result;
  }
  return 0;
}
