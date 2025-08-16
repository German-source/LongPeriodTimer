#pragma once

#include <Arduino.h>
#include "TimeClock.h"

#define TMR_RESTART 0
#define TMR_TIMER 1
#define TMR_LOOP 2

typedef char& mode_t;


class LongPeriodTimer {
    public:

    void restart(void) { 
        _tmr = TimeClock.seconds();
    }

    void attach(void (*cb)(mode_t)) {
        _cb = cb;
    }

    void detach(void) {
        _cb = nullptr;
    }

    void setPeriod(uint32_t period) {
        _prd = period;
    }

    void create() {
        void (*_cb)(mode_t) = nullptr;
        _start = true;
    }
    
    bool tick(void) {
        TimeClock.tick();
        if (_start && TimeClock.seconds() - _tmr >= _prd) {
            char md = 0;
            if (_cb) (*_cb)(md);
            if (md == 1) {
                detach();
                _start = false;
            } 
            if (md != 2) {
                restart();
            }
            return true;
        }
        return false;
    }

    operator bool() {
        return tick();
    }

    private:

    bool _start = true;
    uint32_t _tmr = 0;
    uint32_t _prd = 10;
    void (*_cb)(mode_t) { nullptr };
};