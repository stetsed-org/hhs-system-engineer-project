#include "../../headers.hpp"
#include "compassbase.h"


CompassBase::CompassBase(): _vector.x(0), _vector.y(0), _vector.z(0) { _interface.init(); }

Vector3 CompassBase::Values() {
	return _vector;
}

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
