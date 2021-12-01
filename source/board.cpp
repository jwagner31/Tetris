//
//  board.cpp
//  glad
//
//  Created by Joe Wagner on 12/1/21.
//

#include "common.h"

void board::init(){
  std::string vshader = shader_path + "vshader_board.glsl";
  std::string fshader = shader_path + "fshader_board.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  check_shader_compilation(vshader, vertex_shader);
  
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
  check_shader_compilation(fshader, fragment_shader);
  
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  
  glLinkProgram(program);
  check_program_link(program);
  
  glBindFragDataLocation(program, 0, "fragColor");
  
  vpos_location   = glGetAttribLocation(program, "vPos");
  vcolor_location = glGetAttribLocation( program, "vColor" );
  PM_location = glGetUniformLocation( program, "ProjectionModelview" );

  // Create a vertex array object
  glGenVertexArrays( 1, &vao );
  //Set GL state to use vertex array object
  glBindVertexArray( vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &buffer );
  
  glEnableVertexAttribArray(vpos_location);
  glEnableVertexAttribArray( vcolor_location );
  
  glBindVertexArray(0);

  delete[] vertex_shader_source;
  delete[] fragment_shader_source;
  
};

  void board::update(){
  
    vec2 *pos = new vec2[blocks.size()];
    vec3 *col = new vec3[blocks.size()];

    for(unsigned int i=0; i < blocks.size(); i++){
      pos[i] = blocks[i].loc;
      col[i] = blocks[i].color;
    }
    
    //Set GL state to use this buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
    //Create GPU buffer to hold vertices and color
    glBufferData( GL_ARRAY_BUFFER, blocks.size()*sizeof(vec2) + blocks.size() *sizeof(vec3), NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, blocks.size()*sizeof(vec2), pos );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, blocks.size()*sizeof(vec2), blocks.size()*sizeof(vec3), col );

    glVertexAttribPointer( vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(blocks.size()*sizeof(vec2)) );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    delete[] pos;
    delete[] col;

  };
  
  void board::emit(){
    blocks.push_back(blocks());
  };
  

