#include "Input.h"
#include <s3ePointer.h>
#include <s3eDevice.h>
#include <s3eDebug.h>

Input::Input()
{
}

Input::~Input()
{
}

bool Input::clicked() const
{
	return s3ePointerGetState(S3E_POINTER_BUTTON_LEFTMOUSE) == S3E_POINTER_STATE_RELEASED ||
		   s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) == S3E_POINTER_STATE_RELEASED;
}

bool Input::pressed() const
{
	return s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_DOWN;
}

void Input::update()
{
	//s3eDeviceUnYield();
	s3ePointerUpdate();
}

int Input::getPointerX() const
{
	return s3ePointerGetX();
}

int Input::getPointerY() const
{
	return s3ePointerGetY();
}