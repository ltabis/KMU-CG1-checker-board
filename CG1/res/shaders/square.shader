#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
out vec3 out_Color;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * position;
	out_Color = color;
};

#shader FRAGMENT color
#version 330 core
layout(location = 0) out vec4 color;

in vec3 out_Color;

void main()
{
	color = vec4(out_Color, 1.0);
};