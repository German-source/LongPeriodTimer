#pragma once

#include <Arduino.h>
#include "TimeClock.h"

class LongPeriodTimer {
    public:

    void restart(void) { 
        _tmr = TimeClock.seconds();
    }

    void attach(void (*cb)()) {
        _cb = cb;
    }

    void detach(void) {
        _cb = nullptr;
    }

    void setPeriod(uint32_t period) {
        _prd = period;
    }

    bool tick(void) {
        TimeClock.tick();
        if (TimeClock.seconds() - _tmr >= _prd) {
            _tmr = TimeClock.seconds();
            return true;
        }
        return false;
    }

    operator bool() {
        return tick();
    }

    private:

    bool _start = false;
    uint32_t _tmr = 0;
    uint32_t _prd = 10;
    uint32_t _sec = 0;
    void (*_cb)() { nullptr };
};