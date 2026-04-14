#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent, ks;
uniform float phongExp;

// uniform sampler2DRect textureUnit;
uniform sampler2D textureUnit;

in vec4 normal;
in vec4 lightDir;
in vec4 viewDir;
in vec2 tCoord;

void main(void)
{
  vec4 n = normalize(normal);
  vec4 l = normalize(lightDir);
  vec4 v = normalize(viewDir);
  
  vec4 halfVector = normalize(v + l);
  
  float val = max(0.0, dot(n, l));

  vec3 texel = texture(textureUnit, tCoord).rgb;
  vec3 finalDiffuse = diffuseComponent.rgb * texel;

  vec3 diffuse = vec3( finalDiffuse.r * val, finalDiffuse.g * val, finalDiffuse.b * val );

  vec3 specular = ks * pow(max(0.0, dot(n, halfVector)), phongExp);

  vec3 finalColor = diffuse + specular;
  // vec3 finalColor = texel;
  fragmentColor = vec4(finalColor, 1.0);
}
