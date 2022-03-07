#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H

#include <optional>

namespace ShaderUtils
{

    enum Type
    {
        FRAGMENT_SHADER_TYPE,
        VERTEX_SHADER_TYPE,
    };

    struct Program
    {

    private:
        std::optional<unsigned int> vertexShader = std::nullopt;
        std::optional<unsigned int> fragmentShader = std::nullopt;
        std::optional<unsigned int> program = std::nullopt;
        bool registered = false;

    public:
        Program();
        ~Program();
        bool registerShader(const Type shader_type, const char *shader_source);
        bool registerProgram();
        std::optional<unsigned int> getProgram() const;
        bool programIsRegistered() const;
    };

}

#endif /* SHADER_UTILS_H */
