//
// cc glfw-opengl-example.c glad.c -lglfw
//
#include "GLAD/glad.h" // https://glad.dav1d.de/
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "shader.h"
#include "ui.cpp"
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include <nuklear/nuklear.h>


static void keyHandler(GLFWwindow *window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {

        switch (key) {

            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;

        }
        
    }

}


int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(1280, 720, "tetris", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, keyHandler);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders("ColTriangle.vertexshader", "ColTriangle.fragmentshader");

    // MVP handle -- only to be in the initialization
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // (field of view, ratio 4:3, display range, 0.1 -> 100 units)
    // glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 1280 / (float) 720, 0.1f, 100.0f);
    glm::mat4 Projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

    // Camera matrix
    // glm::mat4 View = glm::lookAt(
    //     glm::vec3(640,360,5), // Camera is at (4,3,3), in World Space
    //     glm::vec3(0,0,0), // and looks at the origin
    //     glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    // );
    // glm::mat4 View = glm::mat4(1.0f);
    // Not necessary in 2D

    // Model/identity matrix
    glm::mat4 Model = glm::mat4(1.0f);

    // scaling matrix
    // Model = glm::scale(Model, glm::vec3(0.5f, 1.0f, 2.0f));

    // translation
    // Model = glm::translate(Model, glm::vec3(0.0f, 2.0f, 0.0f));
    // Model = glm::translate(Model, glm::vec3(-100.0f, 100.0f, 0.0f));

    // ModelViewProjection
    glm::mat4 mvp = Projection * Model; // Has to be multiplied in order

    static const GLfloat g_vertex_buffer_data[] = {
        0.0f, 720.0f, 0.0f,
        640.0f, 0.0f, 0.0f,
        1280.0f, 720.0f, 0.0f,

        0.0f, 0.0f, 0.0f,
        640.0f, 720.0f, 0.0f,
        1280.0f, 0.0f, 0.0f
    };

    const GLfloat g_color_buffer_data2[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
    };

    const GLfloat g_color_buffer_data1[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
    };

    for (int i = 0; i < sizeof(g_color_buffer_data1); i++) {
        std::cout << g_color_buffer_data1[i] << ", ";
    } std::cout << "\n\n";

    GLfloat* g_color_buffer_data = new GLfloat[sizeof(g_color_buffer_data1) + sizeof(g_color_buffer_data2)];
    std::copy(g_color_buffer_data1, g_color_buffer_data1 + sizeof(g_color_buffer_data1), g_color_buffer_data);
    std::copy(g_color_buffer_data2, g_color_buffer_data2 + sizeof(g_color_buffer_data2), g_color_buffer_data + sizeof(g_color_buffer_data1));

    for (int i = 0; i < sizeof(g_color_buffer_data); i++) {
        std::cout << g_color_buffer_data[i] << ", ";
    } std::cout << "\n";

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data1), g_color_buffer_data1, GL_STATIC_DRAW);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        glUseProgram(programID);

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
			1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
        );


        glDrawArrays(GL_TRIANGLES, 0, 2*3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glfwSwapBuffers(window);
    } while (!glfwWindowShouldClose(window));

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}