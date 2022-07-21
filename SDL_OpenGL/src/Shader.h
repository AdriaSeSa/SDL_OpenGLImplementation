#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int programID;

    // constructor reads and builds the shader
    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);

    // Create Shader
    void CreateShader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void SetFloat3(const std::string& name, float v1, float v2, float v3) const;
    void SetFloat4(const std::string& name, float v1, float v2, float v3, float v4) const;
    void SetMatFloat4v(const std::string& name, const GLfloat* value);
    
};

#endif
