#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "../headers.hpp"

/*! \struct motorSpeeds
 *  \brief A structure to hold the motor speeds.
 */
struct motorSpeeds {
  uint16_t left, right;
};


/*! \class MotorController
 *  \brief A class to control the Zumo32U4 motors.
 * 
 *  This class inherits from Sensor and provides methods to control the motor
 *  speeds, read the current speeds, and stop the motors.
 */
class MotorController : public Sensor {
  private:
    Zumo32U4Motors motors; /*!< Instance of Zumo32U4Motors to control the motors */

  public:
      /*! \brief Constructor for MotorController. */
    MotorController();

     /*! \brief Reads the current speeds of the motors.
     *  \return A motorSpeeds struct containing the speeds of the left and right motors.
     */
    motorSpeeds read();

    /*! \brief Sets the speeds for both motors.
     *  \param newLeft Speed for the left motor.
     *  \param newRight Speed for the right motor.
     */
    void setSpeed(int newLeft, int newRight);

    /*! \brief Stops both motors. */
    void stop();
};

//#include "MotorController.cpp"

#endif // MOTORCONTROLLER_H