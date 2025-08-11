#include "monitor.h"
#include <stdio.h>
#include <unistd.h>

// Config table: just add more vitals here
const VitalLimit vitalLimits[] = {
    {"Temperature", 95.0f, 102.0f, "Temperature is critical!"},
    {"Pulse Rate",  60.0f, 100.0f, "Pulse Rate is out of range!"},
    {"SpO2",        90.0f, 200.0f, "Oxygen Saturation out of range!"}
};
const int numVitals = sizeof(vitalLimits) / sizeof(vitalLimits[0]);

// Pure function
static int valueInRange(float value, float min, float max) {
    return (value >= min && value <= max);
}

// I/O helpers
static void blinkPattern(void) {
    printf("\r* ");
    fflush(stdout);
    sleep(1);
    printf("\r *");
    fflush(stdout);
    sleep(1);
}

static void alertAnimation(const char* message) {
    printf("%s\n", message);
    fflush(stdout);
    for (int i = 0; i < 6; i++) {
        blinkPattern();
    }
    printf("\n");
}

// Public API
int isVitalOk(const float* readings) {
    for (int i = 0; i < numVitals; i++) {
        if (!valueInRange(readings[i], vitalLimits[i].min, vitalLimits[i].max)) {
            alertAnimation(vitalLimits[i].alertMsg);
            return 0;
        }
    }
    return 1;
}
