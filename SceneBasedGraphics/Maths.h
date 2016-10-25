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
		Transform2(const glm::vec2 & t, const glm::vec2 & s, const float r) : 
			translation(t), scale(s), rotation(r) {}
		Transform2(const glm::vec2 & t, const float uniScale, const float r) :
			translation(t), scale(uniScale, uniScale), rotation(r) {}
		Transform2(const float dx, const float dy, const float sx, const float sy, const float r) :
			translation(glm::vec2(dx, dy)), scale(glm::vec2(sx, sy)), rotation(r) {}
		Transform2(const float dx, const float dy, const float s, const float r) :
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
		Transform3() : translation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), 
			rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {}
		Transform3(glm::vec3 & t, glm::vec3 & s, glm::quat & r) : translation(t), scale(s), rotation(r) {}
		Transform3(const float dx, const float dy, const float dz, 
			const float sx, const float sy, const  float sz, 
			const float eueler_x, const float euler_y, const float euler_z) :
			translation(dx, dy, dz), scale(sx, sy, sz), rotation(glm::vec3(eueler_x, euler_y, euler_z)) {}
		Transform3 operator+(const Transform3 & t) const;
		Transform3 operator*(const float f) const;
	};

	template <typename T>
	class Box_t {
	public:
		Box_t() {}
		~Box_t() {}
	};

	typedef Box_t<int> Boxi;
	typedef Box_t<float> Boxf;
	typedef Boxf Box;

	template <typename T>
	class Box2_t : public Box_t<T> {
	public:
		T x_min, x_max;
		T y_min, y_max;
		Box2_t() : Box_t(), x_min(), y_min() { x_max = x_min + 1; y_max = y_min + 1; }
		Box2_t(T xMin, T xMax, T yMin, T yMax) :
			Box_t(), x_min(xMin), x_max(xMax), y_min(yMin), y_max(yMax) {}
	};

	typedef Box2_t<int> Box2i;
	typedef Box2_t<float> Box2f;
	typedef Box2f Box2;

	template <typename T>
	class Box3_t : public Box_t<T> {
	public:
		T x_min, x_max;
		T y_min, y_max;
		T z_min, z_max;
		Box3_t() : Box_t(), x_min(), y_min(), z_min() { x_max = x_min + 1; y_max = y_min + 1; z_max = z_min + 1 }
		Box3_t(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax) :
			Box_t(), x_miin(xMin), x_max(xMax), y_min(yMin), y_max(yMax), z_min(zMin), z_max(zMax) {}
	};

	typedef Box3_t<int> Box3i;
	typedef Box3_t<float> Box3f;
	typedef Box3f Box3;

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

