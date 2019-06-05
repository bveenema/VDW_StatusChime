#ifndef CHIME_STATUS_H
#define CHIME_STATUS_H

#include "Particle.h"

enum StatusChime_Priority {
    StatusChime_Priority_Low = 1,
    StatusChime_Priority_Med = 4, 
    StatusChime_Priority_High = 7,
    StatusChime_Priority_Critical = 10, 
};

enum StatusChime_Pattern {
    StatusChime_Pattern_Solid,
    StatusChime_Pattern_Pulse,
};

enum StatusChime_Speed {
    StatusChime_Speed_Fast = 100,
    StatusChime_Speed_Medium = 350,
    StatusChime_Speed_Slow = 750,
};

#ifndef DISABLED_ACTIVE_ENUM
#define DISABLED_ACTIVE_ENUM
enum {
    Disabled,
    Active,
};
#endif

// forward declare the target LED for reference
class VDW_StatusChimeTarget;

class VDW_ChimeStatus{
    friend class VDW_StatusChimeTarget;
    public:

        // Creates a new status with pulseRate, number of pulses before being set inactive, and priority
        VDW_ChimeStatus(VDW_StatusChimeTarget *TargetChime, StatusChime_Priority priority, StatusChime_Pattern pattern, StatusChime_Speed speed = StatusChime_Speed_Medium, uint32_t numBlinks = 0);
        VDW_ChimeStatus(VDW_StatusChimeTarget *TargetChime, StatusChime_Priority priority, StatusChime_Pattern pattern, uint32_t pulseRate, uint32_t pulseLength, uint32_t numBlinks = 0);

        void construct(VDW_StatusChimeTarget *TargetChime, StatusChime_Priority priority, StatusChime_Pattern pattern, uint32_t pulseRate, uint32_t pulseLength, uint32_t numBlinks);

        // turns the status on or off
        void setStatus(bool isActive){
            _active = isActive;
            _blinksCompleted = 0;
        }

        // changes the priority level (higher is more important) of the status
        void setPriority(uint32_t priority){
            _priority = priority;
        }

        // makes the status the highest priority in the list and sets it active, then calls update to display the status immediately
        //  WARNING: should not be used except for absolutely critical statuses that will be active for short durations or just before a crash, reset or power-down would occur
        bool displayNow();

        void printStatus(){
            Serial.printlnf("Status %d", this);
            Serial.printlnf("\tActive: %d", _active);
            Serial.printlnf("\tBlink Rate: %d", _pulseRate);
            Serial.printlnf("\tNum Blinks: %d", _numBlinks);
            Serial.printlnf("\tBlinks Completed: %d", _blinksCompleted);
            Serial.printlnf("\tPriority: %d", _priority);
            Serial.printlnf("\tNext Status: %d", _nextStatus);
        }

    private:

        VDW_StatusChimeTarget *_TargetChime; // The target LED this status belongs to
        uint32_t _priority; // active ledStatus with highest priority will be the one displayed, if multiple are same priority, lowest index will be displayed
        uint32_t _pattern;
        uint32_t _pulseRate; // time between pulses
        uint32_t _pulseLength; // duration of pulse
        uint32_t _numBlinks; // number of blinks before active is set to false, 0 is infinite
        
        uint32_t _blinksCompleted; // the number of times the status has blinked since setStatus() was called
        bool _active = false; // active status means the color and blink rate will be displayed if it's highest priority

        typedef VDW_ChimeStatus* ChimeStatusPtr;
        ChimeStatusPtr _nextStatus;
};

#endif