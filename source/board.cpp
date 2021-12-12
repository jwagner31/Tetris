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
  /*
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 10; j++){
      grid[i][j] = ;
    }
  }
   */
};

int board::getJ(float x){
  return x + 5;
}

int board::getI(float y){
  return (y-10)*-1;
}

void board::addBlock(block block){
  int j = block.loc.x + 5;
  int i = (block.loc.y - 10)*-1;
  grid[i][j] = block;
}

void board::addShape(shape shape){
  for(int index = 0; index < 4; index++){
    addBlock(shape.getBlock(index));
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
      grid[i][j].draw(proj);
    }
  }
  
  
  glBindVertexArray(0);
  glUseProgram(0);

}


  


