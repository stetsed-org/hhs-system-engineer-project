# Arduino Library base folder and example structure
EXAMPLE ?= main.cpp

# Arduino CLI executable name and directory location
ARDUINO_CLI = arduino-cli
ARDUINO_CLI_DIR = .

# Arduino CLI Board type
BOARD_TYPE ?= pololu-a-star:avr

compile:
	/usr/bin/arduino-cli compile -v --profile zumo-linux --build-path="./build/" $(PWD)

compile-windows:
	C:\Program Files\arduino-cli.exe compile -v --profile zumo-windows --build-path="./build/" $(PWD)
