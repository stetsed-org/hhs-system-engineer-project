#include "../../../headers.hpp"
#include "gyro.h"


void Gyroscope::_retrieveData() {
	if (_interface.gyroDataReady())
	{
		_interface.readGyro();
		_vector.x = _interface.g.x;
		_vector.y = _interface.g.y;
		_vector.z = _interface.g.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
