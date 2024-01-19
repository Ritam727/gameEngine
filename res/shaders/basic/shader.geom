#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec3 col;
} gs_in[];

out GS_OUT
{
	vec3 col;
} gs_out;

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gs_out.col = gs_in[i].col;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}