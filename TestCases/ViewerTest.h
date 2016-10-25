#pragma once
#include "Viewer2.h"
#include "ResourceManager.h"
#include "ModelEntity.h"
#include "Text.h"
#include "Arrow.h"

class ViewerTest : public Viewer2
{
private:

	struct ConstModelEntity {
		ConstColorComp color;
		ConstTransform2Comp transform;
		ModelEntity entity;
		ConstModelEntity(const std::string & path) : entity(path) {}
	} background;

	struct PairColorModdelEntity {
		PairColorComp color;
		ConstTransform2Comp transform;
		ModelEntity entity;
		PairColorModdelEntity(const std::string & path) : entity(path) {}
	} arrow;

	struct PairTransformedModelEntity {
		ConstColorComp color;
		PairTransform2Comp transform;
		ModelEntity entity;
		PairTransformedModelEntity(const std::string & path) : entity(path) {}
	} arrow_m;

	struct ConstTextEntity {
		ConstTransform2Comp transform;
		Text text;
	} text;

	bool logWasLoaded;

public:
	ViewerTest(Scene* parent);
	~ViewerTest();

	void increment(float time, float deltaTime) override;
	void render(RenderMode rm) override;
	void init() override;

	void charDown(char c) override;
	void mouseLdown(int x, int y) override;


// stuff for the double pendulum
private:

	struct PendulumEntity {
		ConstTransform2Comp transform;
		ConstColorComp color;
		ModelEntity entity;
		PendulumEntity() : entity("res/models/pendulum.mdl") {
			entity.add(&transform);
			entity.add(&color);
		}
	} p1, p2;

	Arrow2ConstColor a1, a2;

	struct Constants {
		double k, l; // lenth of pendulum 1, pandulum 2
		double m, n; // mass of pendulum 1, pendulum 2
		double g; // gravity
		Constants(double k, double l, double m, double n, double g) : 
			k(k), l(l), m(m), n(n), g(g) {}
	} constants;

	struct State {
		double dda, da, a; // angle of pendulum 1 and it's diffs
		double ddb, db, b; // angle off pendulum 2 and it's diffs
		State(State* s) : dda(s->dda), da(s->da), a(s->a), ddb(s->ddb), db(s->db), b(s->b) {}
		State(double dda, double da, double a, double ddb, double db, double b) :
			dda(dda), da(da), a(a), ddb(ddb), db(db), b(b) {}
		State() : dda(0.0), da(0.0), a(0.0), ddb(0.0), db(0.0), b(0.0) {}
	}currentState;

	void incrementPendulums(double deltaTime);
	void updateTransforms(State* state);
	double ddAlpha(State* s);
	double ddBeta(State* s);


};

