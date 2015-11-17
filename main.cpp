#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Player.hpp"
#include "Game.hpp"

const char* vertexShaderCode =
"#version 130\n\
in vec3 position;\n\
uniform mat4 matrix;\n\
void main()\n\
{\n\
	gl_Position = vec4(position, 1.0) * matrix;\n\
}\n";

const char* fragmentShaderCode =
"#version 130\n" \
"void main(){\n" \
"	gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n" \
"}\n";

enum
{
	ATTRIBUTE_VERTEX_COORDINATE,
	NUM_ATTRIBUTES
};

int main()
{
	glfwInit();

	int count;
	GLFWmonitor ** monitors = glfwGetMonitors(&count);
	GLFWmonitor * monitor = monitors[0];
	//GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	GLFWvidmode const * mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	std::shared_ptr<GLFWwindow> window(glfwCreateWindow(mode->width, mode->height, "TOR", nullptr, nullptr), glfwDestroyWindow);
	glfwMakeContextCurrent(window.get());

	glLoadIdentity();
	glViewport(0, 0, mode->width, mode->height);
	gluPerspective(90, static_cast<double>(mode->width) / static_cast<double>(mode->height), 1, 1024);
	gluLookAt(0, 0, 256, 0, 0, 0, 0, 1, 0);
	/*
	glfwSetWindowSizeCallback(window.get(),[](GLFWwindow * window, int w, int h)
	{
		glViewport(0, 0, w, h);
		glLoadIdentity();
		gluPerspective(90, static_cast<double>(w) / static_cast<double>(h), 1, 100);
		gluLookAt(0, 0, 64, 0, 0, 0, 0, 1, 0);
	});
	*/

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}

	std::cerr << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cerr << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cerr << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cerr << "GL_RENDERER: " << glGetString(GL_RENDERER) << std::endl;

		// 頂点シェーダオブジェクトの作成
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	// 頂点シェーダのコンパイルが正常に行えたかどうかのチェック
	GLint vertexShaderCompileStatus;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus);
	if (vertexShaderCompileStatus == GL_FALSE)
	{
		std::cerr << "Vertex Shader Compile Error: ";
		GLsizei logLength, logLengthWritten;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH , &logLength);
		GLchar *logString = new GLchar[logLength];
		glGetShaderInfoLog(vertexShader, logLength, &logLengthWritten, logString);
		std::cerr << logString << std::endl;
		delete[] logString;
	}

	// フラグメントシェーダオブジェクトの作成
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	// フラグメントシェーダのコンパイルが正常に行えたかどうかのチェック
	GLint fragmentShaderCompileStatus;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);
	if (fragmentShaderCompileStatus == GL_FALSE)
	{
		std::cerr << "Fragment Shader Compile Error." << std::endl;
		GLsizei logLength, logLengthWritten;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH , &logLength);
		GLchar *logString = new GLchar[logLength];
		glGetShaderInfoLog(fragmentShader, logLength, &logLengthWritten, logString);
		std::cerr << logString << std::endl;
		delete[] logString;
	}

	// プログラムオブジェクトの作成
	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// シェーダコード内の変数にインデックスを設定する
	glBindAttribLocation(program, ATTRIBUTE_VERTEX_COORDINATE, "position");
	glBindAttribLocation(program, 1, "matrix");

	// プログラムオブジェクトのリンク
	glLinkProgram(program);

	// リンクが正常に行えたかどうかのチェック
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		std::cerr << "Program Link Error." << std::endl;
		GLsizei logLength, logLengthWritten;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		GLchar *logString = new GLchar[logLength];
		glGetProgramInfoLog(program, logLength, &logLengthWritten, logString);
		std::cerr << logString << std::endl;
		delete[] logString;
	}

	// 頂点シェーダをリリースする
	if (vertexShader)
	{
		glDetachShader(program, vertexShader);
		glDeleteShader(vertexShader);
	}

	// フラグメントシェーダをリリースする
	if (fragmentShader)
	{
		glDetachShader(program, fragmentShader);
		glDeleteShader(fragmentShader);
	}

	static double faceVertexCoordinates[] =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	// 頂点配列オブジェクトを作成して設定する
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	{
	// 頂点バッファオブジェクトを作成する
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(double)*9, faceVertexCoordinates, GL_STATIC_DRAW);

	// 頂点バッファオブジェクトにシェーダ内の変数vertexCoodrinateを結びつける
	glEnableVertexAttribArray(ATTRIBUTE_VERTEX_COORDINATE);
	glVertexAttribPointer(ATTRIBUTE_VERTEX_COORDINATE, 3, GL_DOUBLE, GL_FALSE, sizeof(double)*3, 0);
	}

	{
	glUseProgram(program);
	int index = glGetUniformLocation(program, "matrix");
	std::cout << index << std::endl;

	glPushMatrix();
	GLfloat matrix[16];
	glLoadIdentity();
	glTranslated(-0.4, 0.1, 0);
	glViewport(0, 0, mode->width, mode->height);
	gluPerspective(90, static_cast<double>(mode->width) / static_cast<double>(mode->height), 1, 1024);
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	for (auto e : matrix)
	std::cout << e << std::endl;

	glUniformMatrix4fv(index, 1, true, matrix);
	glPopMatrix();
	}

	Game game(window);

	while (!glfwWindowShouldClose(window.get()))
	{
		glClearColor(0x30 / static_cast<double>(0xFF), 0x40 / static_cast<double>(0xFF), 0x60 / static_cast<double>(0xFF), 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glBindVertexArray(vao);
		glUseProgram(program);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glUseProgram(0);

		//game.run();
		//game.draw();
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	glDeleteProgram(program);
	glfwTerminate();
}

