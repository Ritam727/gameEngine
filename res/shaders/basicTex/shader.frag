#version 450 core

struct Material
{
    sampler2D diffuse[1];
    sampler2D specular[1];
    sampler2D emission[1];
    sampler2D normal[1];

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