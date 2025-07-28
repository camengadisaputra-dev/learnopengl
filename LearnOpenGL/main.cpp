#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

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

	Shader ourshader("vertex.vert", "fragment.frag");

	float vertices[] = {
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f, 1.0f, // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
	};

	// VBO Vertex Buffer Objects
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // this required

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &EBO);
	// REMEMBER TO BINDING FIRST
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// UNBIND IT
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//buffer loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		// rendering command
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//int vertexLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		ourshader.use();
		//glUniform4f(vertexLocation, 0.1f, greenValue, .5f, 1.0f); // this must use after use program

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

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