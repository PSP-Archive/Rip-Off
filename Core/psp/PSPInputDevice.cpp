#ifdef _SPSP

#include "psp/PSPInputDevice.h"
#include "psp/PSPOS.h"
#include "input/InputManager.h"

unsigned int PSPInputDevice::m_button = 0;
unsigned int PSPInputDevice::m_prevButton = 0;

//--------------------------------------------------------------------------------
PSPInputDevice::PSPInputDevice() :
	m_numGamepads(1)
{
	// Standard bindings
	standardBindings();
}

//--------------------------------------------------------------------------------
bool 
PSPInputDevice::init(const ConfigItem* conf)
{
	// The PSP Controller Service runs as a default module. 
	// Explicit initialization is not necessary.

	// Enable analog input
	sceCtrlSetSamplingMode( SCE_CTRL_MODE_DIGITALANALOG ) ;
	

	// Load the bindings
	loadBindings(conf);

	return true;
}

//--------------------------------------------------------------------------------
void
PSPInputDevice::update(InputManagerBase* input)
{
	// Retrieve the buffered data from the gamepads
	//for(unsigned int i=0; i<m_numGamepads; i++)
	//{
		// Use to store controller buffered data
		SceCtrlData items;
		
		// Keep previous pressed button
		m_prevButton = m_button;

		// Retrieves controller state data
		sceCtrlReadBufferPositive(&items, 1);

		// Parse the output
		processGamepadInput(input, items);
	//}
}

//--------------------------------------------------------------------------------
void
PSPInputDevice::cleanUp()
{


}

//--------------------------------------------------------------------------------
void 
PSPInputDevice::standardBindings()
{
	// Standard gamepad controls for all
	//for(unsigned int i=0; i<m_numGamepads; i++)
	//{
		m_gamepadBindings[0][UP] = SCE_CTRL_UP;
		m_gamepadBindings[0][DOWN] = SCE_CTRL_DOWN;
		m_gamepadBindings[0][LEFT] = SCE_CTRL_LEFT;
		m_gamepadBindings[0][RIGHT] = SCE_CTRL_RIGHT;
		m_gamepadBindings[0][BUTTON1] = SCE_CTRL_TRIANGLE;
		m_gamepadBindings[0][BUTTON2] = SCE_CTRL_SQUARE;
		m_gamepadBindings[0][BUTTON3] = SCE_CTRL_CIRCLE;
		m_gamepadBindings[0][BUTTON4] = SCE_CTRL_CROSS;
		m_gamepadBindings[0][START] = SCE_CTRL_START;
		m_gamepadBindings[0][SELECT] = SCE_CTRL_SELECT;
	//}

}

//--------------------------------------------------------------------------------
void 
PSPInputDevice::loadBindings(const ConfigItem* conf)
{
	// PSP Gamepads
	//for(unsigned int i=0; i<m_numGamepads; i++)
	//{

		for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
		{
			_STL::string prefix = "psp_";
			if(conf->hasString(prefix.append(getButtonSuffix(j))))
			{
				m_gamepadBindings[0][j] = resolveGamepadButton(conf->getString(prefix));
			}
		}
	//}

}

//--------------------------------------------------------------------------------
_STL::string 
PSPInputDevice::getButtonSuffix(unsigned int button)
{
	switch(static_cast<ButtonType>(button))
	{
		case UP:
			return "UP";
		case DOWN:
			return "DOWN";
		case LEFT:
			return "LEFT";
		case RIGHT:
			return "RIGHT";
		case BUTTON1:
			//return "BTN1";
			return "TRIANGLE";
		case BUTTON2:
			//return "BTN2";
			return "SQUARE";
		case BUTTON3:
			//return "BTN3";
			return "CIRCLE";
		case BUTTON4:
			//return "BTN4";
			return "CROSS";
		case START:
			return "START";
		case SELECT:
			return "SELECT";
	}

	return "";

}

//--------------------------------------------------------------------------------
unsigned int 
PSPInputDevice::resolveGamepadButton(const _STL::string& name)
{
	if(!(name == "none")) return 0;
	if(!(name == "start")) return SCE_CTRL_START;
	if(!(name == "select")) return SCE_CTRL_SELECT;
	if(!(name == "up")) return SCE_CTRL_UP;
	if(!(name == "right")) return SCE_CTRL_RIGHT;
	if(!(name == "down")) return SCE_CTRL_DOWN;
	if(!(name == "left")) return SCE_CTRL_LEFT;
	if(!(name == "triangle")) return SCE_CTRL_TRIANGLE;
	if(!(name == "circle")) return SCE_CTRL_CIRCLE;
	if(!(name == "cross")) return SCE_CTRL_CROSS;
	if(!(name == "square")) return SCE_CTRL_SQUARE;

	//if(!(name == "button1")) return SCE_CTRL_SELECT;
	//if(!(name == "button2")) return SCE_CTRL_START;
	//if(!(name == "button3")) return SCE_CTRL_UP;
	//if(!(name == "button4")) return SCE_CTRL_RIGHT;
	//if(!(name == "button5")) return SCE_CTRL_DOWN;
	//if(!(name == "button6")) return SCE_CTRL_LEFT;
	//if(!(name == "button7")) return SCE_CTRL_L;
	//if(!(name == "button8")) return SCE_CTRL_R;
	//if(!(name == "button9")) return SCE_CTRL_TRIANGLE;
	//if(!(name == "button10")) return SCE_CTRL_CIRCLE;
	//if(!(name == "button11")) return SCE_CTRL_CROSS;
	//if(!(name == "button12")) return SCE_CTRL_SQUARE;
	//if(!(name == "button13")) return SCE_CTRL_INTERCEPTED;
	//if(!(name == "button14")) return SCE_CTRL_HOLD;
}

