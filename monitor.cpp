#include "monitor.h"
#include <stdio.h>
#include <unistd.h>

typedef struct {
    const char* name;     // Vital sign name
    float min;            // Lower threshold
    float max;            // Upper threshold
    const char* alertMsg; // Message to display if out of range
} VitalLimit;

// ---- Internal reusable helpers ----
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

static int valueInRange(float value, float min, float max) {
    return (value >= min && value <= max);
}

// ---- Configuration Table ----
// To add a new vital sign, just add a new row here.
static const VitalLimit vitalLimits[] = {
    {"Temperature", 95.0f, 102.0f, "Temperature is critical!"},
    {"Pulse Rate",  60.0f, 100.0f, "Pulse Rate is out of range!"},
    {"SpO2",        90.0f, 200.0f, "Oxygen Saturation out of range!"}
};

// ---- Public API ----
int isVitalOk(float temperature, float pulseRate, float spo2) {
    float readings[] = {temperature, pulseRate, spo2};
    int numVitals = sizeof(vitalLimits) / sizeof(vitalLimits[0]);

    for (int i = 0; i < numVitals; i++) {
        if (!valueInRange(readings[i], vitalLimits[i].min, vitalLimits[i].max)) {
            alertAnimation(vitalLimits[i].alertMsg);
            return 0;
        }
    }
    return 1;
}
