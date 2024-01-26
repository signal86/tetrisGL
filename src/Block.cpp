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


class Block {
    
    public:

        char blockType;

        Block() {

            char blockTypes[] = "ijlostz";
            blockType = blockTypes[rand() % 7];
            delete[] blockTypes;

        }

};