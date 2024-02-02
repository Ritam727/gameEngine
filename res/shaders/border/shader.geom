#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

vec3 getNormal();

in VS_OUT
{
	vec3 cen;
} gs_in[];

void main()
{
	for (int i = 0; i < 3; i++)
	{
		vec3 dir = normalize(vec3(gl_in[i].gl_Position) - gs_in[i].cen);
		gl_Position = gl_in[i].gl_Position + vec4(1.0f, 0.0f, 0.0f, 0.0f) * 0.02;
		EmitVertex();
	}
	for (int i = 0; i < 3; i++)
	{
		vec3 dir = normalize(vec3(gl_in[i].gl_Position) - gs_in[i].cen);
		gl_Position = gl_in[i].gl_Position - vec4(1.0f, 0.0f, 0.0f, 0.0f) * 0.02;
		EmitVertex();
	}

	for (int i = 0; i < 3; i++)
	{
		vec3 dir = normalize(vec3(gl_in[i].gl_Position) - gs_in[i].cen);
		gl_Position = gl_in[i].gl_Position + vec4(0.0f, 1.0f, 0.0f, 0.0f) * 0.02;
		EmitVertex();
	}
	for (int i = 0; i < 3; i++)
	{
		vec3 dir = normalize(vec3(gl_in[i].gl_Position) - gs_in[i].cen);
		gl_Position = gl_in[i].gl_Position - vec4(0.0f, 1.0f, 0.0f, 0.0f) * 0.02;
		EmitVertex();
	}

	for (int i = 0; i < 3; i++)
	{
		vec3 dir = normalize(vec3(gl_in[i].gl_Position) - gs_in[i].cen);
		gl_Position = gl_in[i].gl_Position + vec4(0.0f, 0.0f, 1.0f, 0.0f) * 0.02;
		EmitVertex();
	}
	for (int i = 0; i < 3; i++)
	{
		vec3 dir = normalize(vec3(gl_in[i].gl_Position) - gs_in[i].cen);
		gl_Position = gl_in[i].gl_Position - vec4(0.0f, 0.0f, 1.0f, 0.0f) * 0.02;
		EmitVertex();
	}

	EndPrimitive();
}