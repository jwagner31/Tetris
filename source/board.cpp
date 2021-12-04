//
//  board.cpp
//  glad
//
//  Created by Joe Wagner on 12/1/21.
//

#include "common.h"

board::board() {

};

void board::init() {
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

/*void board::gl_init() {
    //Board
    vec2 tempVec = board::getLocation();
    board_vert[0] = tempVec;
    board_vert[1] = vec2(tempVec.x, tempVec.y - 1);
    block_vert[2] = vec2(tempVec.x + 1, tempVec.y);
    block_vert[3] = vec2(tempVec.x + 1, tempVec.y - 1);


    block_color[0] = block::getColor();
    block_color[1] = block::getColor();
    block_color[2] = block::getColor();
    block_color[3] = block::getColor();

    std::string vshader = shader_path + "vshader_block.glsl";
    std::string fshader = shader_path + "fshader_block.glsl";

    GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
    GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

    GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(GLvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
    glCompileShader(GLvars.vertex_shader);
    check_shader_compilation(vshader, GLvars.vertex_shader);

    GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(GLvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
    glCompileShader(GLvars.fragment_shader);
    check_shader_compilation(fshader, GLvars.fragment_shader);

    GLvars.program = glCreateProgram();
    glAttachShader(GLvars.program, GLvars.vertex_shader);
    glAttachShader(GLvars.program, GLvars.fragment_shader);

    glLinkProgram(GLvars.program);
    check_program_link(GLvars.program);

    glBindFragDataLocation(GLvars.program, 0, "fragColor");

    GLvars.vpos_location = glGetAttribLocation(GLvars.program, "vPos");
    GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor");
    GLvars.M_location = glGetUniformLocation(GLvars.program, "M");

    // Create a vertex array object
    glGenVertexArrays(1, &GLvars.vao);
    //Set GL state to use vertex array object
    glBindVertexArray(GLvars.vao);

    //Generate buffer to hold our vertex data
    glGenBuffers(1, &GLvars.buffer);
    //Set GL state to use this buffer
    glBindBuffer(GL_ARRAY_BUFFER, GLvars.buffer);

    //Create GPU buffer to hold vertices and color
    glBufferData(GL_ARRAY_BUFFER, sizeof(block_vert) + sizeof(block_color), NULL, GL_STATIC_DRAW);
    //First part of array holds vertices
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(block_vert), block_vert);
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(block_vert), sizeof(block_color), block_color);

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location);

    glVertexAttribPointer(GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(block_vert)));

    glBindVertexArray(0);

}*/
void board::draw(mat4 proj) {

};
  

  

