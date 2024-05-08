#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef MAGNET_H
#define MAGNET_H

/** Class that interfaces with
 * the Magnetometer sensor in the IMU
 * to read its data
 */
class Magnetometer : private ICompassBase {
	private:
		/**
		 * Private method that checks if the Magnetometer
		 * has new data available, and if so, it copies it into m_Vector
		 */
		void pvt_RetrieveData() override;
	public:
		using ICompassBase::ICompassBase;
		using ICompassBase::Values;
		using ICompassBase::PrintDebugInfo;
};

#include "magnet.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
