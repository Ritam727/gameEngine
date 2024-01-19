#version 450 core

// position, color and normals are needed
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Col;
layout (location = 2) in vec3 in_Norm;

// color and normals need to forwarded to fragment shader
out VS_OUT
{
    vec3 pos;
    vec3 norm;
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
    vs_out.pos = in_Pos;
    vs_out.norm = mat3(transpose(inverse(model))) * in_Norm;
    gl_Position = proj * view * model * vec4(in_Pos, 1.0f);
}