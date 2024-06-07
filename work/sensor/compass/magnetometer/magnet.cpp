#include "magnet.h"

void Magnetometer::pvt_RetrieveData() {
	// if new data ready
	if (m_InterfacePTR->magDataReady())
	{
		// get new reading
		m_InterfacePTR->readMag();

		// copy reading to m_Vector
		m_Vector.x = m_InterfacePTR->m.x;
		m_Vector.y = m_InterfacePTR->m.y;
		m_Vector.z = m_InterfacePTR->m.z;
	}
}

void Magnetometer::pvt_DebugRead() {
  Serial1.println("M\n" + m_Vector.x + '\n' + m_Vector.y + '\n' + m_Vector.z + '\n' + 'm');
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
