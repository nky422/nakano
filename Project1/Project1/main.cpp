#include "include\GL\glew.h"
#include "include\GLFW\glfw3.h"
#include "glm\glm.hpp"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment (lib,"lib/Release/Win32/glew32.lib")
#pragma comment (lib,"lib/Release/Win32/glew32s.lib")
#pragma comment (lib,"lib-vc2015/glfw3.lib")
#pragma comment (lib,"lib-vc2015/glfw3dll.lib")

GLFWwindow* window;
using namespace glm;

void main()
{
	// GLFW��������
	if (!glfwInit())
	{
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// �E�B���h�E���J���AOpenGL�R���e�L�X�g�����
	window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
	if (window == NULL)
	{
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
	
	// GLEW��������
	if (glewInit() != GLEW_OK) 
	{
		return ;
	}
	
	// �G�X�P�[�v�L�[�̉����̊m�F��ۏ�
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	

	do 
	{
		// �_�[�N�u���[�̔w�i
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// �o�b�t�@����������
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ESC�L�[�������ꂽ���A�E�B���h�E������ꂽ�����m�F����
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// OpenGL�E�B���h�E����AGLFW���I������
	glfwTerminate();

	return;
	
}