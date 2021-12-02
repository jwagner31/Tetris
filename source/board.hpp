//
//  board.hpp
//  glad
//
//  Created by Joe Wagner on 12/1/21.
//

#ifndef board_hpp
#define board_hpp

#include "common.h"

class board{
public:

  
  GLuint vao;
  GLuint program;
  GLuint buffer;
  GLuint vertex_shader, fragment_shader;
  GLint vpos_location, vcolor_location;
  GLint PM_location;
  
  board();
  
  void gl_init();
  
  void update();
  
  block **blockGrid;
  
  
    
  
  };
 

#endif /* board_hpp */
