#include "TestScene.h"

const std::string TestScene::resources[] = {
	"res/meshs/arrow2d.data",
	"res/meshs/quad.data",
	"res/shaders/uniformColor",
	"res/meshs/texture_quad.data",
	"res/textures/mona_lisa.png",
	"res/shaders/textured",
	"res/meshs/cross.data",
};
const int TestScene::resourceCount = sizeof(TestScene::resources) / sizeof(std::string);

TestScene::TestScene(Scene* parent, const glm::vec4 & color, float rotation, float angular) : Scene(parent)
{
	this->color = color;
	this->rotation = rotation;
	this->angular = angular;
}


TestScene::~TestScene()
{
	resm->releaseResources(TestScene::resources, TestScene::resourceCount);
}

void TestScene::render(RenderMode rm) {
	Scene::render(rm);

	glViewport(dimention.x, dimention.y, dimention.w, dimention.h);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glDisable(GL_BLEND);

	Shader* shader = (Shader*)resm->getResource("res/shaders/uniformColor");
	Shader* texturedShader = (Shader*)resm->getResource("res/shaders/textured");
	Mesh* quad = (Mesh*)resm->getResource("res/meshs/quad.data");
	Mesh* texturedQuad = (Mesh*)resm->getResource("res/meshs/texture_quad.data");
	Mesh* arrow = (Mesh*)resm->getResource("res/meshs/arrow2d.data");
	Texture* mona = (Texture*)resm->getResource("res/textures/mona_lisa.png");

	// render background
	shader->use();
	shader->uniform("mvp", glm::mat4(1.0f));
	glm::vec4 c = color * (mouse.isInside ? 1.0f : 0.5f);
	shader->uniform("color", c);
	quad->render();
	
	// render 1x1 Quad
	texturedShader->use();
	glm::mat4 aspect = getProjection(STD2);
	shader->uniform("mvp", aspect);
	glBindTexture(GL_TEXTURE_2D, mona->tbo);
	texturedQuad->render();
	glBindTexture(GL_TEXTURE_2D, 0);

	// render arrow
	const float speed = 19.0f;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glm::mat4 mvp(1.0f);
	mvp = glm::rotate(mvp, (speed / 3.0f)*rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	mvp = aspect * mvp;
	shader->use();
	shader->uniform("mvp", mvp);
	shader->uniform("color", glm::vec4(0.3f, 0.3f, 0.8f, 0.8f));
	arrow->render();
	mvp = glm::mat4(1.0f);
	mvp = glm::rotate(mvp, (speed / 11.0f)*rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	mvp = aspect * mvp;
	shader->uniform("mvp", mvp);
	shader->uniform("color", glm::vec4(0.8f, 0.3f, 0.3f, 0.8f));
	arrow->render();
	mvp = glm::mat4(1.0f);
	mvp = glm::rotate(mvp, (speed / 7.0f)*rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	mvp = aspect * mvp;
	shader->uniform("mvp", mvp);
	shader->uniform("color", glm::vec4(0.3f, 0.8f, 0.3f, 0.8f));
	arrow->render();

	// render quad as mouse courser
	if (mouse.isInside) {
		glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
		mvp = glm::mat4(1.0f);
		mvp = glm::translate(mvp, glm::vec3(getMouseGl(), 0.0f));
		mvp = glm::scale(mvp, glm::vec3(0.1f, 0.1f, 1.0f));
		shader->uniform("mvp", mvp);
		shader->uniform("color", glm::vec4(0.75f, 0.5f, 0.25f, 1.0f));
		quad->render();
	}

	Mesh* mesh = (Mesh*)resm->getResource("res/meshs/cross.data");
	shader->use();
	shader->uniform("mvp", glm::translate(glm::mat4(1.0f), glm::vec3(-0.8f, 0.0f, 0.0f)));
	shader->uniform("color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	mesh->render();

	glDisable(GL_BLEND);
	glUseProgram(0);

	text.render();
}

void TestScene::init() {
	Scene::init();

	resm->prepareResources(TestScene::resources, TestScene::resourceCount);

	text.init();
}

void TestScene::increment(float time, float deltaTime) {
	Scene::increment(time, deltaTime);
	rotation += angular*deltaTime;
}

void TestScene::charDown(char c) {
	Scene::charDown(c);

	if (mouse.isInside) {

		switch (c) {
		case 0x08: // backspace
			text.remove(text.size() - 1);
			break;
		case 0x0A: // linefeed
			text << '\n';
			break;
		case 0x1B: // escape

			break;
		/*case 0x09: // tab

			break;*/
		case 0x0D: // carriage return
			text << '\n';
			break;
		default: // printable char
			text << (char)c;
			break;
		}
		text.pack();

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