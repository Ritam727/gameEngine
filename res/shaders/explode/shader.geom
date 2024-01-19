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

uniform float time;

vec3 getNormal();
vec4 explode(vec4 position, vec3 normal);

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gs_out.col = gs_in[i].col;
        gs_out.norm = gs_in[i].norm;
        gs_out.fragPos = gs_in[i].fragPos;
        gs_out.texCoords = gs_in[i].texCoords;
		gl_Position = explode(gl_in[i].gl_Position, getNormal());
		EmitVertex();
	}

	EndPrimitive();
}

vec3 getNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
	float magnitude = 2.0f;
	vec3 direction = normal * magnitude * (sin(time) + 1.0f) / 2.0f;
	return position + vec4(direction, 0.0f);
}