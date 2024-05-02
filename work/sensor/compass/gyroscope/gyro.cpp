void Gyroscope::_retrieveData() {
	if (_interfacePTR->gyroDataReady())
	{
		_interfacePTR->readGyro();
		_vector.x = _interfacePTR->g.x;
		_vector.y = _interfacePTR->g.y;
		_vector.z = _interfacePTR->g.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
