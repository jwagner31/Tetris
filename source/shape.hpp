//
//  shape.hpp
//  glad
//
//  Created by Joe Wagner on 12/7/21.
//

#ifndef shape_hpp
#define shape_hpp

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

#include <cmath>

class shape{
  
  struct{
    int blockCount; //Keeps track of figure's blocks, 0 signifies block does not exist yet
    block **shapeBlocks; //Points to array 
  } state;
 public:
  
  //Shape Constructor
  shape();
  
  
  
  
  //Draw a single block
  void draw(mat4 proj);
  
};

#endif /* shape_hpp */
