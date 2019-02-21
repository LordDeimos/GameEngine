#version 410
layout (triangles) in;
layout (triangle_strip) out;

void main(){
    gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}