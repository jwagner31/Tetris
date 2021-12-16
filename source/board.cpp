//
//  board.cpp
//  glad
//
//  Created by Joe Wagner on 12/1/21.
//

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
#include "block.hpp"
#include "shape.hpp"
#include "board.hpp"

board::board() {
  //Initialize board array with false exists blocks representing nonexistent blocks
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 10; j++){
      block filler(getX(j), getY(i));
      filler.exists = false;
      grid[i][j] = filler;
    }
  }
  drawShape = true;
};

void board::init(){
  currShape.init();
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 10; j++){
      grid[i][j].gl_init();
    }
  }
}

  //Animate the Board, Check if shape needs to be set
void board::animate(){
  if(!moveTest(0)){
    setShape();
    //Check if line needs to be deleted
    for(int i = 0; i <20; i++){
      if(!checkLine(i)){
        moveLinesDown(i);
      }
    }
    respawnShape();
    
  }else{
    //User's shape is moved down automatically
    move(0);
  }
}

  //Set Shape into blocks array
void board::setShape(){
  for(int k = 0; k < 4; k++){
    grid[getI(currShape.getBlock(k).getLocation().y)][getJ(currShape.getBlock(k).getLocation().x)].exists = true;
    
  }
}
  
  //Spawn new shape into blocks array
void board::respawnShape(){
  currShape.emptyShape();
  currShape.init();
}

//Returns false if full
bool board::checkLine(int i){
  for(int j = 0; j < 10; j++){
    if(grid[i][j].exists == false){
      return true;
      break;
    }
  }
  return false;
}

//delete blocks on line i, then shift lines above it down
void board::moveLinesDown(int i){
  for(int j = 0; j < 10; j++){
    grid[i][j].exists = false;
  }
  for(int k = i-1; k >= 0; k--){
    for(int j = 0; j < 10; j++){
      if(grid[k][j].exists){
        grid[k+1][j].exists = true;
        grid[k][j].exists = false;
      }
    }
  }
}



int board::getJ(float x){
  return x + 5;
}

int board::getI(float y){
  return (y-10)*-1;
}

float board::getX(int j){
  return j - 5.0;
}

float board::getY(int i){
  return (i*-1.0)+10.0;
}

void board::addBlock(block block){
  int j = block.loc.x + 5;
  int i = (block.loc.y - 10)*-1;
  grid[i][j].exists = true;
  grid[i][j].color = block.getColor();
}




  //Checks if block at position exists
  bool board::isEmpty(int i, int j){
    return !grid[i][j].exists;
  }

  //Sets block exists variable to false
  void board::deleteBlock(int i, int j){
    grid[i][j].exists = false;
  }

  //Move Test for Shape by boundaries and against blocks array
  bool board::moveTest(int direction){
    shape tempShape = currShape;
    bool boundaryCheck = tempShape.moveTest(direction);
    if(boundaryCheck){
      tempShape.move(direction);
      bool arrayCheck = true;
      //Check if there is block where tempShape would be
      for(int k = 0; k < 4; k++){
        int i = getI(tempShape.getBlock(k).getLocation().y);
        int j = getJ(tempShape.getBlock(k).getLocation().x);
        arrayCheck = isEmpty(i, j);
        if(arrayCheck == false){
          return arrayCheck;
          break;
        }
      }
      return true;
    }else{
      return boundaryCheck;
    }
    
  }
  
//Move current shape
void board::move(int direction){
  if(moveTest(direction)){
    currShape.move(direction);
  }
}

void board::gl_init(){

  float height = -10.0;
  for(int i = 0; i < 42; i++){
    if(i%2 == 0){
      board_vert[i] = vec2(-5.0, height);
    }
    else{
      board_vert[i] = vec2(5.0, height);
      height++;
    }
  }
  
  float width = -5.0;
  for(int j = 42; j < 64 ; j++){
    if(j%2 == 0){
      board_vert[j] = vec2(width, 10.0);
    }
    else{
      board_vert[j] = vec2(width, -10.0);
      width++;
    }
  }
  
  for(int k = 0; k < 64; k++){
    board_color[k] = vec3(0.0, 1.0, 0.0);
  }
  std::string vshader = shader_path + "vshader_board.glsl";
  std::string fshader = shader_path + "fshader_board.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);
  
  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);
  
  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);
  
  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);
  
  glBindFragDataLocation(GLvars.program, 0, "fragColor");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
   //Create GPU buffer to hold vertices and color
    glBufferData( GL_ARRAY_BUFFER, sizeof(board_vert) + sizeof(board_color), NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(board_vert), board_vert );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(board_vert), sizeof(board_color), board_color );
    
    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );
    
    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(board_vert)) );
    
    glBindVertexArray(0);

  }

//Draw the Board
void board::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj);

  glDrawArrays(GL_LINES, 0, 64);
  
  //Draw something
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 10; j++){
      if(!isEmpty(i, j)){
        grid[i][j].draw(proj);
      }
    }
  }
  if(drawShape){
    currShape.draw(proj);
  }
  
  glBindVertexArray(0);
  glUseProgram(0);

}


  


