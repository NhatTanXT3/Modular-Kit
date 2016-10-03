#ifndef MODULE_BUTTON_
#define MODULE_BUTTON_
struct {
  int pushButton = 2;
  int buttonState = 0;
} m_button;



unsigned char m_button_update()
{
  m_button.buttonState = digitalRead(m_button.pushButton);
  return m_button.buttonState;
}

void m_button_init()
{
   pinMode(m_button.pushButton, INPUT);
}
#endif
