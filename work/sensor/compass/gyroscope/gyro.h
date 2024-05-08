#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef GYRO_H
#define GYRO_H

/** Class that interfaces with
 * the Gyroscope sensor in the IMU
 * to read its data
 */
class Gyroscope : private ICompassBase {
	private:
		/**
		 * Private method that checks if the Gyroscope
		 * has new data available, and if so, it copies it into m_Vector
		 */
		void pvt_RetrieveData() override;
	public:
		using ICompassBase::ICompassBase;
		using ICompassBase::Values;
		using ICompassBase::PrintDebugInfo;
};

#include "gyro.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
