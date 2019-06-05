#include "VDW_ChimeStatus.h"
#include "VDW_StatusChimeTarget.h"


VDW_ChimeStatus::VDW_ChimeStatus(VDW_StatusChimeTarget *TargetChime, StatusChime_Priority priority, StatusChime_Pattern pattern, StatusChime_Speed speed, uint32_t numBlinks){
    construct(TargetChime, priority, pattern, speed, speed/2, numBlinks);
}
VDW_ChimeStatus::VDW_ChimeStatus(VDW_StatusChimeTarget *TargetChime, StatusChime_Priority priority, StatusChime_Pattern pattern, uint32_t pulseRate, uint32_t pulseLength, uint32_t numBlinks){
    construct(TargetChime, priority, pattern, pulseRate, pulseLength, numBlinks);
}

void VDW_ChimeStatus::construct(VDW_StatusChimeTarget *TargetChime, StatusChime_Priority priority, StatusChime_Pattern pattern, uint32_t pulseRate, uint32_t pulseLength, uint32_t numBlinks){
    _TargetChime = TargetChime;
    _priority = priority;
    _pattern = pattern;
    if(_pattern != StatusChime_Pattern_Solid){
        _pulseRate = pulseRate;
        _pulseLength = pulseLength;
    }
    else _pulseRate = 0;
    _numBlinks = numBlinks;

    _nextStatus = _TargetChime->addStatus(this);
}

// makes the named status the highest priority in the list and sets it active, then calls update, returns 0 if name is not found in status list
//  WARNING: should not be used except for absolutely critical statuses that will be active for short durations or just before a crash, reset or power-down would occur
bool VDW_ChimeStatus::displayNow(){
    // remove the status from the current location in the list and insert it at the beginning of the list
    _nextStatus = _TargetChime->removeStatus(this);
    _nextStatus = _TargetChime->pushBack(this);

    // make the status active, and  
    setStatus(Active);
    _TargetChime->update();
    
    return true;
}