#include "include\GL\glew.h"
#include "include\GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp" 

#pragma comment(lib, "OpenGL32.lib")
#pragma comment (lib,"lib/Release/Win32/glew32.lib")
#pragma comment (lib,"lib/Release/Win32/glew32s.lib")
#pragma comment (lib,"lib-vc2015/glfw3.lib")
#pragma comment (lib,"lib-vc2015/glfw3dll.lib")

GLFWwindow* window;
using namespace glm;


//���_�o�b�t�@�i�ʒu�j
static const GLfloat g_vertex_buffer_data[8][3] =
{
	{-1.0f, 1.0f, 1.0f},
	{-1.0f,-1.0f, 1.0f},
	{ 1.0f, 1.0f, 1.0f},
	{ 1.0f,-1.0f, 1.0f},
	{ 1.0f, 1.0f,-1.0f},
	{ 1.0f,-1.0f,-1.0f},
	{-1.0f, 1.0f,-1.0f},
	{-1.0f,-1.0f,-1.0f},
};

//�C���f�b�N�X�o�b�t�@
static const GLint g_index_buffer_data[12][3] =
{
	{2,3,1},
	{2,1,0},
	{4,5,3},
	{4,3,2},
	{6,7,5},
	{6,5,4},
	{0,1,7},
	{0,7,6},
	{4,2,0},
	{4,0,6},
	{3,5,7},
	{3,7,1},
};

//�s��
glm::mat4 mat_world;		//���[���h�ϊ��s��
glm::mat4 mat_view;			//�r���[�ϊ��s��
glm::mat4 mat_projection;	//�ˉe�ϊ��s��
glm::mat4 mat_wvp;			//���[���h�E�r���[�E�ˉe�����s��

//�V�F�[�_�v���O�����I�u�W�F�N�g
GLuint g_ProgramID;

//�o�b�t�@�I�u�W�F�N�g
GLuint g_vertexbuffer;		//���_�o�b�t�@�I�u�W�F�N�g
GLuint g_indexbuffer;		//�C���f�b�N�X�o�b�t�@�I�u�W�F�N�g

//���_�V�F�[�_
const char g_vertex_shader[] =
{
	"#version 330 core											\n"
	"layout(location = 0) in vec3 pos;							\n"
	"uniform mat4 MVP;											\n"
	"void main()												\n"
	"{															\n"
	"	gl_Position =MVP * vec4(pos,1);							\n"
	"}															\n"
};

//�t���O�����g�V�F�[�_�i�s�N�Z���V�F�[�_�j
const char g_fragment_shader[] =
{
	"#version 330 core											\n"
	"															\n"
	"out vec3 color;											\n"
	"															\n"
	"void main()												\n"
	"{															\n"
	"	color = vec3(1,0,0);									\n"
	"}															\n"
};

void main()
{
	// GLFW��������
	if (!glfwInit())
		return;

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
		return;

	// �G�X�P�[�v�L�[�̉����̊m�F��ۏ�
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//���_���C�A�E�g�쐬
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);//���������̗v�f���̒��_���C�A�E�g�z����쐬
	glBindVertexArray(VertexArrayID);	 //VertexArrayID�̃��C�A�E�g�����o���쐬



	//���f���o�b�t�@�I�u�W�F�N�g�쐬---------
	//���_�o�b�t�@�I�u�W�F�N�g�쐬
	glGenBuffers(1, &g_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//�C���f�b�N�X�I�u�W�F�N�g�쐬
	glGenBuffers(1, &g_indexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_indexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_index_buffer_data), g_index_buffer_data, GL_STATIC_DRAW);
	//----------------------------------------

	//GLSL�v���O�����I�u�W�F�N�g�쐬----------
	// GLSL�v���O�������V�F�[�_����쐬�A�R���p�C��
	g_ProgramID = glCreateProgram();//�V�F�[�_�v���O����
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//���_�V�F�[�_�R���p�C��
	char const* v = g_vertex_shader;
	glShaderSource(VertexShaderID, 1, &v, NULL);
	glCompileShader(VertexShaderID);

	//�t���O�����g�V�F�[�_�R���p�C��
	char const* f = g_fragment_shader;
	glShaderSource(FragmentShaderID, 1, &f, NULL);
	glCompileShader(FragmentShaderID);

	//���_�ƃt���O�����g�V�F�[�_���v���O�����Ƀ����N����
	glAttachShader(g_ProgramID, VertexShaderID);
	glAttachShader(g_ProgramID, FragmentShaderID);
	glLinkProgram(g_ProgramID);

	//�v���O�����ɂ����̂ŃV�F�[�_�͔j��
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	// "MVP" uniform�̃n���h�����擾
	GLuint MatrixID = glGetUniformLocation(g_ProgramID, "MVP");
	//-----------------------------------------

	do
	{
		//�e�s��̌v�Z

		//�P�ʍs��
		mat_world = glm::mat4(1.0f);
		mat_view = glm::mat4(1.0f);
		mat_projection = glm::mat4(1.0f);
		mat_wvp = glm::mat4(1.0f);

		//�J�����s��쐬
		static float f = 0.0f;
		f += 0.001f;
		glm::vec3 c_pos(cos(f)*3.0f, 2.0f, sin(f)*3.0f);
		glm::vec3 c_tar(0.0f, 0.0f, 0.0f);
		glm::vec3 c_vec(0.0f, 1.0f, 0.0f);
		mat_view = glm::lookAt(c_pos, c_tar, c_vec);

		//�p�[�X�e�N�e�B�u�s��쐬
		mat_projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.01f, 100.0f);

		//�v�u�o�s��쐬
		mat_wvp = mat_projection *mat_view * mat_world;


		// �V�F�[�_���g��
		glUseProgram(g_ProgramID);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mat_wvp[0][0]);

		//�w�i�F�̐ݒ�
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		//���_���C�A�E�g�̃����o�̗L���ݒ�
		glEnableVertexAttribArray(0);	//0�F�@���_

		//�]�����钸�_�o�b�t�@�w��
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER        , g_vertexbuffer);
		//�]������o�b�t�@�̃����o�̐��ƌ^��ݒ肵0�ԂƂ��đ���
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// �O�p�`��`��
		//glDrawArrays(GL_TRIANGLES, 0, 12); 
		glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);


		glDisableVertexAttribArray(0);
		


		// �o�b�t�@����������
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ESC�L�[�������ꂽ���A�E�B���h�E������ꂽ�����m�F����
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	//�j��
	glDeleteBuffers(1, &g_vertexbuffer);	//���_�o�b�t�@�j��
	glDeleteBuffers(1, &g_indexbuffer);		//�C���f�b�N�X�o�b�t�@�j��
	glDeleteVertexArrays(1, &VertexArrayID);//���C�A�E�g���j��
	glDeleteProgram(g_ProgramID);

	glfwTerminate();// OpenGL�E�B���h�E����AGLFW���I������

	return;

}