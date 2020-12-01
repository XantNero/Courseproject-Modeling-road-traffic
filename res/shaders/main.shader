#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 a_color;

uniform mat4 u_ViewProjectionMatrix;

out vec3 v_color;

void main()
{
    gl_Position = u_ViewProjectionMatrix * position;
    v_color = a_color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_color;

void main()
{
    color = vec4(v_color, 1.0);
}