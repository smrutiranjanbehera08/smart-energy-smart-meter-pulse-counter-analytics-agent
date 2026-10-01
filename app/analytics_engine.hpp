#ifndef ANALYTICS_ENGINE_HPP
#define ANALYTICS_ENGINE_HPP

#include <cstdint>

class AnalyticsEngine {
public:
    static double calculateEnergyKwh(
        std::uint64_t pulse_count,
        double pulses_per_kwh) noexcept;

    static double calculateAveragePowerWatts(
        std::uint64_t previous_pulse_count,
        std::uint64_t current_pulse_count,
        double pulses_per_kwh,
        double elapsed_seconds) noexcept;

    static double calculateEstimatedCost(
        double energy_kwh,
        double tariff_per_kwh) noexcept;
};

#endif
