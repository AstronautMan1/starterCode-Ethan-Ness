#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_TexCoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

uniform vec4 lightPosWorld;
uniform vec4 cameraPosWorld;

out vec4 normal;
out vec4 lightDir;
out vec4 viewDir;
out vec2 tCoord;

void main(void)
{
  vec4 vertexWorldPos = modelMatrix * vec4(in_Position, 1.0);
  
  normal = normalize(normalMatrix * vec4(in_Normal, 0.0));
  lightDir = normalize(lightPosWorld - vertexWorldPos);
  viewDir = normalize(cameraPosWorld - vertexWorldPos);
  
  // Pass the texture coordinate to the fragment shader
  tCoord = in_TexCoord;

  gl_Position = projMatrix * viewMatrix * vertexWorldPos;
}








