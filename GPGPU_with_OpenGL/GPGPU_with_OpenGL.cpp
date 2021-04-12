
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "gtc/matrix_transform.hpp"
#include <ctime>

Shader* GPGPUShader = nullptr;

GLFWwindow* window;

int width = 1024;
int height = 512;

GLuint fb;

int N = 16;

float* cpu_data1 = new float[N];
float* cpu_data2 = new float[N];

float* result = new float[N];

GLuint screenQuadVao;

GLuint xtexID;
GLuint ytexID;
GLuint rtexID;

int texture_target = GL_TEXTURE_2D;

GLfloat texSize = std::sqrt(N) / 2;

int internal_format = GL_RGBA8;

int texture_format = GL_RGBA;

int data_format = GL_FLOAT;

void init() {

	glfwInit();

	window = glfwCreateWindow(width, height, "Opengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	GPGPUShader = new Shader("../../../../GPGPU_with_OpenGL/gpgpu.vert", "../../../../GPGPU_with_OpenGL/gpgpu.frag");

	srand((unsigned)time(0));

	//fill data with random values 
	for (int i = 0; i < N; i++) {
		cpu_data1[i] = ((float)rand() / (RAND_MAX * 2));

	}

	for (int i = 0; i < N; i++) {
		cpu_data2[i] = ((float)rand() / (RAND_MAX * 2));

	}
	
}


void initFBO() {
	// create FBO (off-screen framebuffer)
	glGenFramebuffersEXT(1, &fb);
	// bind offscreen buffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
		GL_COLOR_ATTACHMENT0_EXT,
		texture_target, rtexID, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
}

GLuint createTexture() {
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(texture_target, texID);
	// turn off filtering and set proper wrap mode
	// (obligatory for float textures atm)
	glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP);
	// set texenv to replace instead of the default modulate
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// and allocate graphics memory
	glTexImage2D(texture_target, 0, internal_format,
		texSize, texSize, 0, texture_format, data_format, 0);
	return texID;
}

void initTexture() {
	xtexID = createTexture();
	ytexID = createTexture();
	rtexID = createTexture();
}

void setupScreenQuad() {

	GLfloat screenQuadVertices[] =
	{//	x			y			u			v
		0.0,		0.0,		0.0,		0.0,
		 texSize,	0.0,		1.0,	0.0,
		 texSize,	texSize,	1.0,	1.0,
		0.0,		texSize,	0.0,		1.0
	};

	glGenVertexArrays(1, &screenQuadVao);
	glBindVertexArray(screenQuadVao);


	//vertex Attributes
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadVertices), screenQuadVertices, GL_DYNAMIC_DRAW);



	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(sizeof(GL_FLOAT) * 2));
	glEnableVertexAttribArray(1);
}


void render() {
	GPGPUShader->use();

	glm::mat4 proj = glm::ortho(0.0f, texSize, 0.0f, texSize);

	glm::vec4 test = proj * glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::vec4 test2 = proj * glm::vec4(texSize, texSize, 0.0, 1.0);

	GPGPUShader->setMat4("proj", proj);
	
	glViewport(0, 0, texSize, texSize); 

	//transfer data to gpu
	glBindTexture(texture_target, xtexID);
	glTexSubImage2D(texture_target, 0, 0, 0, texSize, texSize,
		texture_format, data_format, cpu_data1);

	glBindTexture(texture_target, ytexID);
	glTexSubImage2D(texture_target, 0, 0, 0, texSize, texSize,
		texture_format, data_format, cpu_data2);

	//setup shader stuff

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texture_target, xtexID);
	GPGPUShader->setInt("textureX", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(texture_target, ytexID);
	GPGPUShader->setIntARB("textureY", 1);

	//perform computation
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glBindVertexArray(screenQuadVao);

	glDrawArrays(GL_QUADS, 0, 4);


	//read back data and output result
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glReadPixels(0, 0, texSize, texSize, texture_format, data_format, result);

	std::cout << "INPUT" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << cpu_data1[i] << ", "; 
	}
	std::cout << std::endl;

	for (int i = 0; i < N; i++) {
		std::cout << cpu_data2[i] << ", ";
	}
	std::cout << std::endl;

	std::cout << "OUTPUT" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << result[i] << ", ";
	}
}

void cleanup() {
	delete(cpu_data1);
	delete(cpu_data2);
	delete(result);
	glDeleteFramebuffersEXT(1, &fb);
	glDeleteTextures(1, &xtexID);
	glDeleteTextures(1, &ytexID);
	glDeleteTextures(1, &rtexID);
}

int main()
{
	init();
	initTexture();
	initFBO();
	setupScreenQuad();
	render();
	cleanup();

	return 0;
}
