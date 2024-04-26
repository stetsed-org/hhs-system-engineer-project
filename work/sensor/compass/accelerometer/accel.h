#include "../../../headers.hpp"
#include "../compassbase.h"

class Accelerometer : public CompassBase {
	using CompassBase::CompassBase;

	private:
		void _retrieveData() override;
};

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
