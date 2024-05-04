void Gyroscope::pvt_RetrieveData() {
	// if new data ready
	if (m_InterfacePTR->gyroDataReady())
	{
		// get new reading
		m_InterfacePTR->readGyro();

		// copy reading to m_Vector
		m_Vector.x = m_InterfacePTR->g.x;
		m_Vector.y = m_InterfacePTR->g.y;
		m_Vector.z = m_InterfacePTR->g.z;
	}
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
