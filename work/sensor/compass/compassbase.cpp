ICompassBase::ICompassBase(Zumo32U4IMU* zumoInterfacePTR): m_Vector{0, 0, 0}, m_InterfacePTR(zumoInterfacePTR) {  }

Vector3 ICompassBase::Values() {
	
	// call pvt_RetrieveData to place sensor reading in m_Vector
	this->pvt_RetrieveData();

	return m_Vector;
}

void ICompassBase::PrintDebugInfo() {
	Serial1.println((uint8_t)m_InterfacePTR->getType());
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
