//
//  block.cpp
//  asteroids
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

using namespace Angel;

#include "shader.h"
#include "block.hpp"
#include "lodepng.h"
#include "SourcePath.h"
#include "SourcePath.cpp.in"


GLuint gray_texture;

/* -------------------------------------------------------------------------- */
#ifdef _WIN32
static
unsigned int lodepng_decode_wfopen(std::vector<unsigned char>& out, unsigned& w, unsigned& h,
  const std::string& filename,
  LodePNGColorType colortype = LCT_RGBA, unsigned bitdepth = 8)
{
  std::wstring wcfn;
  if (u8names_towc(filename.c_str(), wcfn) != 0)
    return 78;
  FILE* fp = _wfopen(wcfn.c_str(), L"rb");
  if (fp == NULL) { return 78; }

  std::vector<unsigned char> buf;
  fseek(fp, 0L, SEEK_END);
  long const size = ftell(fp);
  if (size < 0) {
    fclose(fp);
    return 78;
  }

  fseek(fp, 0L, SEEK_SET);
  buf.resize(size);
  fread(buf.data(), 1, size, fp);
  fclose(fp);

  return lodepng::decode(out, w, h, buf, colortype, bitdepth);
}
#endif //_WIN32

void loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex){
  
  std::vector<unsigned char> image;
  unsigned int width;
  unsigned int height;
  //decode
#ifdef _WIN32
  unsigned error = lodepng_decode_wfopen(image, width, height, lpszPathName, LCT_RGBA, 8);
#else
  unsigned error = lodepng::decode(image, width, height, lpszPathName, LCT_RGBA, 8);
#endif //_WIN32

  //if there's an error, display it
  if(error){
    std::cout << "decoder error " << error;
    std::cout << ": " << lodepng_error_text(error) << std::endl;
    return;
  }

  /* the image "shall" be in RGBA_U8 format */

  std::cout << "Image loaded: " << width << " x " << height << std::endl;
  std::cout << image.size() << " pixels.\n";
  std::cout << "Image has " << image.size()/(width*height) << "color values per pixel.\n";

  GLint GL_format = GL_RGBA;

  glActiveTexture( GLtex );
  glBindTexture( GL_TEXTURE_2D, textureID );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_format, width, height, 0, GL_format, GL_UNSIGNED_BYTE, &image[0] );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glGenerateMipmap(GL_TEXTURE_2D);
  
  //Put things away and free memory
  image.clear();
}


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

  //Block Constructor
  block::block(){
    loc = vec2(0.0, 0.0);
    origin = vec2(loc.x-0.5, loc.y-0.5);
    color = vec3(0.0, 0.0, 1.0);
    exists = true;

  };

  block::block(float x, float y){
    loc = vec2(x, y);
    origin = vec2(loc.x-0.5, loc.y-0.5);
    color = vec3(0.8, 0.0, 0.0);
    exists = true;

  };

  bool block::moveTest(int direction){
    if(direction == 0){
      if(getLocation().y-1 >= -9.0){
        return true;
      }
    }
    if(direction == 1){
      if(getLocation().x-1 >= -5.0){
        return true;
      }
    }
    if(direction == 2){
      if(getLocation().x+1 <= 4.0){
        return true;
      }
    }
    return false;
  }

  //Move block in given direction 0=down, 1=left, 2=right
  void block::move(int direction){
      //Move Down
      if(direction == 0){
        setLocation(getLocation().x, getLocation().y-1);
        setOrigin(origin.x, origin.y-1.0);
      }
      if(direction == 1){
        setLocation(getLocation().x-1, getLocation().y);
        setOrigin(origin.x-1.0, origin.y);
      }
      if(direction == 2){
        setLocation(getLocation().x+1, getLocation().y);
        setOrigin(origin.x+1, origin.y);
      }
  }

//Rotate around center (0=clockwise, 1=counter-clockwise)
void block::rotate(int orientation, vec2 centroid){
  
  if(origin.x != centroid.x && origin.y != centroid.y){
    //float distX = origin.x - centroid.x;
    //float distY = centroid.y - origin.y;
    
    float newX = centroid.x+centroid.y-origin.y;
    float newY = centroid.y-centroid.x+origin.x;
      
    origin.x = newX;
    origin.y = newY;
    loc.x = newX-0.5;
    loc.y = newY+0.5;
  }
  
}

void block::gl_init(){

  block_vert[0] = vec2(0.0, 0.0);
  block_vert[1] = vec2(0.0, -1.0);
  block_vert[2] = vec2(1.0, 0.0);
  block_vert[3] = vec2(1.0, -1.0);
  
  block_color[0] = color;
  block_color[1] = color;
  block_color[2] = color;
  block_color[3] = color;

  texture_coords[0] = vec2(0.0, 1.0);
  texture_coords[1] = vec2(0.0, 0.0);
  texture_coords[2] = vec2(1.0, 1.0);
  texture_coords[3] = vec2(1.0, 0.0);

  std::string vshader = shader_path + "vshader_block.glsl";
  std::string fshader = shader_path + "fshader_block.glsl";
  
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

  //Per Vertex Attributes
  GLuint vTexCoord = glGetAttribLocation( GLvars.program, "vTexCoord");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );

  unsigned int uv_bytes = 4*sizeof(vec2);
  
  //Generate Texture
  glGenTextures( 1, &gray_texture);

  std::string gray_img = source_path + "/Images/gray_block.png";
  loadFreeImageTexture(gray_img.c_str(), gray_texture, GL_TEXTURE0);
  glUniform1i( glGetUniformLocation(GLvars.program, "textureGray"),0);

  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(block_vert) + sizeof(block_color) + sizeof(texture_coords), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(block_vert), block_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(block_vert), sizeof(block_color), block_color );
  //Third part holds texture coordinates
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(block_color),sizeof(texture_coords), texture_coords);
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  glEnableVertexAttribArray(vTexCoord);
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(block_vert)) );
  glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(block_vert)+sizeof(block_color)));

  glBindVertexArray(0);

}

//Draw a block
void block::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  mat4 M1;
  M1 = Translate(getLocation().x, getLocation().y, 0.0);
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj*M1);
  
  //Draw something
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glBindVertexArray(0);
  glUseProgram(0);

}




