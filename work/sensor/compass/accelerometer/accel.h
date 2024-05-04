#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef ACCEL_H
#define ACCEL_H

/** Class that interfaces with
 * the Accelerometer sensor in the IMU
 * to read its data
 */
class Accelerometer : private CompassBase {
	private:
		/**
		 * Private method that checks if the Accelerometer
		 * has new data available, and if so, it copies it into m_Vector
		 */
		void pvt_RetrieveData() override;
	public:
		using CompassBase::CompassBase;
		using CompassBase::Values;
		using CompassBase::PrintDebugInfo;
};

#include "accel.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
