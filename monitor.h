#ifndef MONITOR_H
#define MONITOR_H

typedef struct {
    const char* name;
    float min;
    float max;
    const char* alertMsg;
} VitalLimit;

extern const VitalLimit vitalLimits[];
extern const int numVitals;

int isVitalOk(const float* readings);

#endif
