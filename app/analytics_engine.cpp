#include "analytics_engine.hpp"

double AnalyticsEngine::calculateEnergyKwh(
    std::uint64_t pulse_count,
    double pulses_per_kwh) noexcept
{
    if (pulses_per_kwh <= 0.0)
        return 0.0;

    return static_cast<double>(pulse_count) / pulses_per_kwh;
}

double AnalyticsEngine::calculateAveragePowerWatts(
    std::uint64_t previous_pulse_count,
    std::uint64_t current_pulse_count,
    double pulses_per_kwh,
    double elapsed_seconds) noexcept
{
    if (pulses_per_kwh <= 0.0 || elapsed_seconds <= 0.0)
        return 0.0;

    if (current_pulse_count < previous_pulse_count)
        return 0.0;

    const std::uint64_t pulse_difference =
        current_pulse_count - previous_pulse_count;

    const double energy_difference_kwh =
        static_cast<double>(pulse_difference) / pulses_per_kwh;

    return energy_difference_kwh * 3600000.0 / elapsed_seconds;
}

double AnalyticsEngine::calculateEstimatedCost(
    double energy_kwh,
    double tariff_per_kwh) noexcept
{
    if (energy_kwh < 0.0 || tariff_per_kwh < 0.0)
        return 0.0;

    return energy_kwh * tariff_per_kwh;
}
