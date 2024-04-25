#pragma once

typedef uint32_t pin_t;

/* Operation of GPIO by pin. */

#define setPinInput(pin) palSetLineMode((pin), PAL_MODE_INPUT)
#define setPinInputHigh(pin) palSetLineMode((pin), PAL_MODE_INPUT_PULLUP)
#define setPinInputLow(pin) palSetLineMode((pin), PAL_MODE_INPUT_PULLDOWN)
#define setPinOutputPushPull(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_PUSHPULL)
#define setPinOutputOpenDrain(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_OPENDRAIN)
#define setPinOutput(pin) setPinOutputPushPull(pin)

#define writePinHigh(pin) palSetLine(pin)
#define writePinLow(pin) palClearLine(pin)
#define writePin(pin, level)   \
    do {                       \
        if (level) {           \
            writePinHigh(pin); \
        } else {               \
            writePinLow(pin);  \
        }                      \
    } while (0)

#define readPin(pin) palReadLine(pin)

#define togglePin(pin) palToggleLine(pin)
