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
    int blockCount; //Keeps track of figure's total blocks, 0 signifies a shape does not exist yet
    std::vector<block> shapeBlocks; //Points to pointer to array of blocks
  } state;
  
 public:
  
  //Shape Constructor for empty shape
  shape();
  
  //Shape Initializer
  void init();
  
  //Draw a shape by drawing the four blocks in shapeBlocks
  void draw(mat4 proj);
  
  //Getter Function for Shape
  block getBlock(int i);
  
};

#endif /* shape_hpp */
