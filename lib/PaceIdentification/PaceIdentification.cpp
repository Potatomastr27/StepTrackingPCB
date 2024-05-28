#include "paceIdentification.h"

void updatePace(int movementRate) {
    // Reset LEDs
    digitalWrite(STATIONARY_PIN, LOW);
    digitalWrite(WALKING_PIN, LOW);
    digitalWrite(RUNNING_PIN, LOW);

    // Update LEDs based on movement rate
    switch (movementRate) {
        case 0: // Stationary
            digitalWrite(STATIONARY_PIN, HIGH);
            break;
        case 1: // Walking
            digitalWrite(STATIONARY_PIN, HIGH);
            digitalWrite(WALKING_PIN, HIGH);
            break;
        case 2: // Running
            digitalWrite(STATIONARY_PIN, HIGH);
            digitalWrite(WALKING_PIN, HIGH);
            digitalWrite(RUNNING_PIN, HIGH);
            break;
        default: // Error or invalid movement rate
            /* shutdownError(static_cast<const char*>("Invalid movement rate")); */ //!!! You can't use this here as it's not defined
            break;
    }
}
