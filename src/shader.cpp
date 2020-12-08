#include"shader.h"
 shaderSources shader:: ParseShader(const string& filePath)
{   ifstream stream(filePath);
    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }

    }
    return { ss[0].str(),ss[1].str() };
}
void shader:: addShader(const char* shaderCode, GLenum shaderType)
{
    int theShader = glCreateShader(shaderType);
    const char* theCode;
    theCode = shaderCode;
    int codeLength;
    codeLength = strlen(theCode);
    glShaderSource(theShader, 1, &theCode, &codeLength);
    glCompileShader(theShader);
    int result = 0;
    char eLog[1024] = { 0 };
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        cout << "Error  compiling " << shaderType << "shader:" << eLog << endl;
        return;
    }
    glAttachShader(shaderId, theShader);
}

void shader:: compileShader(const string& filePath)
{
    shaderId = glCreateProgram();
    if (!shaderId) {
        cout << "error in creating shader" << endl;
    }
    shaderSources source = ParseShader("resources/shaders/Basic.shader");
    addShader( source.vShader.c_str(), GL_VERTEX_SHADER);
    addShader(source.fShader.c_str(), GL_FRAGMENT_SHADER);

    int result = 0;
    char eLog[1024] = { 0 };
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
        cout << "Error Linking Program:" << eLog << endl;
        return;
    }
    glValidateProgram(shaderId);
    glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
        cout << "Error validate Program:" << eLog << endl;
        return;
    }

    uniformAmbientColour = glGetUniformLocation(shaderId, "directionalLight.colour");
    uniformAmbientintensity = glGetUniformLocation(shaderId,"directionalLight.ambientIntensity");

    uniformDirection = glGetUniformLocation(shaderId, "directionalLight.direction"); 
    uniformDiffuseIntensity = glGetUniformLocation(shaderId, "directionalLight.diffuseIntensity");
}
void shader::setBool(const string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}
void shader:: setInt(const string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}
void shader:: setFloat(const string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}
void  shader::setVec2(const string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}
void shader::setVec2(const string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderId, name.c_str()), x, y);
}
void shader::setVec3(const string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}
void shader:: setVec3(const string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderId, name.c_str()), x, y, z);
}
void shader::setVec4(const string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}
void shader::setVec4(const string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(shaderId, name.c_str()), x, y, z, w);
}
void shader:: setMat2(const string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void shader::setMat3(const string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void shader::setMat4(const string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

unsigned int shader::GetAmbientIntensityLocation()
{
    return uniformAmbientintensity;
}

unsigned int shader::GetAmbientColourLocation()
{
    return uniformAmbientColour;
}

unsigned int shader::GetDirectionLocation()
{
    return uniformDirection;
}

unsigned int shader::GetDiffuseIntensityLocation()
{
    return uniformDiffuseIntensity;
}
