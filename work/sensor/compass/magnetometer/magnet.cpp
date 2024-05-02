void Magnetometer::_retrieveData() {
	if (_interfacePTR->magDataReady())
	{
		_interfacePTR->readMag();
		_vector.x = _interfacePTR->m.x;
		_vector.y = _interfacePTR->m.y;
		_vector.z = _interfacePTR->m.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
