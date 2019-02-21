#version 330 core
in vec3 OutColor;
out vec4 FragColour;
void main(){
	FragColour = vec4(OutColor,1.0);
}