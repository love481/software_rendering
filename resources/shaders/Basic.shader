#shader vertex
#version 330

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textureCoord;

out vec3  vs_pos;
out vec3 vs_colour;
out vec2 vs_textureCoord;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main()
{
    vs_pos = vec4(modelMatrix * vec4(v_pos, 1.0f)).xyz;
    vs_textureCoord = v_textureCoord;
    gl_Position = projectionMatrix* viewMatrix*modelMatrix * vec4(v_pos, 1.0f);
};

#shader fragment
#version 330

in vec3  vs_pos;
in vec3 vs_colour;
in vec2 vs_textureCoord;
out vec4 colour;
uniform sampler2D texture_diffuse;
uniform DirectionalLight directionalLight;
struct DirectionalLight
{
    vec3 colour;
    float ambientIntensity;
    
};

void main()
{
    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
    colour = texture(texture_diffuse, vs_textureCoord) * ambientColour;
};
