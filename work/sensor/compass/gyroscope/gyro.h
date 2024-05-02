#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef GYRO_H
#define GYRO_H

class Gyroscope : private CompassBase {
	private:
		void _retrieveData() override;
	public:
		using CompassBase::CompassBase;
		using CompassBase::Values;
		using CompassBase::PrintDebugInfo;
};

#include "gyro.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
