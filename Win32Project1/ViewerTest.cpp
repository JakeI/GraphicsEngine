#include "ViewerTest.h"

const std::string ViewerTest::resources[] = {
	"res/meshs/arrow2d.data",
	"res/meshs/quad.data",
	"res/shaders/uniformColor",
	"res/meshs/texture_quad.data",
	"res/textures/mona_lisa.png",
	"res/shaders/textured",
};
const int ViewerTest::resourceCount = sizeof(ViewerTest::resources) / sizeof(std::string);

ViewerTest::ViewerTest(Scene* parent) :
	Viewer2(parent),
	arrowPos(15),
	rotation(0.0f),
	angularSpeed(M_PI/3000.0f)
{
	for (int i = 0; i < 16; i++) {
		int x = i % 4;
		int y = i / 4;
		float fx = 1.5f*(float)x - 2.5f;
		float fy = 1.5f*(float)y - 2.5f;
		arrowPos.push_back(glm::vec2(fx, fy));
	}
}


ViewerTest::~ViewerTest() {
	resm->releaseResources(resources, resourceCount);
}

void ViewerTest::render(RenderMode rm) {
	Viewer2::render(rm);

	glViewport(dimention.x, dimention.y, dimention.w, dimention.h);
	glDisable(GL_DEPTH_TEST);

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

	glUseProgram(0);
}

void ViewerTest::init() {
	Viewer2::init();
	resm->prepareResources(resources, resourceCount);
}

void ViewerTest::increment(float time, float deltaTime) {
	Viewer2::increment(time, deltaTime);
	rotation += angularSpeed*deltaTime;
}