void Gyroscope::pvt_RetrieveData() {
	if (m_InterfacePTR->gyroDataReady())
	{
		m_InterfacePTR->readGyro();
		m_Vector.x = m_InterfacePTR->g.x;
		m_Vector.y = m_InterfacePTR->g.y;
		m_Vector.z = m_InterfacePTR->g.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
