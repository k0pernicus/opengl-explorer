#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

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
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int program = 0;
        bool registered = false;

    public:
        Program();
        ~Program();
        unsigned int registerShader(const Type shader_type, const char *shader_source);
        bool registerProgram();
        unsigned int getProgram() const;
        bool programIsRegistered() const;
    };

}

#endif /* SHADER_UTILS_H */
