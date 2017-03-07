#ifndef _InitializingState_h
#define _InitializingState_h

#include <State.h>
#include <WallSwitch.h>

// Pines de conexion del LCD
#define LCD_CS A11 // Chip Select - Pin analogico 3
#define LCD_CD A10 // Command/Data - Pin Analogico 2
#define LCD_WR A9 // LCD Write - Pin Analogico 1
#define LCD_RD A8 // LCD Read - Pin Analogico 0
#define LCD_RESET A12 // LCD Reset - Pin Analogico 4

#define   RED     0xF800
#define   GREEN   0x07E0
#define   WHITE   0xFFFF
#define   BLUE    0x001F
#define   CYAN    0x07FF
#define   YELLOW  0xFFE0
#define   MAGENTA 0xF81F
#define   BLACK   0x0000

class InitializingState : public State<WallSwitch>
{
	private:
		InitializingState(){};
		void initializeTFT(WallSwitch* ws);
		void initializeButton(WallSwitch* ws);
		bool loadConfiguration();


	public:
	  	static InitializingState* Instance();
		void enter(WallSwitch* ws);
		void execute(WallSwitch* ws);
		void exit(WallSwitch* ws);
};

#endif
