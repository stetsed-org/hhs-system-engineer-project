CompassBase::CompassBase(Zumo32U4IMU* zumoInterfacePTR): m_Vector{0, 0, 0}, m_InterfacePTR(zumoInterfacePTR) {  }

<<<<<<< Updated upstream
Vector3 CompassBase::Values() {
=======
Vector3 ICompassBase::read() {
>>>>>>> Stashed changes
	
	// call pvt_RetrieveData to place sensor reading in m_Vector
	this->pvt_RetrieveData();

  if (debug) {
    this->pvt_DebugRead();
  }

	return m_Vector;
}

<<<<<<< Updated upstream
void CompassBase::PrintDebugInfo() {
	Serial1.println((uint8_t)m_InterfacePTR->getType());
}

=======
>>>>>>> Stashed changes
// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
