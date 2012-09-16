#include "Input.h"
#include <s3ePointer.h>

Input::Input()
{
}

Input::~Input()
{
}

bool Input::Clicked() const
{
	return s3ePointerGetState(S3E_POINTER_BUTTON_LEFTMOUSE) == S3E_POINTER_STATE_RELEASED ||
		   s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) == S3E_POINTER_STATE_RELEASED;
}

void Input::Update()
{
	s3ePointerUpdate();
}

float Input::GetMouseX() const
{
	return (float)s3ePointerGetX();
}

float Input::GetMouseY() const
{
	return (float)s3ePointerGetY();
}