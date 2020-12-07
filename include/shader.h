#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_
#include"defines.h"
enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
struct shaderSources {
    string vShader;
    string fShader;
};
class shader {
    unsigned int shaderId, uniformAmbientIntensity, uniformAmbientColour;
    shaderSources ParseShader(const string&);
    void addShader( const char*, GLenum);
    void compileShader(const string&);
public:
    shader(const string& filePath){ this->compileShader(filePath); }
    ~shader(){glDeleteProgram(this->shaderId);}
    void use() { glUseProgram(shaderId); }
    unsigned int getProgramId() { return shaderId; }
    void setBool(const string&, bool) const;
    void setInt(const string&, int) const;
    void setFloat(const string&, float) const;
    void setVec2(const string&, const glm::vec2&) const;
    void setVec2(const string&, float, float) const;
    void setVec3(const string&, const glm::vec3&) const;
    void setVec3(const string&, float, float, float) const;
    void setVec4(const string&, const glm::vec4&) const;
    void setVec4(const string&, float , float , float , float) const;
    void setMat2(const string&, const glm::mat2& mat) const;
    void setMat3(const string&, const glm::mat3& mat) const;
    void setMat4(const string&, const glm::mat4& mat) const;
    unsigned int GetAmbientIntensityLocation();
    unsigned int GetAmbientColourLocation();
};
#endif
