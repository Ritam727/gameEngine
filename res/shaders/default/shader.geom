#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec3 col;
    vec3 norm;
    vec3 fragPos;
    vec2 texCoords;
} gs_in[];

out GS_OUT
{
    vec3 col;
    vec3 norm;
    vec3 fragPos;
    vec2 texCoords;
} gs_out;

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gs_out.col = gs_in[i].col;
        gs_out.norm = gs_in[i].norm;
        gs_out.fragPos = gs_in[i].fragPos;
        gs_out.texCoords = gs_in[i].texCoords;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}