#include "VDW_StatusChimeTarget.h"
#include "VDW_ChimeStatus.h"

void VDW_StatusChimeTarget::init(){
    if(!_externalIO) pinMode(_chimePin, OUTPUT);
    if(_activeLow) _analogWritePin(_chimePin, 255);
    else _analogWritePin(_chimePin, 0);
}

ChimeStatusPtr VDW_StatusChimeTarget::addStatus(ChimeStatusPtr status){
    // Insert Elements sorted by priority, highest to lowest
    ChimeStatusPtr nStatus = _headStatusList; // head is NULL if no elements in list
    ChimeStatusPtr pStatus = NULL;
    while(nStatus){
        if(nStatus->_priority <= status->_priority) break; // find the element where the priority is less than or equal to the new element
        pStatus = nStatus; // record the status that will be just before the status
        nStatus = nStatus->_nextStatus; // get the next status to test against, if we get to the end of the list, _nextStatus will be NULL
    }

    // The previous element should now reference the incoming element
    if(pStatus){
        pStatus->_nextStatus = status;
    } else{ // if there was no previous element, this is the highest priority element and therefor the new head
        _headStatusList = status;
    }

    // the incoming element should reference the next element
    return nStatus; // will be NULL if first element or last element
}

ChimeStatusPtr VDW_StatusChimeTarget::pushBack(ChimeStatusPtr status){
    // insert the incoming element to the beginning of the list
    ChimeStatusPtr tempStatus = _headStatusList;
    _headStatusList = status;

    return tempStatus;
}

ChimeStatusPtr VDW_StatusChimeTarget::removeStatus(ChimeStatusPtr status){
    Serial.println("Before Removal");
    printStatuses();
    // find the elements just before and after the incoming element
    ChimeStatusPtr nStatus = _headStatusList;
    ChimeStatusPtr pStatus = NULL;
    while(nStatus){
        if(nStatus == status){
            nStatus = nStatus->_nextStatus;
            break;
        }
        pStatus = nStatus;
        nStatus = nStatus->_nextStatus;
    }

    // set the previous element to point to the element after the incoming element
    pStatus->_nextStatus = nStatus;
    Serial.println("After Removal");
    printStatuses();

    // return a NULL pointer
    return NULL;
}

// display highest priority active status, run blink patterns and count number of blinks, reset active status if number of blinks exceeds set number
void VDW_StatusChimeTarget::update(){

    ChimeStatusPtr aStatus = NULL; // the "active" status

    // find the highest priority, active status. list is sorted by priority ==> first active element is highest priority, active element
    ChimeStatusPtr cStatus = _headStatusList;
    while(cStatus != NULL){
        if(cStatus->_active){
            aStatus = cStatus;
            break;
        }
        cStatus = cStatus->_nextStatus;
    }

    // if all statuses inactive, turn LED off and exit update();
    if(aStatus == NULL){
        if(_activeLow) _analogWritePin(_chimePin, 255);
        else _analogWritePin(_chimePin, 0);
        return;
    }

    // if a new status is active, reset _pulseState
    if(aStatus != _lastActiveStatus) _pulseState = false;
    _lastActiveStatus = aStatus;

    // if solid color (pulseRate == 0) or blink state is ON turn the LED to the specific color
    if(aStatus->_pulseRate == 0 || _pulseState == true){
        uint8_t pwm = _volume;
        if(_activeLow) pwm = 255-_volume; // if active low, invert _volume

        _analogWritePin(_chimePin, pwm);
    } else {
        if(_activeLow) _analogWritePin(_chimePin, 255);
        else _analogWritePin(_chimePin, 0);
    }

    // exit update() if solid color
    if(aStatus->_pulseRate == 0) return;

    // determine if a pulse state change is due
    if(_pulseState && millis() - _pulseOnTime > aStatus->_pulseLength){ // if pulse should end
        _pulseState = false;
    }else if(!_pulseState && millis() - _pulsePeriodTime > aStatus->_pulseRate){ // if pulse should start
        _pulsePeriodTime = millis();
        _pulseOnTime = millis();
        _pulseState = true;
    }

    // exit update() if blink should go on forever
    if(aStatus->_numBlinks == 0) return;

    // increment blinksCompleted when blink cycle is completed, detected by falling edge of blink
    if((_pulseState != _previousBlinkState) && (_previousBlinkState == 1)) aStatus->_blinksCompleted += 1;
    _previousBlinkState = _pulseState;

    // if status has blinked numBlinks (and numBlinks was set), set the status inactive
    if(aStatus->_blinksCompleted >= aStatus->_numBlinks) aStatus->_active = false;

    return;
}

void VDW_StatusChimeTarget::setVolume(uint32_t volume){
    if(volume > 255) volume = 255;
    _volume = volume;
}