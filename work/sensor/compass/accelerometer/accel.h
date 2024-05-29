#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef ACCEL_H
#define ACCEL_H

/** Class that interfaces with
 * the Accelerometer sensor in the IMU
 * to read its data
 */
class Accelerometer : private ICompassBase {
	private:
		/**
		 * Private method that checks if the Accelerometer
		 * has new data available, and if so, it copies it into m_Vector
		 */
		void pvt_RetrieveData() override;
	public:
		using ICompassBase::ICompassBase;
		using ICompassBase::Values;
		using ICompassBase::PrintDebugInfo;
};

#include "accel.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
