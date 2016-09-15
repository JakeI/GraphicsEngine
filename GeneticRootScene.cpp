#include "GeneticRootScene.h"

const std::string GeneticRootScene::resources[] = {
	std::string("res/shaders/standard"),
	std::string("res/shaders/textured"),
	std::string("res/textures/mona_lisa.png"),
};
const int GeneticRootScene::resourcesCount = sizeof(GeneticRootScene::resources) / sizeof(std::string);

GeneticRootScene::GeneticRootScene() : RootScene()
{
	//setPreferedDimention(glm::ivec2(640, 480));
	
	constantLayout = new ConstantLayout();

	tsCenter = new TestScene(this, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), 0.0f, M_PI / 4000.0f);
	add(tsCenter);
	constantLayout->add(tsCenter, ConstantLayout::Info(ConstantLayout::Info::PlacementMode::TOP_LEFT, 160, 100));
	tsCenter->setLayer(1);

	horizontalLayout = new HorizontalLayout();
	constantLayout->add(horizontalLayout, ConstantLayout::Info(ConstantLayout::Info::PlacementMode::CENTER, 1.0f, 1.0f));

	verticalLayout = new VerticalLayout();
	horizontalLayout->add(verticalLayout, WeightedLayout::Info(200));

	tsRed = new TestScene(this, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		M_PI/3.0f, M_PI / 10240.0f);
	add(tsRed);
	verticalLayout->add(tsRed, WeightedLayout::Info(100));

	tsBlue = new TestScene(this, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		M_PI / 6.0f, -M_PI / 5120.0f);
	add(tsBlue);
	verticalLayout->add(tsBlue, WeightedLayout::Info(3.0f));

	vtMain = new ViewerTest(this);
	add(vtMain);
	horizontalLayout->add(vtMain, WeightedLayout::Info(4.0f));

	setLayoutPtr(constantLayout);

	arangeChildren();

	angle = 0;
}


GeneticRootScene::~GeneticRootScene()
{
	resm->releaseResources(resources, resourcesCount);

	delete tsRed;
	delete tsBlue;
	delete vtMain;
	delete tsCenter;
	delete horizontalLayout;
	delete verticalLayout;
	delete constantLayout;
}

void GeneticRootScene::render(RenderMode rm)
{
	
	InputState* is = getInputState();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	RootScene::render();

	if (is->mouse.isLdown()) {

		glViewport(0, 0, is->windowSize.w, is->windowSize.h);

		glEnable(GL_DEPTH_TEST);

		Shader* s = (Shader*)resm->getResource(std::string("res/shaders/textured"));
		s->use();
		Texture* t = (Texture*)resm->getResource(std::string("res/textures/mona_lisa.png"));

		glBindTexture(GL_TEXTURE_2D, t->tbo);

		glBindVertexArray(vao);

		glm::mat4 mvp(1.0f);
		mvp = glm::translate(mvp, glm::vec3(((float)is->mouse.x / (float)is->windowSize.w)*2.0f - 1.0f,
			((float)is->mouse.y / (float)is->windowSize.h)*2.0f - 1.0f, 0.0f));
		mvp = glm::scale(mvp, glm::vec3(0.05f, 0.05f, 0.05f));
		s->uniform("mvp", mvp);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(3);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(3);

		glBindVertexArray(0);

		glUseProgram(0);
	}
}

void GeneticRootScene::keyDown(char key) {
	switch (key) {
	case VK_ADD:
		angle += 5.0f;
		break;
	case VK_SUBTRACT:
		angle -= 5.0f;
		break;
	/*case 'A':
		verticalLayout->remove(tsBlue);
		updateLayout();
		break;
	case 'B':
		verticalLayout->add(tsBlue, WeightedLayout::Info());
		updateLayout();
		break;*/
	}
}

void GeneticRootScene::init() {
	Scene::init();

	resm->prepareResources(resources, resourcesCount);

	static const float quad[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f
	};
	vertexcount = sizeof(quad) / sizeof(float);

	static const float uvs[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(2, vbos);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0);
}

void GeneticRootScene::increment(float time, float deltaTime)
{
	RootScene::increment(time, deltaTime);

	static const float omega = 2 * M_PI / 1000.0f;
	static const float phi = 2 * M_PI / 2000.0f;
	trianglePos = 0.2f*cosf(phi*time)*glm::vec3(cosf(omega*time), sinf(omega*time), 0.0f);
}


