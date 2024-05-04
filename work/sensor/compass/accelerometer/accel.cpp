void Accelerometer::pvt_RetrieveData() {
	if (m_InterfacePTR->accDataReady()) 
	{
		m_InterfacePTR->readAcc();
		m_Vector.x = m_InterfacePTR->a.x;
		m_Vector.y = m_InterfacePTR->a.y;
		m_Vector.z = m_InterfacePTR->a.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
