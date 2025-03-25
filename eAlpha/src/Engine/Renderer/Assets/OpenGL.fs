#version 330


out vec4 fragColor;

in vec3 interpColor;

void main()
{
  fragColor = vec4( interpColor, 1.0 );
}