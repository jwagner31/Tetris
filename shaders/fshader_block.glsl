#version 150

in  vec4 color;
in vec2 texCoord;
uniform sampler2D textureGray;
out vec4 fragColor;

void
main()
{

  vec4 textureColor = (texture(textureGray, texCoord));


  fragColor = color + textureColor;
  fragColor = clamp(fragColor, 0.0, 1.0);
  fragColor.a = 1.0;

}
