#include <avr/io.h>

typedef enum{
            NEUTRAL = 1,
            UP = 2,
            DOWN = 3,
            RIGHT = 4,
            LEFT = 5,
            }Direction;

struct  pos{
            int8_t x;
            int8_t y;
            };
void initJoystick(void); 
struct pos readJoystick(void);
struct pos joyPosition(void);
Direction joyDirection(void);
uint8_t readButton(void);
