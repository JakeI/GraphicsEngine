#pragma once

#include "Camera.h"

class Camera2 : public Camera
{
private:

	struct Range2D {
		float t, b, l, r;
		float x, y;
		Range2D(float x, float y, float top, float bottom, float left, float right) {
			this->x = x; this->y = y; t = top; b = bottom; l = left; r = right;
		}
	} center;
	float dragSpeed;

	struct Range {
		float min, max, current;
		Range(float min, float max, float current) {
			this->min = min; this->max = max; this->current = current;
		}
	} scale;
	float scaleSpeed;

public:
	Camera2();
	~Camera2();

	void moveBy(glm::vec2 & delta);
	void scaleBy(float delta);

	inline void setScales(float min, float max) { scale.min = min; scale.max = max; }
	inline void setDragSpeed(float speed) { dragSpeed = speed; }
	inline void setBound(float top, float bottom, float left, float right) {
		center.t = top; center.b = bottom; center.l = left; center.r = right;
	}
	inline void setScaleSpeed(float speed) { scaleSpeed = speed; }

	glm::mat4 getView() override;
};

