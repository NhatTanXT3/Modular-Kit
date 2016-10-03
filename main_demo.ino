//#include <I2Cdev.h>

// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain


#include "Communication.h"

#include "module_led.h"
#include "module_gripper.h"
#include "module_slider.h"
#include "module_button.h"
#include "module_recorder.h"

#include "connection_module.h"

int intPin = 2;

//
//int pushButton = 2;
//int buttonState = 0;


/*=====================================
             timer variables
  =====================================*/
unsigned long currentMicros;
unsigned long previousMicros_100Hz = 0;        // will store last time it was called for 100Hz timer
const long interval_100Hz = 10000;           // interval at which to do 100Hz task(micros)

unsigned long previousMicros_50Hz = 0;        // will store last time it was called for 50Hz timer
const long interval_50Hz = 20000;           // interval at which to do 50Hz task (micros)

unsigned long previousMicros_200Hz = 0;       // will store last time it was called for 200Hz timer
const long interval_200Hz = 5000;           // interval at which to do 200Hz task (micros)


void setup() {
  Serial.begin(115200);

  //  attachInterrupt(digitalPinToInterrupt(intPin), flagINTpin, RISING);
  //  IMU_init();
  //  Serial.println(" Calib gyro ...");
  //  while (Calib_Gyro());
  m_gripper_init();
  m_led_init();
  m_button_init();
  //  Serial.println(sensor_module.states, BIN);
  //  sensor_module.connect_state.m_button = 1;
  //  Serial.println(sensor_module.states, BIN);
  //  sensor_module.connect_state.m_slider = 1;
  //  sensor_module.connect_state.m_button = 0;
  //  Serial.println(sensor_module.states, BIN);

}

void loop() {
  serialEvent();
  currentMicros = micros();
  if (currentMicros - previousMicros_200Hz >= interval_200Hz)
  {
    previousMicros_200Hz = currentMicros;
    //your code begin from here
  }

  if (currentMicros - previousMicros_100Hz >= interval_100Hz)
  {
    previousMicros_100Hz = currentMicros;
    //your code begin from here


  }

  if (currentMicros - previousMicros_50Hz >= interval_50Hz)
  {
    previousMicros_50Hz = currentMicros;
    //your code begin from here
    if (flag.display)
    {
      display();
    }
    if(actuator_module.connect_state.m_gripper)
    m_gripper_behavior();
    if(actuator_module.connect_state.m_led)
    m_led_behavior();
  }

}

void display() {
  //your code start from here
  //  Serial.write(CN_1);
  //  Serial.print(m_slider.outputValue);
  //  Serial.write(CN_2);
  //  Serial.println(sensorValue);
  //    Serial.write(CN_3);
  //    Serial.println(MPU6050.accZ_raw);
  //  Serial.write(CN_4);
  //  Serial.print(PID_position.set_point);
  //  Serial.write(CN_5);
  //  Serial.print(training_position);
  //  Serial.write(CN_6);
  //  Serial.print(PID_admittance.output);
  //  Serial.write(CN_7);
  //  Serial.println(PID_force.set_point);
  //  Serial.write(CN_8);e
  //  Serial.println(position_setpoint);
  //        Serial.write(CN_9);
  //        Serial.println(as_filter[5]);



}
void display_network_infor() {
  Serial.println(" ");
  Serial.println("system includes: ");
  Serial.println("===sensor module===");
  if (sensor_module.connect_state.m_button)
    Serial.println("+ button module");
  if (sensor_module.connect_state.m_slider)
    Serial.println("+ slider module");
  Serial.println("===actuator module===");
  if (actuator_module.connect_state.m_gripper)
    Serial.println("+ gripper module");
  if (actuator_module.connect_state.m_led)
    Serial.println("+ led module");
    Serial.println(" ");
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    command[command_index] = inChar;
    command_index++;

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }

  if (stringComplete) {
    Serial.print(command);

    switch (command[0])
    {
      case DISPLAY_ON_:
        flag.display = 1;
        break;
      case DISPLAY_OFF_:
        flag.display = 0;
        break;
      default:
        break;
      case CONNECT_MODULE_:
        switch (command[1])
        {
          case M_BUTTON_:
            if (command[2] == MODULE_ON_)
            {
              sensor_module.connect_state.m_button = 1;
              Serial.println("connect button");
            }
            else
            {
              sensor_module.connect_state.m_button = 0;
              Serial.println("disconnect button");
            }
            break;
          case M_SLIDER_:
            if (command[2] == MODULE_ON_)
            {
              sensor_module.connect_state.m_slider = 1;
              Serial.println("connect slider");
            }
            else
            {
              sensor_module.connect_state.m_slider = 0;
              Serial.println("disconnect slider");
            }
            break;
          case M_GRIPPER_:
            if (command[2] == MODULE_ON_)
            {
              actuator_module.connect_state.m_gripper = 1;
              Serial.println("connect gripper");
            }
            else
            {
              actuator_module.connect_state.m_gripper = 0;
              Serial.println("disconnect gripper");
            }
            break;
          case M_LED_:
            if (command[2] == MODULE_ON_)
            {
              Serial.println("connect led");
              actuator_module.connect_state.m_led = 1;
            }
            else
            {
              Serial.println("disconnect led");
              actuator_module.connect_state.m_led = 0;
            }
            break;
          case DISCONNECT_:
             actuator_module.states = 0;
             sensor_module.states = 0;
             Serial.println("disconnect all");
             break;           
        }
        display_network_infor();
        break;
    }
    memset(command, 0, sizeof(command));
    command_index = 0;
    // clear the string:
    stringComplete = false;
  }
}
