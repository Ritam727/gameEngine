#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec3 aNorm;
layout(location = 3) in vec2 aTex;

out VS_OUT
{
    vec3 col;
    vec3 norm;
    vec3 fragPos;
    vec2 texCoords;
} vs_out;

layout (std140, binding = 1) uniform matrices
{
    mat4 proj;
    mat4 view;
};
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
    vs_out.fragPos = vec3(model * vec4(aPos, 1.0f));
    vs_out.col = aCol;
    vs_out.norm = mat3(transpose(inverse(model))) * aNorm;
    vs_out.texCoords = aTex;
}