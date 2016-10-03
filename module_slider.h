#ifndef MODULE_SLIDER_
#define MODULE_SLIDER_

#define MIN_SLIDER_OUTPUT_  110
#define MAX_SLIDER_OUTPUT_  180
struct {
  const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
  int sensorValue = 0;        // value read from the pot
  int outputValue = 0;        // value output to the PWM (analog out)
} m_slider;


void m_slider_init()
{
 
}

int m_slider_update()
{
   m_slider.sensorValue = analogRead(m_slider.analogInPin);
   m_slider.outputValue = map(m_slider.sensorValue, 0, 1023, 110, 180);
   return m_slider.outputValue;
}

#endif
