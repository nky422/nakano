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
static const GLfloat g_vertex_pos_buffer_data[8][3] =
{
	{ -1.0f, 1.0f, 1.0f },
	{ -1.0f,-1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f,-1.0f, 1.0f },
	{ 1.0f, 1.0f,-1.0f },
	{ 1.0f,-1.0f,-1.0f },
	{ -1.0f, 1.0f,-1.0f },
	{ -1.0f,-1.0f,-1.0f },
};

//���_�o�b�t�@(UV�j
static const GLfloat g_vertex_uv_buffer_data[8][2] =
{
	{ 1.00000f, 1.00000f },
	{ 1.00000f, 0.00000f },
	{ 0.00000f, 1.00000f },
	{ 0.00000f, 0.00000f },
	{ 1.00000f, 1.00000f },
	{ 1.00000f, 0.00000f },
	{ 0.00000f, 1.00000f },
	{ 0.00000f, 0.00000f },
};

//���_�o�b�t�@�i�J���[�j
static const GLfloat g_vertex_collar_buffer_data[8][4] =
{
	{ 0.0f, 0.0f, 1.0f ,1.0f },
	{ 0.0f, 1.0f, 0.0f ,1.0f },
	{ 1.0f, 0.0f, 0.0f ,1.0f },
	{ 0.0f, 1.0f, 1.0f ,1.0f },
	{ 1.0f, 0.0f, 1.0f ,1.0f },
	{ 0.0f, 0.0f, 0.5f ,1.0f },
	{ 0.5f, 0.0f, 0.0f ,1.0f },
	{ 0.0f, 0.5f, 0.0f ,1.0f },
};

//�C���f�b�N�X�o�b�t�@
static const GLint g_index_buffer_data[12][3] =
{
	{ 2,3,1 },
	{ 2,1,0 },
	{ 4,5,3 },
	{ 4,3,2 },
	{ 6,7,5 },
	{ 6,5,4 },
	{ 0,1,7 },
	{ 0,7,6 },
	{ 4,2,0 },
	{ 4,0,6 },
	{ 3,5,7 },
	{ 3,7,1 },
};

//�e�N�X�`���f�[�^(�e�X�g�p)
static const GLbyte g_texture_data[4*4*3]=
{
	  0x00,0x00,0x00 , 0xFF,0xFF,0xFF , 0x00,0x00,0x00 , 0xFF,0xFF,0xFF ,
	  0xFF,0xFF,0xFF , 0x00,0x00,0x00 , 0xFF,0xFF,0xFF , 0x00,0x00,0x00 ,
	  0x00,0x00,0x00 , 0xFF,0xFF,0xFF , 0x00,0x00,0x00 , 0xFF,0xFF,0xFF ,
	  0xFF,0xFF,0xFF , 0x00,0x00,0x00 , 0xFF,0xFF,0xFF , 0x00,0x00,0x00 ,
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
GLuint g_colorbuffer;		//�J���[�o�b�t�@�I�u�W�F�N�g
GLuint g_uvbuffer;			//UV�o�b�t�@�I�u�W�F�N�g
GLuint g_indexbuffer;		//�C���f�b�N�X�o�b�t�@�I�u�W�F�N�g




//���_�V�F�[�_
const char g_vertex_shader[] =
{
	//�V�F�[�_�̃o�[�W����
	"#version 330 core								\n"
	//CPU����A������钸�_���Q
	"layout(location = 0) in vec3 pos;				\n"
	"layout(location = 1) in vec4 col;				\n"
	"layout(location = 2) in vec2 uv;				\n"

	//�t���O�����g�V�F�[�_�ɑ�����Q
	"out vec4 fragmentColor;						\n"
	"out vec2 fragmentUv;							\n"

	//�R���X�^���g�O���[�o�����
	"uniform mat4 MVP;								\n"

	"void main()									\n"
	"{												\n"
	"	gl_Position =MVP * vec4(pos,1);				\n"//���X�^���C�Y�p���_�ʒu
	"	fragmentColor=col;							\n"
	"	fragmentUv   =uv;							\n"
	"}												\n"
};

//�t���O�����g�V�F�[�_�i�s�N�Z���V�F�[�_�j
const char g_fragment_shader[] =
{
	"#version 330 core										\n"
	"in  vec4 fragmentColor;								\n"
	"in  vec2 fragmentUv;									\n"
	"out vec4 color;										\n"
	"														\n"
	"uniform sampler2D Tex01;								\n"
	"														\n"
	"void main()											\n"
	"{														\n"
	"	color =fragmentColor;								\n"
	"	color*=vec4(texture2D(Tex01, fragmentUv ).rgb,1);	\n"
	"}														\n"
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

	//���_���C�A�E�g�I�u�W�F�N�g�쐬
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);//���_���C�A�E�g�I�u�W�F�N�g���쐬
	glBindVertexArray(VertexArrayID);	 //�ݒ肷��



	//���f���o�b�t�@�I�u�W�F�N�g�쐬---------
	//���_�o�b�t�@�I�u�W�F�N�g�쐬
	glGenBuffers(1, &g_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_pos_buffer_data), g_vertex_pos_buffer_data, GL_STATIC_DRAW);

	//�J���[�o�b�t�@�I�u�W�F�N�g�쐬
	glGenBuffers(1, &g_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_collar_buffer_data), g_vertex_collar_buffer_data, GL_STATIC_DRAW);

	//UV�o�b�t�@�I�u�W�F�N�g�쐬
	glGenBuffers(1, &g_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_uv_buffer_data), g_vertex_uv_buffer_data, GL_STATIC_DRAW);

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
	
	// "Tex01"uniform�n���h�����擾
	GLuint TextureID = glGetUniformLocation(g_ProgramID, "Tex01");
	glUniform1i(TextureID, 0);	//TextureID��GL_TEXTURE0�ɃZ�b�g
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, g_texture_data);

	//�@�T���v���Z�b�g
	GLuint sampler;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//-----------------------------------------

	//���s���e�X�g�̗L����
	glEnable(GL_DEPTH_TEST);
	
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

		//�e�N�X�`�����g��
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		

		glBindSampler(0, sampler);

		//�w�i�F�̐ݒ�
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		//layout(location = 0)�ɒ��_�𑗂�
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, g_vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//layout(location = 1)�ɃJ���[�𑗂�
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, g_colorbuffer);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//layout(location = 2)��UV�𑗂�
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, g_uvbuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// �C���f�b�N�X�o�b�t�@�����ɎO�p�`��`��
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indexbuffer);
		glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);


		glDisableVertexAttribArray(0);
		// �o�b�t�@����������
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ESC�L�[�������ꂽ���A�E�B���h�E������ꂽ�����m�F����
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	//�j��
	glDeleteBuffers(1, &g_vertexbuffer);	//���_�o�b�t�@�I�u�W�F�N�g�j��
	glDeleteBuffers(1, &g_colorbuffer);		//�J���[�o�b�t�@�I�u�W�F�N�g�j��
	glDeleteBuffers(1, &g_indexbuffer);		//�C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�j��
	glDeleteVertexArrays(1, &VertexArrayID);//���C�A�E�g�I�u�W�F�N�g�j��
	glDeleteProgram(g_ProgramID);			//�V�F�[�_�v���O�����I�u�W�F�N�g�j��

	glfwTerminate();// OpenGL�E�B���h�E����AGLFW���I������

	return;

}