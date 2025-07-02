#ifndef Controller_h
#define Controller_h

#include <Bluepad32.h>
#include "Setup.h"
#include "motor.h"
#include "Solar.h"



// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                           properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            ctl->setColorLED(255, 0, 255);
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, brake: %4d, throttle: %4d, \n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle()   // (0 - 1023): throttle (AKA gas) button
    );
}

void processGamepad(ControllerPtr ctl) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...
    SpeedF      = ctl->throttle();
    SpeedR      = ctl->brake();
    Steer       = ctl->axisX();
    armElbow    = ctl->axisRX();       // (-511 - 512) right X axis
    armShoulder = ctl->axisRY();

    //funcitie met timer die de linetracker aan en uit zet
    if (timer3 + 400< millis()){
      if((ctl->dpad() & 0x01) && useLineTracker == false ){
        useLineTracker = true;
        Serial.println("gebruik linetracker");
      }
      else if ((ctl->dpad() & 0x01) && useLineTracker == true) {
        useLineTracker = false;
        Serial.println("gebruik linetracker gestopt");
        
      }
      if((ctl->dpad() & 0x04)){
        stappenmotor();
        Serial.println("Stappenmotor");

      }
      if(ctl->a() & handmatigArm == false){
        handmatigArm = true;
      }
      else if (ctl->a() & handmatigArm == true){
        handmatigArm = false;
      }
      if((ctl->dpad() & 0x08)){
        stappenmotorReverse();
      }
      if((ctl->dpad() & 0x02)&& useSolarTracker == false){
        useSolarTracker = true;
        Serial.println("Solar tracker aan");
      }
      else if((ctl->dpad() & 0x02)&& useSolarTracker == true){
        useSolarTracker = false;
        Serial.println("Solar tracker uit");

        }
        if((ctl->buttons() & 0x0100) && magnetOn == false){
            magnetOn = true;
            digitalWrite(magneetTransistor, HIGH);
            Serial.println("Magneet aan");
        }
        else if((ctl->buttons() & 0x0100) && magnetOn == true){
            magnetOn = false;
            digitalWrite(magneetTransistor, LOW);
            Serial.println("Magneet uit");
        }
        if((ctl->buttons() & 0x0200) && detectorOn == false){
            detectorOn = true;
           // digitalWrite(detectorTransistor, HIGH);
            Serial.println("detector aan");
        }
        else if((ctl->buttons() & 0x0200) && detectorOn == true){
            detectorOn = false;
           // digitalWrite(detectorTransistor, LOW);
            Serial.println("Detector uit");
        }
      timer3 = millis();
    }

}

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            } else {
                Serial.println("Unsupported controller");
            }
        }
    }
}

void ControllerSetup(){
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    // "forgetBluetoothKeys()" should be called when the user performs
    // a "device factory reset", or similar.
    // Calling "forgetBluetoothKeys" in setup() just as an example.
    // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
    // But it might also fix some connection / re-connection issues.

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}

void controllerUpdate(){
      // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();
        

    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

}

#endif