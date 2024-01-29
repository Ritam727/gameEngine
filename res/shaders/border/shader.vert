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
uniform vec3 centre;

out VS_OUT
{
    vec3 cen;
} vs_out;

void main()
{
    gl_Position = proj * view * model * vec4(in_Pos, 1.0f);
    vs_out.cen = vec3(proj * view * model * vec4(centre, 1.0f));
}