#ifndef CONNECTION_MODULE_
#define CONNECTION_MODULE_
//struct {
//  //======sensor============
//  unsigned char m_button: 1;
//  unsigned char m_slider: 1;
//  unsigned char m_module_input_3: 1;
//  unsigned char m_module_input_4: 1;
//} connect_sensor_module;

//typedef struct {
//  //=====actuator==========
//  unsigned char m_led: 1;
//  unsigned char m_gripper: 1;
//  unsigned char m_module_output_3: 1;
//  unsigned char m_module_output_4: 1;
//} connect_actuator_module_typpe;
//
union {
  unsigned char states;
  struct {
    //======sensor============
    unsigned char m_button: 1;
    unsigned char m_slider: 1;
    unsigned char m_module_input_3: 1;
    unsigned char m_module_input_4: 1;
  } connect_state;
} sensor_module;

union {
  unsigned char states;
  struct {
   //=====actuator==========
  unsigned char m_led: 1;
  unsigned char m_gripper: 1;
  unsigned char m_module_output_3: 1;
  unsigned char m_module_output_4: 1;
  } connect_state;
} actuator_module;
#endif
