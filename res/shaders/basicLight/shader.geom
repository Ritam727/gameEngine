#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec3 pos;
    vec3 norm;
} gs_in[];

out GS_OUT
{
    vec3 pos;
    vec3 norm;
} gs_out;

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gs_out.pos = gs_in[i].pos;
        gs_out.norm = gs_in[i].norm;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}