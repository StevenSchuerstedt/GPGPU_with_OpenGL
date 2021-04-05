// GPGPU_with_OpenGL.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "GPGPU_with_OpenGL.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;


GLFWwindow* window;

int width = 1024;
int height = 512;

void init() {

	glfwInit();

	window = glfwCreateWindow(width, height, "Opengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

}

void render() {

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


}

int main()
{

	init();
	render();


	cout << "Hello CMake." << endl;
	return 0;
}
