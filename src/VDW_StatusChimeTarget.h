#ifndef STATUS_LED_TARGET_H
#define STATUS_LED_TARGET_H

#include "Particle.h"

class VDW_ChimeStatus;
typedef VDW_ChimeStatus* StatusPtr;

inline void digitalWriteParamConverter(uint8_t pin , bool dir){
    digitalWrite(pin, dir);
}

class VDW_StatusChimeTarget{
        public:
        // Native Pin constructor
        VDW_StatusChimeTarget(uint8_t chimePin, bool activeLow = false)
            :   _writePin(digitalWriteParamConverter)
            ,   _chimePin(chimePin)
            ,   _activeLow(activeLow)
            ,   _externalIO(false)
            {}

        // External IO pin constructor
        VDW_StatusChimeTarget(void (*writePin)(uint8_t, bool), uint8_t chimePin, bool activeLow = false)
            :   _writePin(writePin)
            ,   _chimePin(chimePin)
            ,   _activeLow(activeLow)
            ,   _externalIO(true)
            {}

        // make sure all pins are off, pin modes should be setup prior to calling init
        void init();
        
        StatusPtr addStatus(StatusPtr status);
        StatusPtr pushBack(StatusPtr status);
        StatusPtr removeStatus(StatusPtr status);

        // display highest priority active status, run blink patterns and count number of blinks, reset active status if number of blinks exceeds set number
        void update();

        // Set Volume
        // Sets the global volume for the target Chime (all status' will use this volume)
        // \volume [u32] - the volume (0-255) of the chime
        void setVolume(uint32_t volume);

    private:  
        // Constructor Settings
        void (*_writePin)(uint8_t, bool);
        uint8_t _chimePin;
        bool _activeLow;
        bool _externalIO;
        uint32_t _volume = 255;
        
        // Status List
        StatusPtr _headStatusList = NULL;
        StatusPtr _lastActiveStatus = NULL;        

        // Blink Control
        bool _blinkState = true; // true if LED is on during blink
        bool _previousBlinkState = false; // blink state for previous update() call, used to determine, rising edges for incrementing blink counts
        uint32_t _lastBlinkTransition = 0; // time in milliseconds of the last blink state change

        void printStatuses();
};

#endif