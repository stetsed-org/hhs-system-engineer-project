#include "../../headers.hpp"
#include <Zumo32U4IMU.h>

#ifndef COMPASSBASE_H
#define COMPASSBASE_H

/**
 * the struct containing three
 * 16bit integers that will hold
 * the values read by the sensor
 * attached to the child-class
 * of CompassBase
 */
struct Vector3 { int16_t x,y,z; };

/**
 * This is a class meant as a template only!!!
 * Is abstract class! :3c
 * 
 * This is the base class for all Zumo IMU-interfacing classes.
 * The Accelerometer, Gyroscope and Magnetometer classes
 * are all derived from this class (CompassBase).
 */
class CompassBase {
	protected:
		/**
		 * the Vector3 struct (x,y,z) that holds
		 * the data that gets read from the sensor
		 */
		Vector3 m_Vector;
		
		/**
		 * The object that allows us to interface with the IMU-sensors.
		 * It contains methods to read raw values
		 * as well as three containers to
		 * temporarily  store them in;
		 * 
		 * 
		 * Container names:
		 * 'a' for accel readings -
		 * 'g' for gyro readings -
		 * 'm' for magnet readings
		 *
		 * These containers will only be used by
		 * their respective derived-classes
		 */
		Zumo32U4IMU* m_InterfacePTR;
					
		
	private:
		/**
		 * Template method that will make
		 * the derived class read from
		 * its respective sensor
		 */
		virtual void pvt_RetrieveData() = 0;
	
	public: 
		/**
		 * Constructor that places a pointer to
		 * the pre-initialized Zumo32U4IMU sensor class
		 * in the m_InterfacePTR member variable
		 */
		CompassBase(Zumo32U4IMU*);
		
		/**
		 * Public method that allows the Zumo to read
		 * whatever is currently stored in 'm_Vector'
		 * 
		 * Basically: This method returns the current x,y,z (Vector3)
		 * for the sensor you call this method on.
		 */
		Vector3 Values();
		
		/**
		 * Prints debug info.
		 * Currently only the type of sensor that is detected.
		 */
		void PrintDebugInfo();
				  
	// methods are defined in attached file, 'compassbase.cpp'
};

#include "compassbase.cpp"

#endif

// written by: Erynn 'foorpyxof' Scholtes | 2024 NSE Zumo project
