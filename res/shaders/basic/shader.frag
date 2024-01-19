#version 450 core

// output from vertex shader
in GS_OUT
{
    vec3 col;
} fs_in;

// output to screen
out vec4 color;

void main()
{
    color = vec4(fs_in.col, 1.0f);
}