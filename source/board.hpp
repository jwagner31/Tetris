//
//  Created by Joe Wagner on 12/1/21.
//

#ifndef board_hpp
#define board_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <cmath>

#include "utils/Angel.h"

using namespace Angel;

#include "shader.h"
#include "block.hpp"

class board{
public:
    //11 top 11 bottom 21 left right 21 right
    vec2 board_vert[4];
    vec3 board_color[4];
    
    //OpenGL variables for a block
    struct {
      GLuint vao;           //Vertex array object
      GLuint program;       //shader program
      GLuint buffer;        //Vertex buffer objects
      GLuint vertex_shader, fragment_shader;  //Shaders
      GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
      GLint M_location;     //Reference to matrix in shader
    } GLvars;
    

   public:
        
    //Board Constructor for initial spawn state
    board();
    
    //Initialize the gl state and variables
    void gl_init();
    
    //Draw the board
    void draw(mat4 proj);

};
 

#endif /* board_hpp */



