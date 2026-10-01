#include "analytics_engine.hpp"
#include "smart_meter_device.hpp"

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
    SmartMeterDevice device;

    if (!device.openDevice()) {
        std::cerr << "Make sure the smart-meter driver is loaded and run "
                     "this application with sudo.\n";
        return 1;
    }

    constexpr double pulses_per_kwh = 1000.0;
    constexpr double sample_tariff_per_kwh = 8.0;

    bool has_previous_reading = false;
    std::uint64_t previous_pulse_count = 0;
    std::chrono::steady_clock::time_point previous_reading_time;

    while (true) {
        std::cout << "\n=== Smart Meter Analytics Agent ===\n"
                  << "1. Simulate pulses\n"
                  << "2. Show meter analytics\n"
                  << "3. Reset pulse count\n"
                  << "4. Exit\n"
                  << "Choose an option: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            if (std::cin.eof())
                break;

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a number from 1 to 4.\n";
            continue;
        }

        if (choice == 1) {
            std::uint64_t requested_pulses = 0;
            std::cout << "Enter the number of pulses to simulate: ";

            if (!(std::cin >> requested_pulses)) {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter a whole number.\n";
                continue;
            }

            if (requested_pulses == 0 ||
                requested_pulses >
                    std::numeric_limits<std::uint32_t>::max()) {
                std::cout << "Enter a value from 1 to "
                          << std::numeric_limits<std::uint32_t>::max()
                          << ".\n";
                continue;
            }

            if (device.injectPulses(
                    static_cast<std::uint32_t>(requested_pulses))) {
                std::cout << "Simulated "
                          << requested_pulses << " pulse(s).\n";
            }
        } else if (choice == 2) {
            std::uint64_t pulse_count = 0;
            if (!device.getPulseCount(pulse_count))
                continue;

            const auto now = std::chrono::steady_clock::now();
            const double energy_kwh =
                AnalyticsEngine::calculateEnergyKwh(
                    pulse_count, pulses_per_kwh);
            const double estimated_cost =
                AnalyticsEngine::calculateEstimatedCost(
                    energy_kwh, sample_tariff_per_kwh);

            std::cout << std::fixed << std::setprecision(3)
                      << "\nPulse count: " << pulse_count << '\n'
                      << "Estimated energy: " << energy_kwh << " kWh\n"
                      << "Sample tariff: INR "
                      << sample_tariff_per_kwh << " per kWh\n"
                      << "Estimated cost: INR "
                      << estimated_cost << '\n';

            if (has_previous_reading) {
                const double elapsed_seconds =
                    std::chrono::duration<double>(
                        now - previous_reading_time).count();

                const double average_power_watts =
                    AnalyticsEngine::calculateAveragePowerWatts(
                        previous_pulse_count,
                        pulse_count,
                        pulses_per_kwh,
                        elapsed_seconds);

                std::cout << "Estimated average power since the last "
                             "reading: "
                          << average_power_watts << " W\n";
            } else {
                std::cout << "Take another reading to estimate average "
                             "power.\n";
            }

            previous_pulse_count = pulse_count;
            previous_reading_time = now;
            has_previous_reading = true;
        } else if (choice == 3) {
            if (device.resetCount()) {
                std::cout << "Pulse count reset to zero.\n";
                has_previous_reading = false;
            }
        } else if (choice == 4) {
            std::cout << "Exiting the analytics agent.\n";
            break;
        } else {
            std::cout << "Choose an option from 1 to 4.\n";
        }
    }

    return 0;
}
