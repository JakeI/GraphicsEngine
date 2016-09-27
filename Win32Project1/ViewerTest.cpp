#include "ViewerTest.h"

/*const std::string ViewerTest::resources[] = {
	//"res/meshs/arrow2d.data",
	//"res/meshs/quad.data",
	"res/shaders/uniformColor",
	//"res/meshs/texture_quad.data",
	//"res/textures/mona_lisa.png",
	//"res/shaders/textured",
};
const int ViewerTest::resourceCount = sizeof(ViewerTest::resources) / sizeof(std::string);*/

ViewerTest::ViewerTest(Scene* parent) :
	Viewer2(parent),
	background("res/models/quad.mdl"),
	arrow("res/models/arrow2D.mdl"),
	arrow_m("res/models/arrow2D.mdl"),
	text()
	//arrowPos(15),
	//rotation(0.0f),
	//angularSpeed(M_PI/3000.0f)
{
	background.color.getAnimator()->setValue(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	background.entity.add(&background.color);
	background.transform.getAnimator()->setValue(Maths::Transform2());
	background.entity.add(&background.transform);

	arrow.color.getAnimator()->setValue(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f));
	arrow.entity.add(&arrow.color);
	arrow.transform.getAnimator()->setValue(Maths::Transform2());
	arrow.entity.add(&arrow.transform);

	arrow_m.color.getAnimator()->setValue(glm::vec4(0.5f, 0.0f, 0.0f, 0.5f));
	arrow_m.entity.add(&arrow_m.color);
	arrow_m.transform.getAnimator()->set(Maths::Transform2(-1.0f, -1.0f, 0.5f, 1.0f, (float)M_PI/2.0f), Maths::Transform2(0.0f, 1.0f, 2.0f, 1.0f, 0.0f));
	arrow_m.transform.getAnimator()->setLength(10000.0f);
	arrow_m.transform.getAnimator()->setClampFunc(ClampFuncs::circular);
	arrow_m.transform.getAnimator()->setInterpolation(InterpolationFuncs::cosine);
	arrow_m.entity.add(&arrow_m.transform);

	text.transform.getAnimator()->setValue(Maths::Transform2());
	text.text.add(&text.transform);
	text.text << std::string("Hallo");

	/*for (int i = 0; i < 16; i++) {
		int x = i % 4;
		int y = i / 4;
		float fx = 1.5f*(float)x - 2.5f;
		float fy = 1.5f*(float)y - 2.5f;
		arrowPos.push_back(glm::vec2(fx, fy));
	}*/
}


ViewerTest::~ViewerTest() {
	//resm->releaseResources(resources, resourceCount);
}

void ViewerTest::render(RenderMode rm) {
	Viewer2::render(rm);

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
	//resm->prepareResources(resources, resourceCount);
}

void ViewerTest::increment(float time, float deltaTime) {
	Viewer2::increment(time, deltaTime);

	background.entity.increment(time, deltaTime);
	arrow.entity.increment(time, deltaTime);
	arrow_m.entity.increment(time, deltaTime);
	text.text.increment(time, deltaTime);
	//rotation += angularSpeed*deltaTime;
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