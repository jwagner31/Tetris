//
//  Ship.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"

//Ship constructor
Ship::Ship(){
  //Set up initial state here
  
  state.cur_location = vec2(0.0, 0.0);
  state.angle = (0.0);
  state.pointing = vec2(0.0, -1.0);
  state.velocity = vec2(0.0, -0.1);
  state.thruster_on = false;
};

//Called everytime an animation tick happens
void Ship::update_state(){
  // Things to do:
  //a = F
  //Force is in the direction the ship is pointing
  //Clamp acceleration at some maximum value
  
  //v  = old_velocity + a*dt
  // clamp velocity at a maximum value
  // Dampen the velocity at every timestep to lessen intertia

  //p  = old_position + v*dt
  // Wrap the ship position when at the boundary
  
  
  
  if(state.thruster_on){
    state.velocity.x = state.velocity.x + state.pointing.x*_ACC*(.01);
    state.velocity.y = state.velocity.y + state.pointing.y*_ACC*(.01);
  }
  
  if(length(state.velocity) > _MAX_SPEED){
    state.velocity = normalize(state.velocity)*_MAX_SPEED;
  }
  state.velocity *= _DAMPING;
    
    state.cur_location.x += state.velocity.x*(.01);
    state.cur_location.y += state.velocity.y*(.01);
}

//Initialize the gl state and variables
void Ship::gl_init(){
  //Ship
  //!!!!!!!!Populate ship_vert and ship_color
  //Ship
  //!!!!!!!!Populate ship_vert and ship_color
  
  ship_vert[0] = vec2(0.5,0.75);
  ship_vert[1] = vec2(0,-1);
  ship_vert[2] = vec2(-0.5,0.75);
  ship_vert[3] = vec2(-0.25, 1);
  ship_vert[4] = vec2(0,1);
  ship_vert[5] = vec2(0.25, 1);
  
  ship_vert[6] = vec2(-0.1, 1);
  ship_vert[7] = vec2(-0.7, 1.8);
  ship_vert[8] = vec2(-0.15, 1.5);
  ship_vert[9] = vec2(0.0, 2.25);
  ship_vert[10] = vec2(0.15, 1.5);
  ship_vert[11] = vec2(0.7, 1.8);
  ship_vert[12] = vec2(0.1, 1);
  //Uncomment to show the pointing vector
  //ship_vert[13] = state.cur_location;
  //ship_vert[14] = state.pointing;



  ship_color[0] = vec3(1.0, 1.0, 1.0);
  ship_color[1] = vec3(1.0, 1.0, 1.0);
  ship_color[2] = vec3(1.0, 1.0, 1.0);
  ship_color[3] = vec3(1.0, 1.0, 1.0);
  ship_color[4] = vec3(1.0, 1.0, 1.0);
  ship_color[5] = vec3(1.0, 1.0, 1.0);
  
  ship_color[6] = vec3(1.0, 0.7, 0.0);
  ship_color[7] = vec3(1.0, 0.7, 0.0);
  ship_color[8] = vec3(1.0, 0.7, 0.0);
  ship_color[9] = vec3(1.0, 0.7, 0.0);
  ship_color[10] = vec3(1.0, 0.7, 0.0);
  ship_color[11] = vec3(1.0, 0.7, 0.0);
  ship_color[12] = vec3(1.0, 0.7, 0.0);
  //Pointing vector
  //ship_color[13] = vec3(0.0, 0.8, 0.0);
  //ship_color[13] = vec3(0.0, 0.8, 0.0);

  
  
  std::string vshader = shader_path + "vshader_Ship.glsl";
  std::string fshader = shader_path + "fshader_Ship.glsl";
  
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
  glBufferData( GL_ARRAY_BUFFER, sizeof(ship_vert) + sizeof(ship_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(ship_vert), sizeof(ship_color), ship_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ship_vert)) );
  
  glBindVertexArray(0);

                 

}

//Draw a ship
void Ship::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  mat4 M1;
  M1 = Translate(state.cur_location.x, state.cur_location.y, 0.0)*RotateZ(state.angle) * Scale(0.10, 0.10, 1);
    
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj*M1 );
  
  //Draw something
  //glDrawArrays(GL_LINE_LOOP, 0, 6);
  glDrawArrays(GL_LINE_LOOP, 0, 6);
  //glDrawArrays(GL_LINES, 12, 2);
  
  
  if(state.thruster_on){
     glDrawArrays(GL_LINE_LOOP, 6, 7);
    //Maybe draw something different if the thruster is on
  }
  
  glBindVertexArray(0);
  glUseProgram(0);

}


