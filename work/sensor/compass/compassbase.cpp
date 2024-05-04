CompassBase::CompassBase(Zumo32U4IMU* ifacePTR): m_Vector{0, 0, 0}, m_InterfacePTR(ifacePTR) {  }

Vector3 CompassBase::Values() {
	
	this->pvt_RetrieveData();

	return m_Vector;
}

void CompassBase::Initialize() {
	if (m_InterfacePTR->init())
	{
		Serial1.println("Compass interface initialized successfully!");
	} else {
		Serial1.println("Compass interface initialized successfully?");
	}
}

void CompassBase::PrintDebugInfo() {
	Serial1.println((uint8_t)m_InterfacePTR->getType());
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
