#pragma once

#include "StdAfx.h"

class Maths
{
public:
	Maths();
	~Maths();

	struct ProjView {
		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 projView;
		ProjView() : proj(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projView(glm::mat4(1.0f)) {}
		ProjView(glm::mat4 & p, glm::mat4 v) : proj(p), view(v), projView(p*v) {}
		void update() { projView = proj*view; }
	};

	class Transform {
	public:
		Transform() {}
		~Transform() {}
		virtual glm::mat4 getMat() { return glm::mat4(1.0f); }
	};

	class Transform2 : public Transform {
	public:
		glm::vec2 translation;
		glm::vec2 scale;
		float rotation;
		glm::mat4 getMat() override;
		Transform2() : translation(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f) {}
		Transform2(glm::vec2 t, glm::vec2 s, float r) : translation(t), scale(s), rotation(r) {}
		Transform2(float dx, float dy, float sx, float sy, float r) :
			translation(glm::vec2(dx, dy)), scale(glm::vec2(sx, sy)), rotation(r) {}
		Transform2(float dx, float dy, float s, float r) :
			translation(glm::vec2(dx, dy)), scale(glm::vec2(s, s)), rotation(r) {}
		Transform2 operator+(const Transform2 & t) const;
		Transform2 operator*(const float f) const;
	};

	class Transform3 : public Transform {
	public:
		glm::vec3 translation;
		glm::vec3 scale;
		glm::quat rotation;
		glm::mat4 getMat() override;
		Transform3() : translation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {}
		Transform3(glm::vec3 t, glm::vec3 s, glm::quat r) : translation(t), scale(s), rotation(r) {}
		Transform3(float dx, float dy, float dz, float sx, float sy, float sz, float eueler_x, float euler_y, float euler_z) :
			translation(dx, dy, dz), scale(sx, sy, sz), rotation(glm::vec3(eueler_x, euler_y, euler_z)) {}
		Transform3 operator+(const Transform3 & t) const;
		Transform3 operator*(const float f) const;
	};

	// Methodes are in namespace std in c++17

	template <class T> 
	static const T & clamp(const T & v, const T & lo, const T & hi) {
		return clamp(v, lo, hi, std::less<>());
	}
	
	template <class T, class Compare> 
	static const T & clamp(const T & v, const T & lo, const T & hi, Compare comp) {
		return assert(!comp(hi, lo)),
			comp(v, lo) ? lo : comp(hi, v) ? hi : v;
	}
};

