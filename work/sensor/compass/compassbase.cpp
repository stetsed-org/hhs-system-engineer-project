CompassBase::CompassBase(): _vector{0, 0, 0} {  }
CompassBase::CompassBase(Zumo32U4IMU* ifacePTR): _vector{0, 0, 0}, _interfacePTR(ifacePTR) {  }

Vector3 CompassBase::Values() {
	
	this->_retrieveData();

	return _vector;
}

void CompassBase::Initialize() {
	if (_interfacePTR->init())
	{
		Serial1.println("Compass interface initialized successfully!");
	} else {
		Serial1.println("Compass interface initialized successfully?");
	}
}

// void CompassBase::PrintDebugInfo() {
// 	Serial1.println(_interfacePTR->getType());
// }

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project