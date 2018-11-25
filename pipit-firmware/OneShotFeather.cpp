#include "OneShot.h"

// The arduino IDE tries to compile all files, even if they're not included.
#if defined(FEATHER_M0_BLE)

OneShot* OneShot::getInstance() {
  static FeatherOneShot singleton = FeatherOneShot();
  return &singleton;
}

/// The user-provided interrupt service routine.
static voidFuncPtr _callback = nullptr;

FeatherOneShot::FeatherOneShot() { init(); }

void FeatherOneShot::init() {
  initClocks();

  // Pick prescaler and set 32-bit mode.
  sync();
  _timer->CTRLA.reg = _prescaler | TC_CTRLA_MODE_COUNT32;

  // Set direction to count down, enable one-shot mode.
  sync();
  _timer->CTRLBSET.reg = TC_CTRLBSET_DIR | TC_CTRLBSET_ONESHOT;

  // Enable "start" event, so the counter won't immediately start when
  // enabled, and will instead wait for a retrigger.
  sync();
  _timer->EVCTRL.reg = TC_EVCTRL_EVACT_START;

  enableInterrupt();

  // Enable TC module
  sync();
  _timer->CTRLA.reg |= TC_CTRLA_ENABLE;
}

void FeatherOneShot::enableInterrupt() {
  // Enable interrupt on underflow/overflow
  IRQn_Type irq = TC4_IRQn;
  NVIC_ClearPendingIRQ(irq);
  NVIC_EnableIRQ(irq);
  _timer->INTENSET.reg = TC_INTENSET_OVF;
}

void FeatherOneShot::initClocks() {
  // Enable the user interface clock in the power manager
  PM->APBCMASK.reg |= PM_APBCMASK_TC4;

  // Enable the user interface clock for the the slave counter (since mode is
  // 32-bit)
  PM->APBCMASK.reg |= PM_APBCMASK_TC5;

  // Setup clock for module
  GCLK->CLKCTRL.reg = (uint16_t)(GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 |
                                 GCLK_CLKCTRL_ID(GCM_TC4_TC5));

  while (GCLK->STATUS.bit.SYNCBUSY == 1)
    ;
}

void FeatherOneShot::schedule(uint32_t count, voidFuncPtr callback) {
  _callback = callback;
  schedule(count);
}

void FeatherOneShot::schedule(uint32_t count) {
  // Send "retrigger" command.
  // Only call this after the counter has stopped (eg. inside an ISR).
  // From datasheet:
  // "When a retrigger is evoked while the counter is running, the counter will
  // wrap to the top value or zero, depending on the counter direction. When a
  // retrigger is evoked with the counter stopped, the counter will continue
  // counting from the value in the COUNT register."
  setCount(count);
  sync();
  _timer->CTRLBSET.reg = TC_CTRLBCLR_CMD_RETRIGGER;
}

void FeatherOneShot::setCount(uint32_t count) {
  sync();
  _timer->COUNT.reg = count;
}

void inline FeatherOneShot::sync() {
  while (_timer->STATUS.reg & TC_STATUS_SYNCBUSY)
    ;
}

/// Define the magic interrupt handler that's declared in tc.h and will be run
/// when any TC4 interrupt occurs.
void TC4_Handler() {
  if (_callback != nullptr) {
    (*_callback)();
  }

  // Clear all interrupt flags
  TC4->COUNT32.INTFLAG.reg = TC_INTFLAG_MASK;
}

#endif
