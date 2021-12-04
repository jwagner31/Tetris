//
//  board.hpp
//  glad
//
//  Created by Joe Wagner on 12/1/21.
//

#ifndef board_hpp
#define board_hpp

#include "common.h"
#include "block.hpp"

class board{
public:
 
  
  GLuint vao;
  GLuint program;
  GLuint buffer;
  GLuint vertex_shader, fragment_shader;
  GLint vpos_location, vcolor_location;
  GLint PM_location;

  std::vector<block> blocks;
  
  void init();
  
  void update();
    
  void emit();
  void draw(mat4 proj);
  
  };
 

#endif /* board_hpp */
