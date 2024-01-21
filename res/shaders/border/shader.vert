#version 450 core

// only need color and position of vertex
layout (location = 0) in vec3 in_Pos;

// projection, view and model matrices are needed
layout (std140, binding = 1) uniform matrices
{
    mat4 proj;
    mat4 view;
};
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(in_Pos, 1.0f);
}