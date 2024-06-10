#include "../headers.hpp"


//! \brief MotorController constructor
MotorController::MotorController() {}

/*! \brief Sets the speeds for both motors.
 *
 *  This function constrains the speed values to be within the range -350 to 350
 *  and then sets the speeds using the Zumo32U4Motors instance.
 *  
 *  \param newLeft Speed for the left motor.
 *  \param newRight Speed for the right motor.
 */
void MotorController::setSpeed(int newLeft, int newRight){
  newLeft = constrain(newLeft, -350, 350);
  newRight = constrain(newRight, -350, 350);
  motors.setSpeeds(newLeft, newRight);
}

/*! \brief Reads the current speeds of the motors.
 *
 *  This function reads the current speeds and returns them.
 *  
 *  \return A motorSpeeds struct containing the speeds of the left and right motors.
 */
motorSpeeds MotorController::read() {
  return { OCR1B, OCR1A };
}

/*! \brief Stops both motors.
 *
 *  This function stops both motors by setting their speeds to 0.
 */
void MotorController::stop(){
  motors.setSpeeds(0, 0);
}

