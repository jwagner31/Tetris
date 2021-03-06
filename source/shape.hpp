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
  
  //Current Random Shape
  int rand;
  
  //Orientation of Shape
  int orientation;
  
  //Shape Constructor for empty shape
  shape();
  
  //Shape's centroid for rotation
  vec2 centroid;
   
  //Shape Initializer
  void init();
  
  //Empty Shape
  void emptyShape();
  
  //Test if shape can move in this direction
  bool moveTest(int direction);

  //Move shape in given direction 0=down, 1=left, 2=right
  void move(int direction);
  
  //Rotate shape
  void rotate();
  
  //Draw a shape by drawing the four blocks in shapeBlocks
  void draw(mat4 proj);
  
  //Getter Function for Shape
  block getBlock(int index);
  
  //Add block at specified index
  void addBlock(block block, int index);
  
};

#endif /* shape_hpp */
