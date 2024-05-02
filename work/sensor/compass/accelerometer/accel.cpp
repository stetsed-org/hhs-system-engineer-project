void Accelerometer::_retrieveData() {
	if (_interfacePTR->accDataReady()) 
	{
		_interfacePTR->readAcc();
		_vector.x = _interfacePTR->a.x;
		_vector.y = _interfacePTR->a.y;
		_vector.z = _interfacePTR->a.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
