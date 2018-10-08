#include "Feedback.h"

// Codes to send over serial, trigger audio feedback.
#define PLAIN_FEEDBACK_CODE 'A'
#define WORD_FEEDBACK_CODE 'W'
#define MACRO_FEEDBACK_CODE 'M'
#define COMMAND_FEEDBACK_CODE 'S'
#define UNKNOWN_FEEDBACK_CODE 'U'

void Feedback::setup() {
#ifdef ENABLE_RGB_LED
  for (uint8_t p = 0; p != NUM_RGB_LED_PINS; p++) {
    pinMode(conf::rgb_led_pins[p], OUTPUT);
  }
#endif
}

void Feedback::trigger(conf::SeqType type) {
  switch (type) {
    case conf::SeqType::Plain:
      triggerAudioFeedback(PLAIN_FEEDBACK_CODE);
      break;
    case conf::SeqType::Word:
      triggerAudioFeedback(WORD_FEEDBACK_CODE);
      break;
    case conf::SeqType::Macro:
      triggerAudioFeedback(MACRO_FEEDBACK_CODE);
      break;
    case conf::SeqType::Command:
      triggerAudioFeedback(COMMAND_FEEDBACK_CODE);
      break;
    default:
      DEBUG1_LN("seq type has no feedback routine");
  }
}

void Feedback::triggerUnknown() {
  triggerAudioFeedback(UNKNOWN_FEEDBACK_CODE);
  triggerLEDFeedback(LEDRoutine::UnknownFeedback);
}

void Feedback::triggerCyclingFailed() {
  triggerLEDFeedback(LEDRoutine::NoAnagramFeedback);
}

void Feedback::triggerAudioFeedback(char feedback_code) {
#ifndef ENABLE_AUDIO_TYPING_FEEDBACK
  return;
#endif
  Serial.print(feedback_code);
}

void Feedback::triggerLEDFeedback(LEDRoutine routine) {
#ifndef ENABLE_LED_TYPING_FEEDBACK
  return;
#endif
  startRoutine(routine);
}

/************** pretty colors: rgb led *************/

