#version 150

in vec4 vPos;
in vec4 vColor;
in vec2 vTexCoord
out vec4 color;

uniform mat4 M;

out vec2 texCoord;


void
main()
{

  texCoord = vTexCoord;

  gl_Position = M*vPos;
  color = vColor;
}
