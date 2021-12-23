//
//  Created by Joe Wagner on 12/1/21.
//

#ifndef board_hpp
#define board_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <cmath>

#include "utils/Angel.h"

using namespace Angel;

#include "shader.h"
#include "block.hpp"
#include "shape.hpp"

class board{

    //10 top 10 bottom 22 left right 22 right
    vec2 board_vert[64];
    vec3 board_color[64];
    
    //OpenGL variables for a block
    struct {
      GLuint vao;           //Vertex array object
      GLuint program;       //shader program
      GLuint buffer;        //Vertex buffer objects
      GLuint vertex_shader, fragment_shader;  //Shaders
      GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
      GLint M_location;     //Reference to matrix in shader
    } GLvars;
    

   public:
  
    //2d Array representing Board
    block grid[20][10];
  
    //Current shape being controlled by user
    shape currShape;
  
    //Tells board to draw currshape
  bool drawShape;
        
    //Board Constructor for initial spawn state
    board();
  
    //Animate the Board, Check if shape needs to be set
    void animate();
  
    //Rotate currShape
  void rotate();
    //Set Shape into blocks array
    void setShape();
    
    //Spawn new shape into blocks array
    void respawnShape();
    
    //See if line needs to be deleted
    bool checkLine(int i);
  
    //Move lines down if line is full
    void moveLinesDown(int i);
  
    void init();

    //Convert x coord to board vector position
    int getJ(float x);

    //Convert y coord to board vector position
    int getI(float y);
  
    //Convert j position to x coord
    float getX(int j);

    //Convert i position to y coord
    float getY(int i);
  
    //Add Block to board based on current loc of block
    void addBlock(block block);
  
    
    //Checks if block at position exists
    bool isEmpty(int i, int j);
  
    //Sets block exists variable to false
    void deleteBlock(int i, int j);
  
    //Move Test for Shape
    bool moveTest(int direction);
    
    //Move current shape
    void move(int direction);
  
    //Initialize the gl state and variables
    void gl_init();
    
    //Draw the board
    void draw(mat4 proj);

};
 

#endif /* board_hpp */



