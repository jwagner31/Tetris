
//
//  block.hpp
//  asteroids
//
//  Created by Joe Wagner on 12/1/21.
//


#ifndef __Tetris__Block__
#define __Tetris__Block__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <cmath>

#include "utils/Angel.h"
#include "utils/CheckError.h"
#include "utils/mat.h"
#include "utils/u8names.h"
#include "utils/vec.h"


using namespace Angel;

#include "shader.h"

#include <cmath>

class block{
  vec2 block_vert[4];
  vec3 block_color[4];
  
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
  
  //Current values for the block
  vec2 loc;
  vec3 color;
  
  //Block Constructor for initial spawn state
  block();
  
  //Initialize the gl state and variables
  void gl_init();
  
  //Draw a single block
  void draw(mat4 proj);
  
  inline vec2 getLocation(){
    return loc;
  }
  
  inline vec3 getColor(){
    return color;
  }
  
  inline void setLocation(float x, float y){
    loc.x = x;
    loc.y = y;
  }
  
  inline void setColor(float r, float g, float b){
    color.x = r;
    color.y = g;
    color.z = b;
  }
  
};


#endif /* defined(__Tetris__Block__) */
