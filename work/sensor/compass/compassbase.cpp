CompassBase::CompassBase(): _vector{0, 0, 0} {  }

void CompassBase::_retrieveData() {
	return;
}
Vector3 CompassBase::Values() {
	
	this->_retrieveData();

	return _vector;
}

void CompassBase::Initialize() {
	if (_interface.init())
	{
		Serial1.println("Compass interface initialized successfully!");
	} else {
		Serial1.println("Compass interface initialized successfully?");
	}
}
// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
