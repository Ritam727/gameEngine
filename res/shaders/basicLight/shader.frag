#version 450 core

struct BasicMaterial
{
    vec3 diffuse;
    vec3 specular;
    vec3 emission;

    float shininess;
};

struct DirLight
{
    vec4 direction;     // 4 * 4 = 16

    vec4 ambient;       // 4 * 4 = 16
    vec4 diffuse;       // 4 * 4 = 16
    vec4 specular;      // 4 * 4 = 16
                        // 16 + 16 + 16 + 16 = 64
    // padded size = (64 / 16) * 16 = 64
};

struct PointLight
{
    vec4 position;      // 4 * 4 = 16

    vec4 ambient;       // 4 * 4 = 16
    vec4 diffuse;       // 4 * 4 = 16
    vec4 specular;      // 4 * 4 = 16

    float constant;     // 4
    float linear;       // 4
    float quadratic;    // 4
                        // 16 * 4 + 4 * 3 = 76
    // padded size = (76 / 16 + 1) * 16 = 80
};

struct SpotLight
{
    vec4 position;      // 4 * 4 = 16
    vec4 direction;     // 4 * 4 = 16
    vec4 ambient;       // 4 * 4 = 16
    vec4 diffuse;       // 4 * 4 = 16
    vec4 specular;      // 4 * 4 = 16

    float constant;     // 4
    float linear;       // 4
    float quadratic;    // 4

    float innerCutOff;  // 4
    float outerCutOff;  // 4
                        // 16 * 5 + 4 * 5 = 100
    // padded size = (100 / 16 + 1) * 16 = 112
};

vec3 dirLightIllumination(DirLight dirLight, vec3 normal, vec3 viewDir);
vec3 pointLightIllumination(PointLight pointLight, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 spotLightIllumination(SpotLight spotLight, vec3 normal, vec3 viewDir, vec3 fragPos);

#define N_POINT_LIGHTS 20
#define N_DIRECTIONAL_LIGHTS 1
#define N_SPOT_LIGHTS 5

in VS_OUT
{
    vec3 pos;
    vec3 norm;
} fs_in;

out vec4 color;

uniform vec3 cameraPos;
uniform BasicMaterial basicMaterial;
layout (std140, binding = 0) uniform Lights
{
    DirLight dirLight[N_DIRECTIONAL_LIGHTS];                        // 64 * 6
    PointLight pointLights[N_POINT_LIGHTS];                         // 80 * 20
    SpotLight spotLight[N_SPOT_LIGHTS];                             // 112 * 5
    int directionalLightCount;                                      // 4
    int pointLightCount;                                            // 4
    int spotLightCount;                                             // 4
    // total size = 64 * 1 + 112 * 5 + 80 * 20 + 4 * 3 = 2506
};

void main()
{
    vec3 norm = normalize(fs_in.norm);
    vec3 viewDir = normalize(cameraPos - fs_in.pos);
    vec3 result;
    
    for (int i = 0; i < directionalLightCount; i++)
        result += dirLightIllumination(dirLight[i], norm, viewDir);
    
    for (int i = 0; i < pointLightCount; i++)
        result += pointLightIllumination(pointLights[i], norm, viewDir, fs_in.pos);
    
    for (int i = 0; i < spotLightCount; i++)
        result += spotLightIllumination(spotLight[i], norm, viewDir, fs_in.pos);

    result += basicMaterial.emission;
    
    color = vec4(result, 1.0f);
}

vec3 dirLightIllumination(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction.xyz);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), basicMaterial.shininess);

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    ambient += light.ambient.rgb * basicMaterial.diffuse;
    diffuse += light.diffuse.rgb * (diff * basicMaterial.diffuse);

    specular += light.specular.rgb * (spec * basicMaterial.specular);

    return (ambient + diffuse + specular);
}

vec3 pointLightIllumination(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), basicMaterial.shininess);
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    ambient += light.ambient.rgb * basicMaterial.diffuse;
    diffuse += light.diffuse.rgb * (diff * basicMaterial.diffuse);

    specular += light.specular.rgb * (spec * basicMaterial.specular);

    return attenuation * (ambient + diffuse + specular);
}

vec3 spotLightIllumination(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    float theta = dot(lightDir, normalize(-light.direction.xyz));
    float epsilon = (light.innerCutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f ,1.0f);
    
    float diff = intensity * max(dot(lightDir, normal), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = intensity * pow(max(dot(reflectDir, viewDir), 0.0f), basicMaterial.shininess);
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    ambient += light.ambient.rgb * basicMaterial.diffuse;
    diffuse += light.diffuse.rgb * (diff * basicMaterial.diffuse);

    specular += light.specular.rgb * (spec * basicMaterial.specular);

    return attenuation * (ambient + diffuse + specular);
}
