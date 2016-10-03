#include <Servo.h>
#include "connection_module.h"
#include "module_button.h"
#include "module_slider.h"

#define SERVO_MIN_ 110
#define SERVO_MAX_ 180

struct {
  unsigned char m_button = 1;
  unsigned char m_slider = 2;
} input_priority_gripper;

struct {
  int servoPin = 9;
  int servoValue = SERVO_MAX_;
} m_gripper;

Servo myservo;

void m_gripper_init()
{
  myservo.attach(m_gripper.servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(m_gripper.servoValue);
}

void m_gripper_update(int value)
{
  if (value < SERVO_MIN_)
    value = SERVO_MIN_;
  else if (value > SERVO_MAX_)
    value = SERVO_MAX_;

  myservo.write(value);
  m_gripper.servoValue = value;
}

void m_gripper_action_1()
{
  if (m_button_update())
    m_gripper_update(SERVO_MIN_);
  else
    m_gripper_update(SERVO_MAX_);
}
void m_gripper_action_2()
{
  m_gripper_update(m_slider_update());
}

void m_gripper_behavior()
{
  switch (sensor_module.states) {
    case 0b11:
      if (input_priority_gripper.m_slider > input_priority_gripper.m_button)
        m_gripper_action_2();
      else
        m_gripper_action_1();
      break;
    case 0b01:
        m_gripper_action_1();
      break;
    case 0b10:
        m_gripper_action_2();
      break;
    default:
      break;
  }

}


