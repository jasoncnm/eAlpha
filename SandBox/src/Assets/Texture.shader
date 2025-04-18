#shader vertex

#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;


uniform mat4 VP;
uniform mat4 Trans;

out vec2 _TexCoord;

void main()
{
    _TexCoord = texCoord;
    gl_Position = VP * Trans * vec4(position, 1.0);
}


#shader fragment

#version 330

in vec2 _TexCoord;

uniform sampler2D _Texture;

out vec4 fragColor;

void main()
{
    fragColor = texture(_Texture, _TexCoord);
}