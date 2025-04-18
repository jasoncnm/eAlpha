#shader vertex

#version 330

layout(location = 0) in vec3 position;

uniform mat4 VP;
uniform mat4 Trans;

void main()
{
   gl_Position = VP * Trans * vec4(position, 1.0);
}


#shader fragment

#version 330

uniform vec3 Color;

out vec4 fragColor;

void main()
{
    fragColor = vec4(Color, 1.0);
}