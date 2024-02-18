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
	for (float x = -1.0f; x < 2.0f; x += 2.0f)
	{
		for (float y = -1.0f; y < 2.0f ; y += 2.0f)
		{
			for (float z = -1.0f; z < 2.0f; z += 2.0f)
			{
				for (int i = 0; i < 3; i++)
				{
					gl_Position = gl_in[i].gl_Position + vec4(x, y, z, 0.0f) * 0.02;
					EmitVertex();
				}
			}
		}
	}

	EndPrimitive();
}