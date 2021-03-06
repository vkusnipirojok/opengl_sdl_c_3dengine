#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vertColor;
in vec2 texCoords;
out vec4 outColor;
in vec3 vertNormal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform bool wireframeMode;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(vertNormal);
    vec3 lightDir = normalize(FragPos - light.position);
    float diff_koef = max(dot(norm, -lightDir), 0.0f);
    vec3 diffuse = light.diffuse * (diff_koef * material.diffuse);

    // specular
    vec3 viewDir = normalize(FragPos - viewPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec_koef = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec_koef * material.specular);

    if(wireframeMode)
        outColor = vec4(vertColor, 1.0f);
    else
        outColor = texture(ourTexture, texCoords) * 
                   vec4(diffuse + ambient + specular, 1.0f);
}
