compile:
	/usr/bin/arduino-cli compile -v --profile zumo-linux --build-path="./build/" $(PWD)

compile-upload:
	/usr/bin/arduino-cli compile -v --clean --profile zumo-linux --build-path="./build/" $(PWD) --upload 

compile-windows:
	C:\Program Files\arduino-cli.exe compile -v --profile zumo-windows --build-path="./build/" $(PWD)
