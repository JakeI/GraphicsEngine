#include "ViewerTest.h"

ViewerTest::ViewerTest(Scene* parent) :
	Viewer2(parent),
	background("res/models/quad.mdl"),
	arrow("res/models/arrow2D.mdl"),
	arrow_m("res/models/arrow2D.mdl"),
	text(),
	logWasLoaded(false),
	p1(), p2(), constants(1.0, 1.6, 1.0, 0.5, 0.3),
	currentState(0.0, 0.0, 0.0, 0.0, 0.0, M_PI/2.0)
{
	background.color.getAnimator()->setValue(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	background.entity.add(&background.color);
	background.transform.getAnimator()->setValue(Maths::Transform2());
	background.entity.add(&background.transform);

	arrow.color.getAnimator()->set(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f), glm::vec4(0.5f, 0.5f, 0.5f, 0.7f));
	arrow.color.getAnimator()->setLength(1000.0f);
	arrow.color.getAnimator()->setClampFunc(ClampFuncs::circular);
	arrow.entity.add(&arrow.color);
	arrow.transform.getAnimator()->setValue(Maths::Transform2());
	arrow.entity.add(&arrow.transform);

	arrow_m.color.getAnimator()->setValue(glm::vec4(0.5f, 0.0f, 0.0f, 0.5f));
	arrow_m.entity.add(&arrow_m.color);
	arrow_m.transform.getAnimator()->set(Maths::Transform2(-1.0f, -1.0f, 0.5f, 1.0f, (float)M_PI/2.0f), 
		Maths::Transform2(0.0f, 1.0f, 2.0f, 1.0f, 0.0f));
	arrow_m.transform.getAnimator()->setLength(10000.0f);
	arrow_m.transform.getAnimator()->setClampFunc(ClampFuncs::circular);
	arrow_m.transform.getAnimator()->setInterpolation(InterpolationFuncs::cosine);
	arrow_m.entity.add(&arrow_m.transform);

	text.transform.getAnimator()->setValue(Maths::Transform2());
	text.text.add(&text.transform);

	p1.color.getAnimator()->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	p2.color.getAnimator()->setValue(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	a1.setColor(glm::vec4(1.0f, 1.0f, 0.0f, 0.5f));
	a2.setColor(glm::vec4(1.0f, 0.0f, 1.0f, 0.5f));
}


ViewerTest::~ViewerTest() {
	//resm->releaseResources(resources, resourceCount);
}

void ViewerTest::render(RenderMode rm) {
	Viewer2::render(rm);

	if (!logWasLoaded) {
		text.text << resm->to_string();
		logWasLoaded = true;
	}

	glViewport(dimention.x, dimention.y, dimention.w, dimention.h);

	glDisable(GL_DEPTH_TEST);
	
	Maths::ProjView pv;
	
	background.entity.render(&pv, UNIFORM);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pv.proj = getProjection(STD2);
	pv.view = camera.getView();
	pv.update();
	arrow.entity.render(&pv, FULL);
	arrow_m.entity.render(&pv, FULL);
	
	p1.entity.render(&pv, FULL);
	p2.entity.render(&pv, FULL);

	a1.render(&pv, FULL);
	a2.render(&pv, FULL);

	glDisable(GL_BLEND);

	text.text.render(&pv, FULL);

	

	/*glDisable(GL_DEPTH_TEST);

	//Get Resources
	Shader* uni = (Shader*)resm->getResource("res/shaders/uniformColor");
	Shader* tex = (Shader*)resm->getResource("res/shaders/textured");

	Mesh* quad = (Mesh*)resm->getResource("res/meshs/quad.data");
	Mesh* arrow = (Mesh*)resm->getResource("res/meshs/arrow2d.data");
	Mesh* texquad = (Mesh*)resm->getResource("res/meshs/texture_quad.data");

	Texture* mona = (Texture*)resm->getResource("res/textures/mona_lisa.png");

	//Draw Background
	uni->use();
	uni->uniform("mvp", glm::mat4(1.0f));
	uni->uniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	quad->render();

	//get Matrix
	glm::mat4 projection = getProjection(STD2);
	glm::mat4 view = camera.getView();
	glm::mat4 projView = projection * view;

	//render Mona
	tex->use();
	tex->uniform("mvp", projView*glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f)));
	mona->bind(GL_TEXTURE_2D);
	texquad->render();
	glBindTexture(GL_TEXTURE_2D, 0);

	//render Arrows
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	uni->use();
	uni->uniform("color", glm::vec4(0.0f, 0.0f, 1.0f, 0.7f));
	for (auto p : arrowPos) {
		glm::mat4 m(1.0f);
		m = glm::rotate(m, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		m = glm::translate(m, glm::vec3(p.x, p.y, 0.0f));
		m = glm::scale(m, glm::vec3(0.25f, 0.25f, 1.0f));
		m = glm::rotate(m, -rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		uni->uniform("mvp", projView*m);
		arrow->render();
	}

	glUseProgram(0);*/
}

void ViewerTest::init() {
	Viewer2::init();

	background.entity.init();
	arrow.entity.init();
	arrow_m.entity.init();
	text.text.init();
	
	p1.entity.init();
	p2.entity.init();
	a1.init();
	a2.init();
	//resm->prepareResources(resources, resourceCount);
}

void ViewerTest::increment(float time, float deltaTime) {
	Viewer2::increment(time, deltaTime);

	incrementPendulums(deltaTime);

	background.entity.increment(time, deltaTime);
	arrow.entity.increment(time, deltaTime);
	arrow_m.entity.increment(time, deltaTime);
	text.text.increment(time, deltaTime);
	
	p1.entity.increment(time, deltaTime);
	p2.entity.increment(time, deltaTime);
	a1.increment(time, deltaTime);
	a2.increment(time, deltaTime);
	//rotation += angularSpeed*deltaTime;
}

void ViewerTest::incrementPendulums(double deltaTime) {
	State nextState;

	double dt = deltaTime;
	dt = dt > 20.0 ? 20.0 : dt;
	dt = dt < 1.0 ? 1.0 : dt;
	dt = dt / 100.0;

	const int numSteps = 1000;

	double fraq = dt / numSteps;

	for (double delta = 0.0; delta <= dt; delta += fraq) {
		nextState.dda = ddAlpha(&currentState);
		nextState.ddb = ddBeta(&currentState);
		nextState.da = nextState.dda*fraq + currentState.da;
		nextState.db = nextState.ddb*fraq + currentState.db;
		nextState.a = nextState.da*fraq + currentState.a;
		nextState.b = nextState.db*fraq + currentState.b;

		currentState = nextState;
	}

	updateTransforms(&currentState);
}

double ViewerTest::ddAlpha(State* s) {
	return (constants.n*constants.l*s->da*s->db*sin(s->a-s->b) +
			(constants.m+constants.n)*constants.g*cos(s->a) + 
			constants.n*constants.l*(s->ddb*cos(s->a-s->b)-s->db*sin(s->a-s->b)*(s->da-s->db))
		) / (-1.0*(constants.m+constants.n)*constants.k);
}

double ViewerTest::ddBeta(State* s) {
	return (constants.n*constants.k*s->da*s->db*sin(s->a-s->b) -
			constants.n*constants.g*cos(s->b) -
			constants.n*constants.k*(s->dda*cos(s->a-s->b)-s->da*sin(s->a-s->b)*(s->da-s->db))
		) / (constants.n*constants.l);
}

void ViewerTest::updateTransforms(State* state) {
	const float dx = 2.0f, dy = 2.0f; // general translation
	const float sx = 1.0f, sy = -1.0f; // general scale
	
	glm::vec2 start1(dx, dy);
	glm::vec2 start2(start1.x + constants.k*cosf(state->a), start1.y + constants.k*sinf(state->a)); // == end1

	p1.transform.getAnimator()->setValue(Maths::Transform2(
		start1, glm::vec2(sx*constants.k, sy*constants.k), state->a));
	p2.transform.getAnimator()->setValue(Maths::Transform2(
		start2, glm::vec2(sx*constants.l, sy*constants.l), state->b));

	glm::vec2 end2(start2.x + constants.l*cosf(state->b), start2.y + constants.l*sinf(state->b));

	glm::vec2 v1 = ((float)(constants.k*state->da))*glm::vec2(-sinf(state->a), cosf(state->b));
	glm::vec2 v2 = v1 + ((float)(constants.l*(float)state->db))*glm::vec2(-sinf(state->b), cosf(state->b));
	a1.setByCenter(start2, 0.5f*v1);
	a2.setByCenter(end2, 0.5f*v2);
}

void ViewerTest::mouseLdown(int x, int y) {
	if (mouse.isInside)
		currentState = State(0.0, 0.0, 0.0, 0.0, 0.0, M_PI / 2.0);
}

void ViewerTest::charDown(char c) {
	Viewer2::charDown(c);

	if (mouse.isInside) {

		switch (c) {
		case 0x08: // backspace
			text.text.remove(text.text.size() - 1);
			break;
		case 0x0A: // linefeed
			text.text << '\n';
			break;
		case 0x1B: // escape

			break;
		// case 0x09: break; // tab
		case 0x0D: // carriage return
			text.text << '\n';
			break;
		default: // printable char
			text.text << (char)c;
			break;
		}
		text.text.pack();

		/*if (c == '\b' || c == VK_DELETE) {
		text.remove(text.size() - 1);
		text.pack();
		} else if (c == '\r') {
		text << '\n';
		} else if (c == VK_SPACE) {
		text << ' ';
		} else if (c == VK_TAB) {
		text << '\t';
		} else if (c >= 0 && c <= 256 && std::isalnum(c)) {
		if (getInputState()->keyboard.get(VK_SHIFT))
		text << (char)std::toupper(c);
		else
		text << (char)std::tolower(c);
		text.pack();
		}*/
	}
}