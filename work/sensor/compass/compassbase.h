#include "../../headers.hpp"
#include <Zumo32U4IMU.h>

#ifndef COMPASSBASE_H
#define COMPASSBASE_H

struct Vector3 { int16_t x,y,z; };

// this is a class meant as a template only!!! is abstract class :3c
class CompassBase {
	// the object that allows us to interface with the IMU-sensors
	protected:
		Vector3 _vector; // the Vector3 struct (x,y,z) that holds the data that has been read
		Zumo32U4IMU _interface; // contains methods to read raw values, as well as three containers to temporarily  store them in;
					// container names: 'a' for accel readings, 'g' for gyro readings, 'm' for magnet readings
					// these containers will only be used by their respective derived-classes
		
	private:
		virtual void _retrieveData() = 0; // template method that will make the derived class read from its respective sensor
	
	public: 
		CompassBase(); // constructor that's gonna be copied to all derived classes (accel, gyro, magnet)
		Vector3 Values(); // public method that allows the Zumo to read whatever is currently stored in '_vector'
				  
	// methods are defined in attached file, 'compassbase.cpp'
};

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
