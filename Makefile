KERNEL_BUILD := /lib/modules/$(shell uname -r)/build
PROJECT_DIR := $(CURDIR)
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iapp -Iinclude

APP_SOURCES := app/main.cpp app/smart_meter_device.cpp app/analytics_engine.cpp
APP_TARGET := smart_meter_agent

.PHONY: all driver app clean

all: driver app

driver:
	$(MAKE) -C $(KERNEL_BUILD) M=$(PROJECT_DIR)/driver modules

app: $(APP_TARGET)

$(APP_TARGET): $(APP_SOURCES) include/smart_meter_ioctl.h
	$(CXX) $(CXXFLAGS) $(APP_SOURCES) -o $@

clean:
	$(MAKE) -C $(KERNEL_BUILD) M=$(PROJECT_DIR)/driver clean
		rm -f $(APP_TARGET) tests/analytics_engine_test

.PHONY: unit-test

unit-test: tests/analytics_engine_test
	./tests/analytics_engine_test

tests/analytics_engine_test: tests/analytics_engine_test.cpp app/analytics_engine.cpp app/analytics_engine.hpp
	$(CXX) $(CXXFLAGS) tests/analytics_engine_test.cpp app/analytics_engine.cpp -o $@
