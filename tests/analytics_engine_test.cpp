#include "analytics_engine.hpp"

#include <cmath>
#include <iostream>

namespace {
int failures = 0;

void expectNear(const char* test_name, double actual, double expected)
{
    constexpr double tolerance = 1e-9;

    if (std::fabs(actual - expected) > tolerance) {
        std::cerr << "FAIL: " << test_name
                  << " (expected " << expected
                  << ", got " << actual << ")\n";
        ++failures;
    } else {
        std::cout << "PASS: " << test_name << '\n';
    }
}
} // namespace

int main()
{
    expectNear(
        "100 pulses at 1000 pulses/kWh = 0.1 kWh",
        AnalyticsEngine::calculateEnergyKwh(100, 1000.0),
        0.1);

    expectNear(
        "zero pulses = 0 kWh",
        AnalyticsEngine::calculateEnergyKwh(0, 1000.0),
        0.0);

    expectNear(
        "zero meter constant returns 0 kWh",
        AnalyticsEngine::calculateEnergyKwh(100, 0.0),
        0.0);

    expectNear(
        "10 pulses over one hour = 10 W",
        AnalyticsEngine::calculateAveragePowerWatts(
            100, 110, 1000.0, 3600.0),
        10.0);

    expectNear(
        "zero elapsed time returns 0 W",
        AnalyticsEngine::calculateAveragePowerWatts(
            100, 110, 1000.0, 0.0),
        0.0);

    expectNear(
        "decreasing pulse count returns 0 W",
        AnalyticsEngine::calculateAveragePowerWatts(
            110, 100, 1000.0, 3600.0),
        0.0);

    expectNear(
        "0.1 kWh at INR 8/kWh = INR 0.8",
        AnalyticsEngine::calculateEstimatedCost(0.1, 8.0),
        0.8);

    expectNear(
        "negative energy returns INR 0",
        AnalyticsEngine::calculateEstimatedCost(-0.1, 8.0),
        0.0);

    if (failures != 0) {
        std::cerr << failures << " unit test(s) failed.\n";
        return 1;
    }

    std::cout << "All analytics unit tests passed.\n";
    return 0;
}
