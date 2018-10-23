#include <Bounce2.h>
#include <Keyboard.h>

#define PIN_RIGHT 11
#define PIN_SPACE 12
#define PIN_LEFT  13

#define KEY_SPACE 32

Bounce left  = Bounce(); 
Bounce space = Bounce();
Bounce right = Bounce();

bool s_left  = false;
bool s_space = false;
bool s_right = false;

void attachBtnToPin(Bounce &btn, int pin, int interval = 2)
{
  pinMode(pin, INPUT_PULLUP);
  btn.attach(pin);
  btn.interval(interval);
}

bool readBtn(Bounce &btn)
{
  btn.update();
  
  return !btn.read();
}

void simulateKey(Bounce &btn, char key, bool &btn_state)
{
  if (readBtn(btn) != btn_state) {
    Keyboard.write(key);
    btn_state = !btn_state;
  }
}

void setup()
{
  attachBtnToPin(left,  PIN_LEFT);
  attachBtnToPin(right, PIN_RIGHT);
  attachBtnToPin(space, PIN_SPACE);

  Keyboard.begin();
}

void loop()
{
  simulateKey(left,  KEY_LEFT_ARROW,  s_left);
  simulateKey(right, KEY_RIGHT_ARROW, s_right);
  simulateKey(space, KEY_SPACE,       s_space);
}
