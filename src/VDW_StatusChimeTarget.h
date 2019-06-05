#ifndef STATUS_CHIME_TARGET_H
#define STATUS_CHIME_TARGET_H

#include "Particle.h"

class VDW_ChimeStatus;
typedef VDW_ChimeStatus* ChimeStatusPtr;

inline void analogWriteParamConverter(uint8_t pin , uint8_t pwm){
    analogWrite(pin, pwm);
}

class VDW_StatusChimeTarget{
        public:
        // Native Pin constructor
        VDW_StatusChimeTarget(uint8_t chimePin, bool activeLow = false)
            :   _analogWritePin(analogWriteParamConverter)
            ,   _chimePin(chimePin)
            ,   _activeLow(activeLow)
            ,   _externalIO(false)
            {}

        // External IO pin constructor
        VDW_StatusChimeTarget(void (*writePin)(uint8_t, uint8_t), uint8_t chimePin, bool activeLow = false)
            :   _analogWritePin(writePin)
            ,   _chimePin(chimePin)
            ,   _activeLow(activeLow)
            ,   _externalIO(true)
            {}

        // make sure all pins are off, pin modes should be setup prior to calling init
        void init();
        
        ChimeStatusPtr addStatus(ChimeStatusPtr status);
        ChimeStatusPtr pushBack(ChimeStatusPtr status);
        ChimeStatusPtr removeStatus(ChimeStatusPtr status);

        // display highest priority active status, run blink patterns and count number of blinks, reset active status if number of blinks exceeds set number
        void update();

        // Set Volume
        // Sets the global volume for the target Chime (all status' will use this volume)
        // \volume [u32] - the volume (0-255) of the chime
        void setVolume(uint32_t volume);

    private:  
        // Constructor Settings
        void (*_analogWritePin)(uint8_t, uint8_t);
        uint8_t _chimePin;
        bool _activeLow;
        bool _externalIO;
        uint32_t _volume = 255;
        
        // Status List
        ChimeStatusPtr _headStatusList = NULL;
        ChimeStatusPtr _lastActiveStatus = NULL;        

        // Blink Control
        bool _pulseState = true; // true if LED is on during blink
        bool _previousBlinkState = false; // blink state for previous update() call, used to determine, rising edges for incrementing blink counts
        uint32_t _pulseOnTime = 0; // The time the current pulse came on
        uint32_t _pulsePeriodTime = 0; // The time the last pulse period began
        uint32_t _lastBlinkTransition = 0; // time in milliseconds of the last blink state change

        void printStatuses();
};

#endif