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
    state.blockCount = 4;
  //I
  if(rand == 0){
      block tempOne(-2.0, 10.0);
      block tempTwo(-1.0, 10.0);
      block tempThree(0, 10.0);
      block tempFour(1.0, 10.0);
    tempOne.setColor(0.0, 1.0, 1.0);
    tempTwo.setColor(0.0, 1.0, 1.0);
    tempThree.setColor(0.0, 1.0, 1.0);
    tempFour.setColor(0.0, 1.0, 1.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  //J
  if(rand == 1){
     block tempOne(-1.0, 10.0);
      block tempTwo(-1.0, 9.0);
      block tempThree(0, 9.0);
      block tempFour(1.0, 9.0);
    tempOne.setColor(0.0, 0.0, 1.0);
    tempTwo.setColor(0.0, 0.0, 1.0);
    tempThree.setColor(0.0, 0.0, 1.0);
    tempFour.setColor(0.0, 0.0, 1.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  //L
  if(rand == 2){
  block tempOne(1.0, 10.0);
  block tempTwo(1.0, 9.0);
  block tempThree(0, 9.0);
  block tempFour(-1.0, 9.0);
    tempOne.setColor(1.0, 0.5, 0.0);
    tempTwo.setColor(1.0, 0.5, 0.0);
    tempThree.setColor(1.0, 0.5, 0.0);
    tempFour.setColor(1.0, 0.5, 0.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  //o
  if(rand == 3){
  block tempOne(0.0, 10.0);
  block tempTwo(0.0, 9.0);
  block tempThree(1.0, 10.0);
  block tempFour(1.0, 9.0);
    tempOne.setColor(1.0, 1.0, 0.0);
    tempTwo.setColor(1.0, 1.0, 0.0);
    tempThree.setColor(1.0, 1.0, 0.0);
    tempFour.setColor(1.0, 1.0, 0.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  //s
  if(rand == 4){
  block tempOne(-1.0, 9.0);
  block tempTwo(0.0, 9.0);
  block tempThree(0.0, 10.0);
  block tempFour(1.0, 10.0);
    tempOne.setColor(0.0, 1.0, 0.0);
    tempTwo.setColor(0.0, 1.0, 0.0);
    tempThree.setColor(0.0, 1.0, 0.0);
    tempFour.setColor(0.0, 1.0, 0.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  //T
  if(rand == 5){
  block tempOne(-1.0, 9.0);
  block tempTwo(0.0, 9.0);
  block tempThree(0.0, 10.0);
  block tempFour(1.0, 9.0);
    tempOne.setColor(1.0, 0.0, 1.0);
    tempTwo.setColor(1.0, 0.0, 1.0);
    tempThree.setColor(1.0, 0.0, 1.0);
    tempFour.setColor(1.0, 0.0, 1.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  //Z
  if(rand == 6){
  block tempOne(-1.0, 10.0);
  block tempTwo(0.0, 10.0);
  block tempThree(0.0, 9.0);
  block tempFour(1.0, 9.0);
    tempOne.setColor(1.0, 0.0, 0.0);
    tempTwo.setColor(1.0, 0.0, 0.0);
    tempThree.setColor(1.0, 0.0, 0.0);
    tempFour.setColor(1.0, 0.0, 0.0);
    tempOne.gl_init();
    tempTwo.gl_init();
    tempThree.gl_init();
    tempFour.gl_init();
    state.shapeBlocks.push_back(tempOne);
    state.shapeBlocks.push_back(tempTwo);
    state.shapeBlocks.push_back(tempThree);
    state.shapeBlocks.push_back(tempFour);
  }
  
  
}

//Empty Shape
void shape::emptyShape(){
  state.shapeBlocks.clear();
  rand++;
  if(rand == 7){
    rand = 0;
  }
}

 //Test if shape can move in this direction
 bool shape::moveTest(int direction){
  for(int i = 0; i < 4; i++){
    bool test = state.shapeBlocks[i].moveTest(direction);
    if(test == false){
      return test;
      break;
    }
  }
  return true;
 }

 //Move shape in given direction 0=down, 1=left, 2=right
void shape::move(int direction){
  if(moveTest(direction)){
  for(int i = 0; i < 4; i++){
    state.shapeBlocks[i].move(direction);
  }
  }
}


block shape::getBlock(int index){
  return state.shapeBlocks[index];
}

void shape::addBlock(block block, int index){
  state.shapeBlocks[index] = block;
}


//Draw a shape by drawing the four blocks in shapeBlocks
void shape::draw(mat4 proj){
    for(int i = 0; i < state.blockCount; i++){
      if(state.shapeBlocks[i].exists){
        state.shapeBlocks[i].draw(proj);
      }
    }
}

//Getter Function for Shape
//block getBlock(int i)

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

