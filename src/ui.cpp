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


class UI {

    private:

        int outerTriangles;
        GLfloat UIr = 0.0f;
        GLfloat UIg = 0.0f;
        GLfloat UIb = 0.0f;

    public:

        void setUIColor(int r, int g, int b) {

            UIr = r / 255.0f;
            UIg = g / 255.0f;
            UIb = b / 255.0f;

        }

        GLuint outerVertexBuffer() {

            static const GLfloat g_vertex_buffer_data[] = {
                0.0f, 720.0f, 0.0f,
                640.0f, 0.0f, 0.0f,
                1280.0f, 720.0f, 0.0f
            };

            GLuint vertexBuffer;
            glGenBuffers(1, &vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        
        }

        GLuint outerColorBuffer() {

            static const GLfloat g_color_buffer_data[] = {
                0.583f,  0.771f,  0.014f,
                0.609f,  0.115f,  0.436f,
                0.327f,  0.483f,  0.844f
            };

            GLuint colorBuffer;
            glGenBuffers(1, &colorBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

        }

};