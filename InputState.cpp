#include "InputState.h"

InputState::InputState(){

}


InputState::~InputState(){

}

InputState::WindowSize::WindowSize() {
	w = 1;
	h = 1;
}

inline glm::ivec2 InputState::WindowSize::get() {
	return glm::ivec2(w, h);
}

InputState::Mouse::Mouse() {
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	wheel = 0;
}

glm::ivec2 InputState::Mouse::get() {
	return glm::ivec2(x, y);
}

glm::ivec2 InputState::Mouse::getDelta() {
	return glm::ivec2(dx, dy);
}

bool InputState::Mouse::isRdown() {
	return (bool)(mask & MOUSE_MASK_RIGHT);
}

bool InputState::Mouse::isLdown() {
	return (bool)(mask & MOUSE_MASK_LEFT);
}

bool InputState::Mouse::isMdown() {
	return (bool)(mask & MOUSE_MASK_MIDDLE);
}

void InputState::Mouse::setX(int x) {
	this->dx = x - this->x;
	this->x = x;
}

void InputState::Mouse::setY(int y) {
	this->dy = y - this->y;
	this->y = y;
}

InputState::Keyboard::Keyboard() {
	for (int i = 0; i < dataLen; i++)
		data[i] = 0;
}

void InputState::Keyboard::set(int id, bool value) {
	if (value)
		setTrue(id);
	else
		setFalse(id);
}

void InputState::Keyboard::setFalse(int id) {
	// 1010 & 1101 == 1000
	data[id / bitsPint] &= ~(1 << (id % bitsPint));
}

void InputState::Keyboard::setTrue(int id) {
	// 1010 | 0010 == 1010
	// 1000 | 0010 == 1010
	data[id / bitsPint] |= (1 << (id % bitsPint));
}

bool InputState::Keyboard::get(int id) {
	return data[id / bitsPint] & (1 << (id % bitsPint));
}

void InputState::update(Event* e) {
	switch (e->type) {
	case Event::EventType::KEY_DOWN:
		keyboard.setTrue(e->a);
		return;
	case Event::EventType::KEY_UP:
		keyboard.setFalse(e->a);
		return;
	case Event::EventType::CHAR_DOWN:
		//Unused
		return;
	case Event::EventType::MOUSE_MOVE:
		mouse.setX(e->a);
		mouse.setY(e->b);
		return;
	case Event::EventType::MOUSE_L_DOWN:
		mouse.mask |= MOUSE_MASK_LEFT;
		return;
	case Event::EventType::MOUSE_L_UP:
		mouse.mask &= ~MOUSE_MASK_LEFT;
		return;
	case Event::EventType::MOUSE_M_DOWN:
		mouse.mask |= MOUSE_MASK_MIDDLE;
		return;
	case Event::EventType::MOUSE_M_UP:
		mouse.mask &= ~MOUSE_MASK_MIDDLE;
		return;
	case Event::EventType::MOUSE_R_DOWN:
		mouse.mask |= MOUSE_MASK_RIGHT;
		return;
	case Event::EventType::MOUSE_R_UP:
		mouse.mask &= ~MOUSE_MASK_RIGHT;
		return;
	case Event::EventType::MOUSE_WHEEL:
		mouse.wheel = e->a;
		return;
	case Event::EventType::SIZE_CHANGE:
		windowSize.w = e->a;
		windowSize.h = e->b;
		return;
	}
}
