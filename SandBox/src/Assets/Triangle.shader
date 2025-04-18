#shader vertex

#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 VP;
uniform mat4 Trans;

out vec4 interpColor;

void main()
{
   interpColor = color;
   gl_Position = VP * Trans * vec4(position, 1.0);
}

#shader fragment

#version 330


out vec4 fragColor;

in vec4 interpColor;

void main()
{
    fragColor = interpColor;
}