void Feedback::updateLED() {
  // State machine for handling LED routines
  // TODO consider replacing LEDRoutine::None with disabled led_timer
#ifndef ENABLE_RGB_LED
  return;
#endif

  if (led_timer.isRunning()) {
    // Timer hasn't run out, we don't need to do anything yet.
    return;
  }

  switch (led_routine) {
    case LEDRoutine::None:
      return;
    case LEDRoutine::Boot:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::White);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::Battery:
      switch (led_subroutine) {
        case 0:
          led_timer.start(2000);
          led_subroutine++;
          switch (battery.getLevel()) {
            case 0:
              setLEDColor(LEDColor::Red);
              break;
            case 1:
              setLEDColor(LEDColor::Orange);
              break;
            case 2:
              setLEDColor(LEDColor::Yellow);
              break;
            case 3:
              setLEDColor(LEDColor::Green);
              break;
            case 4:
              setLEDColor(LEDColor::Teal);
              break;
            default:
              // Battery not present, or bad level
              setLEDColor(LEDColor::White);
              break;
          }
          break;
        default:
          endRoutine();
          break;
      }
      break;

    case LEDRoutine::BleNoConnection:
      switch (led_subroutine) {
        case 0:
          led_timer.start(100);
          setLEDColor(LEDColor::DimBlue);
          led_subroutine++;
          break;
        default:
          endRoutine();
          break;
      }
      break;

    case LEDRoutine::FlashGreen:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::Green);
          led_subroutine++;
          break;
        default:
          led_timer.start(500);
          setLEDColor(LEDColor::Black);
          led_subroutine = 0;
      }
      break;

    case LEDRoutine::FlashRed:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::Red);
          led_subroutine++;
          break;
        default:
          led_timer.start(500);
          setLEDColor(LEDColor::Black);
          led_subroutine = 0;
      }
      break;

    case LEDRoutine::PlainFeedback:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::Blue);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::MacroFeedback:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::Yellow);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::WordFeedback:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::Green);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::UnknownFeedback:
      switch (led_subroutine) {
        case 0:
          led_timer.start(100);
          setLEDColor(LEDColor::Red);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::NoAnagramFeedback:
      switch (led_subroutine) {
        case 0:
          led_timer.start(100);
          setLEDColor(LEDColor::Magenta);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::CommandFeedback:
      switch (led_subroutine) {
        case 0:
          led_timer.start(500);
          setLEDColor(LEDColor::Orange);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::Warning:
      switch (led_subroutine) {
        case 0:
          led_timer.start(700);
          setLEDColor(LEDColor::Orange);
          led_subroutine++;
          break;
        default:
          endRoutine();
      }
      break;

    case LEDRoutine::ToggleWireless:
      if (led_subroutine == 6) {
        endRoutine();
      } else if (led_subroutine % 2 == 0) {
        led_timer.start(500);
        setLEDColor(LEDColor::Purple);
      } else {
        led_timer.start(500);
        setLEDColor(LEDColor::Black);
      }
      led_subroutine++;
      break;

    case LEDRoutine::AllColors:
      // Use subroutine counter to iterate through colors
      if (led_subroutine >= static_cast<uint16_t>(LEDColor::NumColors)) {
        endRoutine();
      } else {
        led_timer.start(500);
        setLEDColor(static_cast<LEDColor>(led_subroutine));
        led_subroutine++;
      }
      break;

    case LEDRoutine::Rainbow:
      if (led_subroutine < 256) {
        // yellow->green
        setLEDRGB(255 - led_subroutine, 255, 0);
      } else if (led_subroutine < 256 * 2) {
        // green->teal
        setLEDRGB(0, 255, led_subroutine);
      } else if (led_subroutine < 256 * 3) {
        // teal->blue
        setLEDRGB(0, 255 - led_subroutine, 255);
      } else if (led_subroutine < 256 * 4) {
        // blue->purple
        setLEDRGB(led_subroutine, 0, 255);
      } else if (led_subroutine < 256 * 5) {
        // purple->red
        setLEDRGB(255, 0, 255 - led_subroutine);
      } else if (led_subroutine < 256 * 6) {
        // red->yellow
        setLEDRGB(255, led_subroutine, 0);
      } else {
        // off-by-one, but whatever
        led_subroutine = 0;
      }
      led_timer.start(3);
      led_subroutine++;
      break;

    default:
      DEBUG1("WARNING: invalid LED routine: ");
      DEBUG1_LN(led_routine);
  }
}

void Feedback::startRoutine(LEDRoutine routine) {
#ifndef ENABLE_RGB_LED
  return;
#endif
  led_routine = routine;
  led_subroutine = 0;
  led_timer.disable();
  setLEDColor(LEDColor::Black);
}

void Feedback::endRoutine() { startRoutine(LEDRoutine::None); }

void Feedback::setLEDColor(LEDColor color) {
  switch (color) {
    case LEDColor::Black:
      setLEDRGB(0, 0, 0);
      break;
    case LEDColor::White:
      setLEDRGB(255, 255, 255);
      break;
    case LEDColor::Red:
      setLEDRGB(255, 0, 0);
      break;
    case LEDColor::Orange:
      setLEDRGB(255, 170, 0);
      break;
    case LEDColor::Yellow:
      setLEDRGB(255, 255, 0);
      break;
    case LEDColor::Green:
      setLEDRGB(0, 255, 0);
      break;
    case LEDColor::Teal:
      setLEDRGB(0, 255, 170);
      break;
    case LEDColor::Blue:
      setLEDRGB(0, 0, 255);
      break;
    case LEDColor::DimBlue:
      setLEDRGB(0, 0, 170);
      break;
    case LEDColor::Purple:
      setLEDRGB(160, 0, 255);
      break;
    case LEDColor::Magenta:
      setLEDRGB(220, 0, 255);
      break;
    default:
      DEBUG1_LN("WARNING: unknown color");
      break;
  }
}

void Feedback::setLEDRGB(uint8_t red, uint8_t green, uint8_t blue) {
#ifdef ENABLE_RGB_LED
  // gamma correction lookup for RGB LED, from adafruit
  static const uint8_t gamma8[] = {
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,
      2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,
      4,   5,   5,   5,   5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,
      8,   9,   9,   9,   10,  10,  10,  11,  11,  11,  12,  12,  13,  13,  13,
      14,  14,  15,  15,  16,  16,  17,  17,  18,  18,  19,  19,  20,  20,  21,
      21,  22,  22,  23,  24,  24,  25,  25,  26,  27,  27,  28,  29,  29,  30,
      31,  32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  39,  40,  41,  42,
      43,  44,  45,  46,  47,  48,  49,  50,  50,  51,  52,  54,  55,  56,  57,
      58,  59,  60,  61,  62,  63,  64,  66,  67,  68,  69,  70,  72,  73,  74,
      75,  77,  78,  79,  81,  82,  83,  85,  86,  87,  89,  90,  92,  93,  95,
      96,  98,  99,  101, 102, 104, 105, 107, 109, 110, 112, 114, 115, 117, 119,
      120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142, 144, 146,
      148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175, 177,
      180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
      215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252,
      255};

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
