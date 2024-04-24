# StepTrackingPCB

--------------- Environments -----------------

There are multiple "Environments" in this project

You can change the environment in the bar at the bottom (by default it should say env:default)
Each Environment has its own main file.

Currrently the environments are:

[env:release]
runs main.cpp
This is the release code that we upload to the pcb for the demonstration.

[env:pcbTest]
runs pcbTest.cpp
This is a test that can be run to make sure the arduino has successfully connected to each component.
Will blink LEDs, respond to button presses, read from the Sensor and print to lcd.

You can add more if you want.

--------------- Headers -----------------

This project also contains multiple header files (eg. lcd.h)
These exist so that code can be shared between different main files, eg. so we dont have to write different lcd setups and pin definitions for each main file.


--------------- Platformio -------------------

Platformio is a embedded software compiler/environment thing that can be configured to program any board.
This project was made using vsCode using platformio, this project will not run correctly on the ArduinoIDE without some changes.

platformio.ini is a file used to provide the compiler with the configuration and environments for building the code.
If you don't know what you are doing don't touch it.

