void Magnetometer::_retrieveData() {
	if (_interface.magDataReady())
	{
		_interface.readMag();
		_vector.x = _interface.m.x;
		_vector.y = _interface.m.y;
		_vector.z = _interface.m.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
