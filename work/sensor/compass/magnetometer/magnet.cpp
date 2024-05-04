void Magnetometer::pvt_RetrieveData() {
	if (m_InterfacePTR->magDataReady())
	{
		m_InterfacePTR->readMag();
		m_Vector.x = m_InterfacePTR->m.x;
		m_Vector.y = m_InterfacePTR->m.y;
		m_Vector.z = m_InterfacePTR->m.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
