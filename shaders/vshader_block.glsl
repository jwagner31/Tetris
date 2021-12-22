#version 150

in vec4 vPos;
in vec4 vColor;
out vec4 color;
in vec2 vTexCoord;
out vec2 texCoord;
uniform mat4 M;


void
main()
{
  texCoord = vTexCoord;
  gl_Position = M*vPos;
  color = vColor;
  
}
