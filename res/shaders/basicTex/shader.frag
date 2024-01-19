#version 450 core

struct Material
{
    sampler2D diffuse[32];
    sampler2D specular[32];
    sampler2D emission[32];
    sampler2D normal[32];

    float shininess;

    int diffuseCount;
    int specularCount;
    int emissionCount;
    int normalCount;
};

in GS_OUT
{
    vec2 tex;
} fs_in;

out vec4 color;

uniform Material material;

void main()
{
    color = texture(material.diffuse[0], fs_in.tex);
}