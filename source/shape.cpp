//
//  shape.cpp
//  glad
//
//  Created by Joe Wagner on 12/7/21.
//

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
#include "shape.hpp"


//Shape Constructor for empty shape
shape::shape(){
  state.blockCount = 0;
};

//Shape Initializer
void shape::init(){
  if(state.shapeBlocks.empty()){
    state.blockCount = 4;
    for(int i = 0; i < state.blockCount; i++){
      
    }
  }
}

//Draw a shape by drawing the four blocks in shapeBlocks
void draw(mat4 proj);

//Getter Function for Shape
block getBlock(int i);
/*
//Draw a block
void block::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  mat4 M1;
  M1 = Translate(getLocation().x, getLocation().y, 0.0);
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj*M1);
  
  //Draw something
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glBindVertexArray(0);
  glUseProgram(0);

}
*/

