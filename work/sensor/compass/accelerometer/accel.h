#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef ACCEL_H
#define ACCEL_H

class Accelerometer : private CompassBase {
	private:
		void pvt_RetrieveData() override;
	public:
		using CompassBase::CompassBase;
		using CompassBase::Values;
		using CompassBase::PrintDebugInfo;
};

#include "accel.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
