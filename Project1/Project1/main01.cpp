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
		return;
	}
	glfwMakeContextCurrent(window);

	// �R�A�v���t�@�C���ŕK�v
	glewExperimental = true; 

	// GLEW��������
	if (glewInit() != GLEW_OK)
	{
		return;
	}

	// �G�X�P�[�v�L�[�̉����̊m�F��ۏ�
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//���_���C�A�E�g�쐬
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);//���������̗v�f���̒��_���C�A�E�g�z����쐬
	glBindVertexArray(VertexArrayID);	 //VertexArrayID�̃��C�A�E�g�����o���쐬


	//glBindVertexArray(0);				//VertexArrayID���C�A�E�g�����o�쐬����
	

	//���_���𒸓_�o�b�t�@������
	static const GLfloat g_vertex_buffer_data[] = 
	{
		1.0f,1.0f, 0.0f,
		-1.0f,1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};

	GLuint vertexbuffer;	//���_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &vertexbuffer);//�������̗v�f���̔z����쐬
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);


	do
	{
		//�w�i�F�̐ݒ�
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//���_���C�A�E�g�̃����o�̗L���ݒ�
		glEnableVertexAttribArray(0);	//0�F�@���_

		//�]�����钸�_�o�b�t�@�w��
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//�]������o�b�t�@�̃����o�̐��ƌ^��ݒ肵0�ԂƂ��đ���
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		// �O�p�`��`��
		glDrawArrays(GL_TRIANGLES, 0, 3); // 0����n�܂�3�̒��_�@���@1�̎O�p�`


		//���_���C�A�E�g�̃����o�̖����ݒ�
		glDisableVertexAttribArray(0);



		// �o�b�t�@����������
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ESC�L�[�������ꂽ���A�E�B���h�E������ꂽ�����m�F����
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// VBO��Еt����
	glDeleteBuffers(1, &vertexbuffer);		//�o�b�t�@�j��
	glDeleteVertexArrays(1, &VertexArrayID);//���C�A�E�g���j��
	

	// OpenGL�E�B���h�E����AGLFW���I������
	glfwTerminate();

	return;

}