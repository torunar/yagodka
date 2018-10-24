// Sketch > Include library > HID-Project (https://github.com/NicoHood/HID)
#include <HID-Project.h>
#include <HID-Settings.h>
#include <Bounce2.h>

#define PIN_PREV 12
#define PIN_PLAY 10
#define PIN_NEXT 8

#define ACTION_PREV 1
#define ACTION_PLAY 2
#define ACTION_NEXT 3

Bounce prev = Bounce(); 
Bounce play = Bounce();
Bounce next = Bounce();

bool s_prev = false;
bool s_play = false;
bool s_next = false;

// false: Arrow left, Arrow right and Space button events are triggered
// true:  Previous, Next and Play/Pause media events are triggered
bool is_media = true;

void attachBtnToPin(Bounce &btn, int pin, int interval = 500)
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

void simulateKey(Bounce &btn, byte action, bool &btn_state)
{
  if (readBtn(btn) != btn_state) {    
    if (action == ACTION_PREV) {
      if (is_media) {
        Consumer.write(MEDIA_PREVIOUS);
      } else {
        Keyboard.write(KEY_LEFT_ARROW);
      }
    } else if (action == ACTION_NEXT) {
        if (is_media) {
          Consumer.write(MEDIA_NEXT);
        } else {
          Keyboard.write(KEY_RIGHT_ARROW);
        }
    } else {
        if (is_media) {
          Consumer.write(MEDIA_PLAY_PAUSE);
        } else {
          Keyboard.write(' ');
        }
    }
    
    btn_state = !btn_state;
  }
}

void setup()
{
  attachBtnToPin(prev, PIN_PREV);
  attachBtnToPin(next, PIN_NEXT);
  attachBtnToPin(play, PIN_PLAY);

  if (is_media) {
    Consumer.begin();
  } else {
    Keyboard.begin();
  }
}

void loop()
{
  simulateKey(prev, ACTION_PREV, s_prev);
  simulateKey(next, ACTION_NEXT, s_next);
  simulateKey(play, ACTION_PLAY, s_play);
}
