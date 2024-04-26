#include "../../../headers.hpp"
#include "../compassbase.h"

class Magnetometer : public CompassBase {
	using CompassBase::CompassBase;

	protected:
		void _retrieveData() override;
};

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
