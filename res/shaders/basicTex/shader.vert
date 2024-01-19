#version 450 core

// position and texture coordinates
layout (location = 0) in vec3 in_Pos;
layout (location = 3) in vec2 in_Tex;

// texture coordinates
out VS_OUT
{
    vec2 tex;
} vs_out;

// projection, view and model matrices
layout (std140, binding = 1) uniform matrices
{
    mat4 proj;
    mat4 view;
};
uniform mat4 model;

void main()
{
    vs_out.tex = in_Tex;
    gl_Position = proj * view * model * vec4(in_Pos, 1.0f);
}