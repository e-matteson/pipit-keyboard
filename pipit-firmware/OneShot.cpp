#include "OneShot.h"

#ifndef TEENSY_LC
#error "OneShot implementation is specific to TEENSY_LC"
#endif

/// The user-provided interrupt service routine.
static voidFuncPtr _callback = nullptr;
static volatile KINETISK_PIT_CHANNEL_t* channel = KINETISK_PIT_CHANNELS;

OneShot* OneShot::getInstance() {
  static OneShot singleton = OneShot();
  return &singleton;
}

OneShot::OneShot() {
  // setup clock for PIT (periodic interrupt timer)
  SIM_SCGC6 |= SIM_SCGC6_PIT;

  // enable PIT module
  PIT_MCR = 0;

  enableInterrupt();

  // set PIT interrupt as lowest priority
  NVIC_SET_PRIORITY(IRQ_PIT, 255);

  // enable PIT interrupt in NVIC
  NVIC_ENABLE_IRQ(IRQ_PIT);
}

void OneShot::enableInterrupt() {
  // clear interrupt flag before enabling, just in case
  channel->TFLG = 1;

  // enable the timer channel and its associated interrupt
  channel->TCTRL = 3;
}

void OneShot::schedule_micros(uint32_t micros, voidFuncPtr callback) {
  _callback = callback;
  schedule_micros(micros);
}

void OneShot::schedule_micros(uint32_t micros) {
  // load countdown value
  uint32_t cycles = (F_BUS / 1000000) * micros - 1;
  channel->LDVAL = cycles;
  enableInterrupt();
}

/// Define the magic interrupt handler that's declared in kinetis.h and will be
/// run when any PIT channel triggers an interrupt
void pit_isr() {
  if (channel->TFLG) {
    // clear flag
    channel->TFLG = 1;
    // disable timer
    channel->TCTRL = 0;

    if (_callback != nullptr) {
      (*_callback)();
    }
  }
  // // should we clear all flags just in case someone else enabled the other
  // // channel?
  // PIT_TFLG0 = 1;
  // PIT_TFLG1 = 1;
}
