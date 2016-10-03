#ifndef COMMUNICATION_
#define COMMUNICATION_

struct {
  unsigned char display: 1;
} flag;

char command[100];
unsigned char command_index = 0;
boolean stringComplete = false;  // whether the string is complete

#define CN_1 '~'
#define CN_2 '!'
#define CN_3 '@'
#define CN_4 '#'
#define CN_5 '$'
#define CN_6 '%'
#define CN_7 '^'
#define CN_8 '*'
#define CN_9 '('
#define CN_10 ')'

/*================================
   Nhận từ máy tính xuống
=================================*/
#define HELP_       'h'
#define SYSTEM_INFOR 'i'

#define DISPLAY_ON_  'e'
#define DISPLAY_OFF_ 'f'

#define CONNECT_MODULE_  'm'
#define DISCONNECT_  '0'
#define M_BUTTON_   '1'
#define M_SLIDER_   '2'
#define M_GRIPPER_  '3'
#define M_LED_      '4'

#define MODULE_ON_  '1'
#define MODULE_OFF_ '0'

void serialEvent();

#endif


