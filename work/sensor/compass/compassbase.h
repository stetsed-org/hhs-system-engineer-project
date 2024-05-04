#include "../../headers.hpp"
#include <Zumo32U4IMU.h>

#ifndef COMPASSBASE_H
#define COMPASSBASE_H

struct Vector3 { int16_t x,y,z; };	/* the struct containing three
					16bit integers that will hold
					the values read by the sensor
					attached to the child-class
					of CompassBase */

// this is a class meant as a template only!!!
// is abstract class :3c
class CompassBase {
	protected:
		Vector3 m_Vector; // the Vector3 struct (x,y,z) that holds
				 // the data that has been read
		
		// the object that allows us to interface with the IMU-sensors
		Zumo32U4IMU* m_InterfacePTR;	// it contains methods to read raw values
					// as well as three containers to
					// temporarily  store them in;
					// 
					// container names:
					// 'a' for accel readings
					// 'g' for gyro readings
					// 'm' for magnet readings
					//
					// these containers will only be used by
					// their respective derived-classes
		
	private:
		virtual void pvt_RetrieveData() = 0;	// template method that will make
						// the derived class read from
						// its respective sensor
	
	public: 
		CompassBase(Zumo32U4IMU*);	// constructor that's gonna be inherited
			       					// by all derived classes
			       					// (accel, gyro, magnet)
		
		Vector3 Values();	// public method that allows the Zumo to read
				 	// whatever is currently stored in '_vector'

		void Initialize();
		
		void PrintDebugInfo();
				  
	// methods are defined in attached file, 'compassbase.cpp'
};

#include "compassbase.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
