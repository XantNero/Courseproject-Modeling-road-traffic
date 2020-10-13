#ifndef _SHADER_H_
#define _SHADER_H_
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererID;
    const std::string m_Path;
    std::unordered_map<std::string, int> cache;
public:
 
    Shader(const std::string& filePath);
    ~Shader();

    void bind() const;
    void unbind() const;
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
private:
    ShaderProgramSource ParseShader(const std::string &filePath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    int getUniformLocation(const std::string &name);
};

#endif