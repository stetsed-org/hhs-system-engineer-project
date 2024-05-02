#include "../../../headers.hpp"
#include "../compassbase.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnetometer : private CompassBase {
	private:
		void _retrieveData() override;
	public:
		using CompassBase::CompassBase;
		using CompassBase::Values;
		using CompassBase::PrintDebugInfo;
};

#include "magnet.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
