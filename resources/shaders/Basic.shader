#shader vertex
#version 330

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textureCoord;
layout(location = 2) in vec3 norm;


out vec3  vs_pos;
out vec3 vs_colour;
out vec2 vs_textureCoord;
out vec3 Normal;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix; 
uniform mat4 projectionMatrix;


void main()
{
    vs_pos = vec4(modelMatrix * vec4(v_pos, 1.0f)).xyz;
    vs_textureCoord = v_textureCoord;
    gl_Position = projectionMatrix* viewMatrix*modelMatrix * vec4(v_pos, 1.0f);

    Normal = mat3(transpose(inverse(modelMatrix))) * norm;
};

#shader fragment
#version 330

in vec3 vs_pos;
in vec3 vs_colour;
in vec2 vs_textureCoord;
in vec3 Normal;


out vec4 colour;

struct DirectionalLight
{
    vec3 colour;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

uniform sampler2D texture_diffuse;
uniform DirectionalLight directionalLight;


void main()
{

    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
    colour = texture(texture_diffuse, vs_textureCoord) * (ambientColour + diffuseColour); 
};
