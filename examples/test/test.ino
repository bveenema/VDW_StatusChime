/*
 * Project M6-Firmware
 * Description: Firmware for MAXX06-ECM Rev M6
 * Author: Ben Veenema - Veenema Design Works
 */
#include "VDW_StatusChime.h"
#include "pins.h"

VDW_StatusChimeTarget Chime(CHIME_VOLUME_PIN);
VDW_ChimeStatus ChimePulseSlow(&Chime, StatusChime_Pattern_Pulse, StatusChime_Speed_Slow);
VDW_ChimeStatus ChimePulseMed(&Chime, StatusChime_Pattern_Pulse, StatusChime_Speed_Medium);
VDW_ChimeStatus ChimePulseFast(&Chime, StatusChime_Pattern_Pulse, StatusChime_Speed_Fast);
VDW_ChimeStatus ChimeContinous(&Chime, StatusChime_Pattern_Solid);

void setup() {
  // Initialize Serial
  Serial.begin(230400);

  // Initialize the Chime Pin
  Chime.init();

}

void loop() {
  static uint32_t lastUpdate = 0;
  if(millis() - lastUpdate > 5000){
    lastUpdate = millis();
    static uint32_t status = 0;
    ChimePulseSlow.setStatus(Disabled);
    ChimePulseMed.setStatus(Disabled);
    ChimePulseFast.setStatus(Disabled);
    ChimeContinous.setStatus(Disabled);
    Serial.printlnf("Status: %d", status);
    switch(status){
      case 0:
        ChimePulseSlow.setStatus(Active);
        status = 1;
        break;
      case 1:
        ChimePulseMed.setStatus(Active);
        status = 2;
        break;
      case 2:
        ChimePulseFast.setStatus(Active);
        status = 3;
        break;
      case 3:
        ChimeContinous.setStatus(Active);
        status = 3;
        break;
      default:
        break;
    }
  }
 
  static uint32_t lastVolumeUpdate = 0;
  if(millis() - lastVolumeUpdate > 1000){
    lastVolumeUpdate = millis();
    static uint32_t volume = 50;
    if(volume > 255) volume = 0;
    Serial.printlnf("Volume: %d", volume);
    Chime.setVolume(volume);
    volume += 50;
  }
  
  Chime.update();
}