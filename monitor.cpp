#include "./monitor.h"
#include <stdio.h>
#include <unistd.h>

// ---- Types ----
typedef struct {
    const char *name;
    float min;
    float max;
    const char *alertMsg;
} VitalLimit;

// Callback type for alerts
typedef void (*AlertHandler)(const char *msg);

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
    {"SpO2",        90.0f, 100.0f, "Oxygen Saturation out of range!"},
    {"Pulse Rate",  60.0f, 100.0f, "Pulse Rate is out of range!"}
};

// ---- Public API ----
int vitalsOk(float temperature, float spo2, float pulseRate,
             const VitalLimit *limits, int numVitals,
             AlertHandler handler) 
{
    float readings[] = {temperature, spo2, pulseRate}; // order matches vitalLimits[]

    // If no handler provided, fallback to default animation
    if (!handler) {
        handler = alertAnimation;
    }

    for (int i = 0; i < numVitals; i++) {
        if (!isValueInRange(readings[i], limits[i].min, limits[i].max)) {
            handler(limits[i].alertMsg);
            return 0;
        }
    }
    return 1;
}
