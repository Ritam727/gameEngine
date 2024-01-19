#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec2 tex;
} gs_in[];

out GS_OUT
{
    vec2 tex;
} gs_out;

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gs_out.tex = gs_in[i].tex;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}