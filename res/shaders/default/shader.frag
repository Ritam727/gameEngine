#version 450 core

struct Material
{
    sampler2D diffuse[8];
    sampler2D specular[8];
    sampler2D emission[8];
    sampler2D normal[8];

    float shininess;

    int diffuseCount;
    int specularCount;
    int emissionCount;
    int normalCount;
};

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

in GS_OUT
{
    vec3 col;
    vec3 norm;
    vec3 fragPos;
    vec2 texCoords;
} fs_in;

out vec4 FragColor;

uniform vec3 cameraPos;
uniform Material material;
uniform BasicMaterial basicMaterial;
uniform vec3 u_Color;
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
    vec3 norm;
    if (material.normalCount > 0)
        norm = normalize(texture(material.normal[0], fs_in.texCoords).rgb);
    else
        norm = normalize(fs_in.norm);
    vec3 result = vec3(0.0f);
    vec3 viewDir = normalize(cameraPos - fs_in.fragPos);
    
    for (int i = 0; i < directionalLightCount; i++)
        result += dirLightIllumination(dirLight[i], norm, viewDir);
    
    for (int i = 0; i < pointLightCount; i++)
        result += pointLightIllumination(pointLights[i], norm, viewDir, fs_in.fragPos);
    
    for (int i = 0; i < spotLightCount; i++)
        result += spotLightIllumination(spotLight[i], norm, viewDir, fs_in.fragPos);

    for (int i = 0; i < material.emissionCount; i++)
        result += vec3(texture(material.emission[i], fs_in.texCoords));
    
    FragColor = vec4(result, 1.0f);
}

vec3 dirLightIllumination(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction.xyz);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    if (material.diffuseCount > 0)
    {
        for (int i = 0; i < material.diffuseCount; i++)
        {
            ambient += light.ambient.rgb * vec3(texture(material.diffuse[i], fs_in.texCoords));
            diffuse += light.diffuse.rgb * vec3(diff * texture(material.diffuse[i], fs_in.texCoords));
        }
    }
    else
    {
        ambient += light.ambient.rgb * basicMaterial.diffuse;
        diffuse += light.diffuse.rgb * (diff * basicMaterial.diffuse);
    }

    if (material.specularCount > 0)
    {
        for (int i = 0; i < material.specularCount; i++)
            specular += light.specular.rgb * (spec * vec3(texture(material.specular[i], fs_in.texCoords)));
    }
    else
    {
        specular += light.specular.rgb * (spec * basicMaterial.specular);
    }

    return (ambient + diffuse + specular);
}

vec3 pointLightIllumination(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    if (material.diffuseCount > 0)
    {
        for (int i = 0; i < material.diffuseCount; i++)
        {
            ambient += light.ambient.rgb * vec3(texture(material.diffuse[i], fs_in.texCoords));
            diffuse += light.diffuse.rgb * vec3(diff * texture(material.diffuse[i], fs_in.texCoords));
        }
    }
    else
    {
        ambient += light.ambient.rgb * basicMaterial.diffuse;
        diffuse += light.diffuse.rgb * (diff * basicMaterial.diffuse);
    }

    if (material.specularCount > 0)
    {
        for (int i = 0; i < material.specularCount; i++)
            specular += light.specular.rgb * (spec * vec3(texture(material.specular[i], fs_in.texCoords)));
    }
    else
    {
        specular += light.specular.rgb * (spec * basicMaterial.specular);
    }

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
    float spec = intensity * pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    if (material.diffuseCount > 0)
    {
        for (int i = 0; i < material.diffuseCount; i++)
        {
            ambient += light.ambient.rgb * vec3(texture(material.diffuse[i], fs_in.texCoords));
            diffuse += light.diffuse.rgb * vec3(diff * texture(material.diffuse[i], fs_in.texCoords));
        }
    }
    else
    {
        ambient += light.ambient.rgb * basicMaterial.diffuse;
        diffuse += light.diffuse.rgb * (diff * basicMaterial.diffuse);
    }

    if (material.specularCount > 0)
    {
        for (int i = 0; i < material.specularCount; i++)
            specular += light.specular.rgb * (spec * vec3(texture(material.specular[i], fs_in.texCoords)));
    }
    else
    {
        specular += light.specular.rgb * (spec * basicMaterial.specular);
    }

    return attenuation * (ambient + diffuse + specular);
}