//--------------------------------------------------------------------------------
void 
PSPInputDevice::processGamepadInput(InputManagerBase* input, SceCtrlData buf)
{
	// Clean up previous button 	
	//input->setButtonState(0, static_cast<ButtonType>(m_prevButton), false);

	
	for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
	{
		input->setButtonState(0, static_cast<ButtonType>(j), false);
	}


	// Access to button pressed
	m_button = buf.Buttons;

		if(m_button == m_gamepadBindings[0][UP])
		{
			input->setButtonState(0, MOVEUP, true);
		}
		// reverse order of turning???
		if(m_button == m_gamepadBindings[0][LEFT])
		{
			input->setButtonState(0, TURNRIGHT, true);
		}
		else if(m_button == m_gamepadBindings[0][RIGHT])
		{
			input->setButtonState(0, TURNLEFT, true);
		}

	for(unsigned int j=0; j<MOVEUP; j++)
	{
		if((m_button &~ m_prevButton) & m_gamepadBindings[0][j])
		{

			input->setButtonState(0, static_cast<ButtonType>(j), true);
			m_prevButton = j;
			return;
		}
	}

	// analog input
	float dx = ( buf.Lx - 128 ) / 128.0f ;
	float dy = ( buf.Ly - 128 ) / 128.0f ;

	//if ( dx > -0.75f && dx < 0.75f ) dx = 0.0f ;
	//if ( dy > -0.75f && dy < 0.75f ) dy = 0.0f ;

	if ( dx > 0.75f ) 
	{
		input->setButtonState(0, TURNLEFT, true);
	}
	else if(dx < -0.75f)
	{
		input->setButtonState(0, TURNRIGHT, true);
	}
	//else
	//{
	//	input->setButtonState(0, TURNLEFT, false);
	//	input->setButtonState(0, TURNRIGHT, false);
	//}

	if(dy > 0.75f)
	{
		input->setButtonState(0, DOWN, true);
	}
	else if(dy < -0.75f)
	{
		input->setButtonState(0, MOVEUP, true);
	}
	//else
	//{
	//	input->setButtonState(0, MOVEUP, false);
	//	input->setButtonState(0, DOWN, false);
	//}

	//// Parse the output
	//if ((m_button ^ m_prevButton) & SCE_CTRL_START) {
	//	printf("you pressed start\n");
	//	input->setButtonState(0, START, true);
	//}
	//else if (m_button & SCE_CTRL_SELECT) {
	//	printf("you pressed select\n");
	//	//input->setButtonState(0, SELECT, true);

	//}
	//else if (m_button & SCE_CTRL_UP) {
	//	printf("you pressed up\n");
	//	input->setButtonState(0, UP, true);

	//}
	//else if (m_button & SCE_CTRL_DOWN) {
	//	printf("you pressed down\n");
	//	input->setButtonState(0, DOWN, true);

	//}
	//else if (m_button & SCE_CTRL_LEFT) {
	//	printf("you pressed left\n");
	//	input->setButtonState(0, LEFT, true);

	//}
	//else if (m_button & SCE_CTRL_RIGHT) {
	//	printf("you pressed right\n");
	//	input->setButtonState(0, RIGHT, true);

	//}
	//else if (m_button & SCE_CTRL_TRIANGLE) {
	//	printf("you pressed triangle\n");
	//	input->setButtonState(0, BUTTON1, true);

	//}
	//else if (m_button & SCE_CTRL_SQUARE) {
	//	printf("you pressed square\n");
	//	input->setButtonState(0, BUTTON2, true);

	//}
	//else if (m_button & SCE_CTRL_CIRCLE) {
	//	printf("you pressed circle\n");
	//	input->setButtonState(0, BUTTON3, true);

	//}
	//else if (m_button & SCE_CTRL_CROSS) {
	//	printf("you pressed cross\n");
	//	input->setButtonState(0, BUTTON4, true);

	//}
	//else if (m_button & SCE_CTRL_L) {
	//	//input->setButtonState(0, L, true);

	//}
	//else if (m_button & SCE_CTRL_R) {
	//	//input->setButtonState(0, R, true);

	//}
}

#endif

