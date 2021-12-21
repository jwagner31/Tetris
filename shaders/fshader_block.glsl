#version 150

in  vec4 color;
in  vec2 texCoord;
out vec4 fragColor;

uniform sampler2D textureGray;

void
main()
{
  vec4 textureColor = texture(textureGray, texCoord);

  fragColor = color + textureColor;
  fragColor = clamp(fragColor, 0.0, 1.0);
  fragColor.a = 1.0;

}
