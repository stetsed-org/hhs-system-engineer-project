#include "accel.h"

void Accelerometer::pvt_RetrieveData() {
	// if new data ready
	if (m_InterfacePTR->accDataReady()) 
	{
		// get new reading
		m_InterfacePTR->readAcc();

		// copy reading to m_Vector
		m_Vector.x = m_InterfacePTR->a.x;
		m_Vector.y = m_InterfacePTR->a.y;
		m_Vector.z = m_InterfacePTR->a.z;
	}
}

void Accelerometer::pvt_DebugRead() {
  Serial1.println("A\n" + m_Vector.x + '\n' + m_Vector.y + '\n' + m_Vector.z + '\n' + 'a');
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
