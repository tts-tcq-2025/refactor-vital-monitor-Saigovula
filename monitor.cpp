#include "./monitor.h"
#include <stdio.h>
#include <unistd.h>

typedef struct {
    const char *name;
    float min;
    float max;
    const char *alertMsg;
} VitalLimit;

// ---- Internal reusable helpers ----
static int isValueInRange(float value, float min, float max) {
    return (value >= min && value <= max);
}

static void blinkPattern(void) {
    printf("\r* ");
    fflush(stdout);
    sleep(1);
    printf("\r *");
    fflush(stdout);
    sleep(1);
}

static void alertAnimation(const char *message) {
    printf("%s\n", message);
    fflush(stdout);
    for (int i = 0; i < 6; i++) {
        blinkPattern();
    }
    printf("\n");
}

// ---- Configuration Table ----
static const VitalLimit vitalLimits[] = {
    {"Temperature", 95.0f, 102.0f, "Temperature is critical!"},
    {"SpO2",        90.0f, 200.0f, "Oxygen Saturation out of range!"}
    {"Pulse Rate",  60.0f, 100.0f, "Pulse Rate is out of range!"},
  
};

// ---- Public API ----
int vitalsOk(float temperature, float pulseRate, float spo2) {
    float readings[] = {temperature, pulseRate, spo2};
    int numVitals = sizeof(vitalLimits) / sizeof(vitalLimits[0]);

    for (int i = 0; i < numVitals; i++) {
        if (!isValueInRange(readings[i], vitalLimits[i].min, vitalLimits[i].max)) {
            alertAnimation(vitalLimits[i].alertMsg);
            return 0;
        }
    }
    return 1;
}
