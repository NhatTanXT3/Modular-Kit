#include "connection_module.h"
#include "module_button.h"
#include "module_slider.h"

struct {
  unsigned char m_button = 2;
  unsigned char m_slider = 1;
} input_priority_led;

struct {
  int ledPin = 13;
  int ledState = 0;
} m_led;


void m_led_init()
{
  pinMode(m_led.ledPin, OUTPUT); // pin for testing
}

void m_led_update(unsigned char value)
{
  analogWrite(m_led.ledPin,value);
   m_led.ledState=value;
//  if(value==0)
//  {
//   m_led.ledState=0;
//   digitalWrite(m_led.ledPin, m_led.ledState);
//  }
//  else
//  {
//    m_led.ledState=1;
//    digitalWrite(m_led.ledPin, m_led.ledState);
//  }

}

void m_led_action_1()
{
  if (m_button_update())
    m_led_update(255);
  else
    m_led_update(0);
}
void m_led_action_2()
{
  m_slider_update();
  m_led_update(m_slider.sensorValue);
}

void m_led_behavior()
{
  switch (sensor_module.states) {
    case 0b11:
      if (input_priority_led.m_slider > input_priority_led.m_button)
        m_led_action_2();
      else
        m_led_action_1();
      break;
    case 0b01:
        m_led_action_1();
      break;
    case 0b10:
        m_led_action_2();
      break;
    default:
      break;
  }

}


