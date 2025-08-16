class ___TimeClock___ {
    public:
    void begin() {
        _sec = 0;
        _tmr = millis();
    }
    void restart() {
        begin();
    }
    uint32_t seconds() {
        return _sec;
    }
    bool tick() {
        if (millis() - _tmr >= 1000) {
            _tmr = millis();
            _sec ++;
            return true;
        }
        return false;
    }
    
    operator bool() {
        return tick();
    }

    private:
    uint32_t _tmr = 0;
    uint32_t _sec = 0;
};

___TimeClock___ TimeClock;