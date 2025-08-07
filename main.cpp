#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	glfwInit();
	// tell opengl to use opengl 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window first
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//opengl function goes here
	glViewport(0, 0, 800, 600);
	//resize?
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);

	Shader ourshader("shader/shader.vert", "shader/shader.frag");

	float vertices[] = {
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // front top left 0
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right 1
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom right 2
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left 3

		-0.5f,  0.5f, 0.5f,  0.0f, 1.0f, // back top left 4
		 0.5f,  0.5f, 0.5f,  1.0f, 1.0f, // top right 5
		 0.5f, -0.5f, 0.5f,  1.0f, 0.0f, // bottom right 6
		-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, // bottom left 7

		-0.5f,  0.5f, 0.5f,  1.0f, 1.0f, // back top left 8
		-0.5f, -0.5f, 0.5f,	 1.0f, 0.0f, // back bottom left 9

		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // front top right 10
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // front bottom right 11

		0.5f,  0.5f, 0.5f,  1.0f, 0.0f, // back top right 12
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, // front top right 13

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom left 14
		-0.5f, -0.5f, 0.5f,	 1.0f, 1.0f, // bottom left 15


	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		2, 3, 0,   // second triangle

		4, 5, 6,
		6, 7, 4,

		0, 8, 9,
		9, 3, 0,

		10, 5, 6,
		6, 11, 10,

		0, 8, 12,
		12, 13, 0,

		14, 15, 6,
		6, 11, 14,
	};

	// VBO Vertex Buffer Objects
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // this required

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Texture texture1;
	texture1.loadTexture("resources/container.jpg", GL_RGB);
	Texture texture2;
	texture2.loadTexture("resources/awesomeface.png", GL_RGBA);


	glGenBuffers(1, &EBO);
	// REMEMBER TO BINDING FIRST
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// UNBIND IT
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	ourshader.use();
	glUniform1i(glGetUniformLocation(ourshader.ID, "texture1"), 0);
	ourshader.setInt("texture2", 1);

	ourshader.use();
	glActiveTexture(GL_TEXTURE0);
	texture1.applyTexture();
	glActiveTexture(GL_TEXTURE1);
	texture2.applyTexture();

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//buffer loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		// rendering command
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f); //clip space
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //view space	

		ourshader.setMat4("projection", projection);
		ourshader.setMat4("view", view);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i * (float)glfwGetTime();
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourshader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

		// check and call event
		glfwPollEvents();
		processInput(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(ourshader.ID);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}