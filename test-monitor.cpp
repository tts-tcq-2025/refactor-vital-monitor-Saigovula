#include <gtest/gtest.h>
extern "C" {
    #include "monitor.h"
}

TEST(Monitor, AllVitalsInRange) {
    EXPECT_TRUE(vitalsOk(98.6f, 70.0f, 98.0f));
}

TEST(Monitor, TemperatureOutOfRange) {
    EXPECT_FALSE(vitalsOk(103.0f, 70.0f, 98.0f));
    EXPECT_FALSE(vitalsOk(94.0f, 70.0f, 98.0f));
}

TEST(Monitor, PulseRateOutOfRange) {
    EXPECT_FALSE(vitalsOk(98.6f, 50.0f, 98.0f));
    EXPECT_FALSE(vitalsOk(98.6f, 120.0f, 98.0f));
}

TEST(Monitor, SpO2OutOfRange) {
    EXPECT_FALSE(vitalsOk(98.6f, 70.0f, 85.0f));
}
