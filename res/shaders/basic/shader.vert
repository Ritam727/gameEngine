#version 450 core

// only need color and position of vertex
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Col;

// only need to pass on color of vertex
out VS_OUT
{
    vec3 col;
} vs_out;

// projection, view and model matrices are needed
layout (std140, binding = 1) uniform matrices
{
    mat4 proj;
    mat4 view;
};
uniform mat4 model;

void main()
{
    vs_out.col = in_Col;
    gl_Position = proj * view * model * vec4(in_Pos, 1.0f);
}