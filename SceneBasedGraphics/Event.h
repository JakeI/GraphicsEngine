#pragma once

#include "StdAfx.h"
#include "Globals.h"

class Event
{
public:

	enum EventType {
		KEY_DOWN,	// key_code = (char)a, 0 = b;
		KEY_UP,		// key_code = (char)a, 0 = b;
		CHAR_DOWN,	// key_code = (char)a

		MOUSE_MOVE, // x_pixel = a, y_pixel = b
		MOUSE_L_DOWN, // x_pixel = a, y_pixel = b
		MOUSE_L_UP, // x_pixel = a, y_pixel = b
		MOUSE_M_DOWN, // x_pixel = a, y_pixel = b
		MOUSE_M_UP, // x_pixel = a, y_pixel = b
		MOUSE_R_DOWN, // x_pixel = a, y_pixel = b
		MOUSE_R_UP, // x_pixel = a, y_pixel = b
		MOUSE_WHEEL, // mouse_rotation = a

		SIZE_CHANGE,// x_size = a, y_size = b;
	} type;
	int a, b, c;
	Event(EventType et, int a = 0, int b = 0, int c = 0) {
		this->type = et;
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Event();
	~Event();
};

