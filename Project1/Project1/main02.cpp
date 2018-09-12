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


//���_�V�F�[�_
const char g_vertex_shader[]=
{
	"#version 330 core                                          \n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;    \n"
	"                                                           \n"
	"void main()                                                \n"
	"{															\n"
	"	gl_Position.xyz = vertexPosition_modelspace;			\n"
	"	gl_Position.w = 1.0;									\n"
	"}															\n"
};

//�t���O�����g�V�F�[�_�i�s�N�Z���V�F�[�_�j
const char g_fragment_shader[]=
{															 
	"#version 330 core											\n"
	"															\n"
	"out vec3 color;											\n"
	"															\n"
	"void main()												\n"
	"{															\n"
	"	color = vec3(0,0,1);									\n"
	"}															\n"
};

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
		1.0f,-1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,

		-1.0f,-1.0f, 0.0f,
		-1.0f,1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	GLuint vertexbuffer;	//���_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &vertexbuffer);//�������̗v�f���̔z����쐬
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// GLSL�v���O�������V�F�[�_����쐬�A�R���p�C��
	GLuint ProgramID		= glCreateProgram();//�V�F�[�_�v���O����
	GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER  );
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	//���_�V�F�[�_�R���p�C��
	char const* v = g_vertex_shader;
	glShaderSource(VertexShaderID, 1,&v, NULL);
	glCompileShader(VertexShaderID);

	//�t���O�����g�V�F�[�_�R���p�C��
	char const* f = g_fragment_shader;
	glShaderSource(FragmentShaderID, 1,&f, NULL);
	glCompileShader(FragmentShaderID);

	//���_�ƃt���O�����g�V�F�[�_���v���O�����Ƀ����N����
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	//�v���O�����ɂ����̂ŃV�F�[�_�͔j��
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	do
	{
		//�w�i�F�̐ݒ�
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// �V�F�[�_���g��
		glUseProgram(ProgramID);

		//���_���C�A�E�g�̃����o�̗L���ݒ�
		glEnableVertexAttribArray(0);	//0�F�@���_

		//�]�����钸�_�o�b�t�@�w��
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//�]������o�b�t�@�̃����o�̐��ƌ^��ݒ肵0�ԂƂ��đ���
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// �O�p�`��`��
		glDrawArrays(GL_TRIANGLES, 0, 6); // 0����n�܂�3�̒��_�@���@1�̎O�p�`

		

										 
		glDisableVertexAttribArray(0);		 //���_���C�A�E�g�̃����o�̖����ݒ�



		// �o�b�t�@����������
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ESC�L�[�������ꂽ���A�E�B���h�E������ꂽ�����m�F����
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// VBO��Еt����
	glDeleteBuffers(1, &vertexbuffer);		//�o�b�t�@�j��
	glDeleteVertexArrays(1, &VertexArrayID);//���C�A�E�g���j��
	glDeleteProgram(ProgramID);

	glfwTerminate();// OpenGL�E�B���h�E����AGLFW���I������

	return;

}