#pragma once

#include "StdAfx.h"
#include "Event.h"

//Mouse Button click masks
#define MOUSE_MASK_NONE		0x0
#define MOUSE_MASK_LEFT		0x2
#define MOUSE_MASK_RIGHT	0x4
#define MOUSE_MASK_MIDDLE	0x8
typedef int MOUSE_MASK;

class InputState
{
public:
	InputState();
	~InputState();

	class WindowSize {
	public:
		int w;
		int h;
		WindowSize();
		glm::ivec2 get();
	} windowSize;

	class Mouse {
	public:
		MOUSE_MASK mask;
		int x;
		int y;
		int dx;
		int dy;
		int wheel;
		Mouse();
		glm::ivec2 get();
		glm::ivec2 getDelta();
		bool isRdown();
		bool isLdown();
		bool isMdown();
		void setX(int x);
		void setY(int y);
	} mouse;

	class Keyboard {
	private:
		static const int bitsPint = 8 * sizeof(unsigned int);
		static const int numKeys = 256;
		static const int dataLen = numKeys / bitsPint;
		unsigned int data[dataLen];
	public:
		Keyboard();
		void set(int id, bool value);
		void setFalse(int id);
		void setTrue(int id);
		bool get(int id);
	} keyboard;

	void update(Event* e);
};

