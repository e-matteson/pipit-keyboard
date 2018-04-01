#include "Feedback.h"

// Codes to send over serial, trigger audio feedback.
#define PLAIN_FEEDBACK_CODE 'A'
#define WORD_FEEDBACK_CODE 'W'
#define MACRO_FEEDBACK_CODE 'M'
#define COMMAND_FEEDBACK_CODE 'S'
#define UNKNOWN_FEEDBACK_CODE 'U'


Feedback::Feedback(){
  battery = new Battery;
  led_timer = new Timer();

#ifdef ENABLE_RGB_LED
  for(uint8_t p = 0; p != NUM_RGB_LED_PINS; p++){
    pinMode(conf::rgb_led_pins[p], OUTPUT);
  }
#endif
}

void Feedback::trigger(conf::seq_type_enum type){
  switch(type) {
    case conf::PLAIN:
      triggerAudioFeedback(PLAIN_FEEDBACK_CODE);
      // triggerLEDFeedback(PLAIN_FEEDBACK_ROUTINE);
      break;
    case conf::WORD:
      triggerAudioFeedback(WORD_FEEDBACK_CODE);
      // triggerLEDFeedback(WORD_FEEDBACK_ROUTINE);
      break;
    case conf::MACRO:
      triggerAudioFeedback(MACRO_FEEDBACK_CODE);
      // triggerLEDFeedback(MACRO_FEEDBACK_ROUTINE);
      break;
    case conf::COMMAND:
      triggerAudioFeedback(COMMAND_FEEDBACK_CODE);
      // triggerLEDFeedback(COMMAND_FEEDBACK_ROUTINE);
      break;
    default: DEBUG1_LN("seq type has no feedback routine");
  }
}

void Feedback::triggerUnknown(){
  triggerAudioFeedback(UNKNOWN_FEEDBACK_CODE);
  triggerLEDFeedback(UNKNOWN_FEEDBACK_ROUTINE);
}

void Feedback::triggerNoAnagram(){
  triggerLEDFeedback(NO_ANAGRAM_FEEDBACK_ROUTINE);
}

void Feedback::triggerAudioFeedback(char feedback_code){
#ifndef ENABLE_AUDIO_TYPING_FEEDBACK
  return;
#endif
  Serial.print(feedback_code);
}

void Feedback::triggerLEDFeedback(led_routine_enum routine){
#ifndef ENABLE_LED_TYPING_FEEDBACK
  return;
#endif
  startRoutine(routine);
}


/************** pretty colors: rgb led *************/

