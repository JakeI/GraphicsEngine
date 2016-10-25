#pragma once

#include "StdAfx.h"

#include "ModelEntity.h"

template <class T> class Arrow
{
public:
	Arrow() {}
	~Arrow() {}

	virtual void setColor(T & color) {}
	virtual void setByCenter(T & center, T & tangent) {}
	virtual void setByTail(T & tail, T & tangent) {}
	virtual void setByTip(T & tip, T & tangent) {}
	virtual void setByTipTail(T & tip, T & tail) {}
};


class Arrow2 : public Arrow<glm::vec2>, public ModelEntity {
private:

	ConstTransform2Comp transform;

public:
	Arrow2() : Arrow<glm::vec2>(), ModelEntity("res/models/arrow2D.mdl") {
		add(&transform);
	}
	~Arrow2() {}

	void setByCenter(glm::vec2 & center, glm::vec2 & tangent) override {
		float len = glm::length(tangent);
		float angle = atan2(tangent.y, tangent.x);
		Maths::Transform2 trans(center, len, angle);
		transform.getAnimator()->setValue(trans);
	}

	void setByTail(glm::vec2 & tail, glm::vec2 & tip) override {

	}

	void setByTip(glm::vec2 & tip, glm::vec2 & tangent) override {

	}

	void setByTipTail(glm::vec2 & tip, glm::vec2 & tail) override {

	}
};

class Arrow2ConstColor : public Arrow2 {
private:

	ConstColorComp color;

public:

	Arrow2ConstColor() : Arrow2() {
		add(&color);
	}

	void setColor(glm::vec4 & color) {
		this->color.getAnimator()->setValue(color);
	}
};
