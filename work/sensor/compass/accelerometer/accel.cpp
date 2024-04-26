#include "../../../headers.hpp"
#include "accel.h"


void Accelerometer::_retrieveData() {
	if (_interface.accDataReady()) 
	{
		_interface.readAcc();
		_vector.x = _interface.a.x;
		_vector.y = _interface.a.y;
		_vector.z = _interface.a.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