void Feedback::updateLED(){
  // State machine for handling LED routines
  // TODO consider replacing NO_ROUTINE with disabled led_timer
#ifndef ENABLE_RGB_LED
  return;
#endif

  if(led_timer->isRunning()){
    // Timer hasn't run out, we don't need to do anything yet.
    return;
  }

  switch(led_routine){
  case NO_ROUTINE:
    return;
  case BOOT_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(500);
      setLEDColor(WHITE);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case BATTERY_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(2000);
      led_subroutine++;
      // Serial.println(battery->getLevel());
      switch(battery->getLevel()){
      case 0:
        setLEDColor(RED);
        break;
      case 1:
        setLEDColor(ORANGE);
        break;
      case 2:
        setLEDColor(YELLOW);
        break;
      case 3:
        setLEDColor(GREEN);
        break;
      case 4:
        setLEDColor(TEAL);
        break;
      default:
        // Battery not present, or bad level
        setLEDColor(WHITE);
        break;
      }
      break;
    default:
      endRoutine();
      break;
    }
    break;

  case BLE_NO_CONNECTION_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(100);
      setLEDColor(DIM_BLUE);
      led_subroutine++;
      break;
    default:
      endRoutine();
      break;
    }
    break;

  case FLASH_GREEN_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(500);
      setLEDColor(GREEN);
      led_subroutine++;
      break;
    default:
      led_timer->start(500);
      setLEDColor(BLACK);
      led_subroutine = 0;
    }
    break;

  case FLASH_RED_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(500);
      setLEDColor(RED);
      led_subroutine++;
      break;
    default:
      led_timer->start(500);
      setLEDColor(BLACK);
      led_subroutine = 0;
    }
    break;

  case PLAIN_FEEDBACK_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(500);
      setLEDColor(BLUE);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case MACRO_FEEDBACK_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(500);
      setLEDColor(YELLOW);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case WORD_FEEDBACK_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(500);
      setLEDColor(GREEN);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case UNKNOWN_FEEDBACK_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(100);
      setLEDColor(RED);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case NO_ANAGRAM_FEEDBACK_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start(100);
      setLEDColor(MAGENTA);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case COMMAND_FEEDBACK_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start( 500);
      setLEDColor(ORANGE);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case WARNING_ROUTINE:
    switch(led_subroutine){
    case 0:
      led_timer->start( 700);
      setLEDColor(ORANGE);
      led_subroutine++;
      break;
    default:
      endRoutine();
    }
    break;

  case SHUTDOWN_ROUTINE:
    if(led_subroutine == 6){
      endRoutine();
    }
    else if(led_subroutine % 2 == 0){
      led_timer->start(500);
      setLEDColor(PURPLE);
    }
    else{
      led_timer->start(500);
      setLEDColor(BLACK);
    }
    led_subroutine++;
    break;

  case ALL_COLORS_ROUTINE:
    if(led_subroutine == BLACK){
      endRoutine();
    }
    else{
      led_timer->start(500);
      setLEDColor((led_color_enum) led_subroutine);
      led_subroutine++;
    }
    break;

  case RAINBOW_ROUTINE:
    if(led_subroutine < 256){
      // yellow->green
      setLEDRGB(255 - led_subroutine, 255, 0);
    }
    else if(led_subroutine < 256*2){
      // green->teal
      setLEDRGB(0, 255, led_subroutine);
    }
    else if(led_subroutine < 256*3){
      // teal->blue
      setLEDRGB(0, 255 - led_subroutine, 255);
    }
    else if(led_subroutine < 256*4){
      // blue->purple
      setLEDRGB(led_subroutine, 0, 255);
    }
    else if(led_subroutine < 256*5){
      // purple->red
      setLEDRGB(255, 0, 255 - led_subroutine);
    }
    else if(led_subroutine < 256*6){
      // red->yellow
      setLEDRGB(255, led_subroutine, 0);
    }
    else{
      // off-by-one, but whatever
      led_subroutine = 0;
    }
    led_timer->start(3);
    led_subroutine++;
    break;

  default:
    DEBUG1("WARNING: invalid LED routine: ");
    DEBUG1_LN(led_routine);
  }
}


void Feedback::startRoutine(led_routine_enum routine){
#ifndef ENABLE_RGB_LED
  return;
#endif
  led_routine = routine;
  led_subroutine = 0;
  led_timer->disable();
  setLEDColor(BLACK);
}

void Feedback::endRoutine(){
  startRoutine(NO_ROUTINE);
}


void Feedback::setLEDColor(led_color_enum color){
  switch(color){
  case BLACK:
    setLEDRGB(0, 0, 0);
    break;
  case WHITE:
    setLEDRGB(255, 255, 255);
    break;
  case RED:
    setLEDRGB(255, 0, 0);
    break;
  case ORANGE:
    setLEDRGB(255, 170, 0);
    break;
  case YELLOW:
    setLEDRGB(255, 255,  0);
    break;
  case GREEN:
    setLEDRGB(0, 255, 0);
    break;
  case TEAL:
    setLEDRGB(0, 255, 170);
    break;
  case BLUE:
    setLEDRGB(0, 0, 255);
    break;
  case DIM_BLUE:
    setLEDRGB(0, 0, 170);
    break;
  case PURPLE:
    setLEDRGB(160, 0, 255);
    break;
  case MAGENTA:
    setLEDRGB(220, 0, 255);
    break;
  default:
    DEBUG1_LN("WARNING: unknown color");
    break;
  }
}

void Feedback::setLEDRGB(uint8_t red, uint8_t green, uint8_t blue){
#ifdef ENABLE_RGB_LED
  // gamma correction lookup for RGB LED, from adafruit
  static const uint8_t gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
    115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
    144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
    177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
    215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

  analogWrite(conf::rgb_led_pins[0], gamma8[red]);
  analogWrite(conf::rgb_led_pins[1], gamma8[green]);
  analogWrite(conf::rgb_led_pins[2], gamma8[blue]);
#endif

  // For debugging
  // Serial.print("(");
  // Serial.print(gamma8[red]);
  // Serial.print(",");
  // Serial.print(gamma8[green]);
  // Serial.print(",");
  // Serial.print(gamma8[blue]);
  // Serial.println(")");
 }
