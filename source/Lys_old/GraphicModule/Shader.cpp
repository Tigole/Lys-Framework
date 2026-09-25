#include "Lys/GraphicModule/Shader.hpp"
#include "Lys/Core/Log.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

namespace lys
{

Shader::Shader(const char* camera_uniform_name, const char* model_matrix_attribute_name) :
    m_Camera_Uniform_Name(camera_uniform_name),
    m_Model_Matrix_Attribute_Name(model_matrix_attribute_name)
{}

void Shader::mt_Use(void)
{
    glUseProgram(m_Id);
}

bool Shader::mt_Create_From_File(const std::string& vertex_shader_file, const std::string& fragment_shader_file)
{
    std::string l_Vertex_Shader_Code;
    std::string l_Fragment_Shader_Code;

    if (mt_Get_File_Content(vertex_shader_file, l_Vertex_Shader_Code) == false)
    {
        LYS_LOG_CORE_ERROR("Failed to get vertex shader code");
        return false;
    }
    if (mt_Get_File_Content(fragment_shader_file, l_Fragment_Shader_Code) == false)
    {
        LYS_LOG_CORE_ERROR("Failed to get vertex shader code");
        return false;
    }

    return mt_Create_From_String(l_Vertex_Shader_Code, l_Fragment_Shader_Code);
}

bool Shader::mt_Create_From_String(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
{
    bool l_b_Ret;
    unsigned int l_vertex_shader;
    unsigned int l_fragment_shader;

    mt_Compile_Shader(vertex_shader_code, GL_VERTEX_SHADER, l_vertex_shader);
    mt_Compile_Shader(fragment_shader_code, GL_FRAGMENT_SHADER, l_fragment_shader);

    m_Id = glCreateProgram();
    glAttachShader(m_Id, l_vertex_shader);
    glAttachShader(m_Id, l_fragment_shader);
    glLinkProgram(m_Id);

    l_b_Ret = mt_Check_Error(m_Id, "PROGRAM");

    glDeleteShader(l_vertex_shader);
    glDeleteShader(l_fragment_shader);

    return l_b_Ret;
}

const char* Shader::mt_Get_Camera_Uniform_Name(void) const
{
    return m_Camera_Uniform_Name;
}

const char* Shader::mt_Get_Model_Matrix_Attribute_Name(void) const
{
    return m_Model_Matrix_Attribute_Name;
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, bool uniform_value)
{
    glUniform1i(glGetUniformLocation(m_Id, uniform_name.c_str()), uniform_value);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, int uniform_value)
{
    glUniform1i(glGetUniformLocation(m_Id, uniform_name.c_str()), uniform_value);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, unsigned int uniform_value)
{
    glUniform1ui(glGetUniformLocation(m_Id, uniform_name.c_str()), uniform_value);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, float uniform_value)
{
    glUniform1f(glGetUniformLocation(m_Id, uniform_name.c_str()), uniform_value);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const sf::Color& uniform_value)
{
    glm::vec3 l_vec;
    l_vec.r = uniform_value.r / 255.0f;
    l_vec.g = uniform_value.g / 255.0f;
    l_vec.b = uniform_value.b / 255.0f;
    mt_Set_Uniform(uniform_name, l_vec);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const glm::vec2& uniform_value)
{
    glUniform2fv(glGetUniformLocation(m_Id, uniform_name.c_str()), 1, &uniform_value[0]);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const glm::vec3& uniform_value)
{
    glUniform3fv(glGetUniformLocation(m_Id, uniform_name.c_str()), 1, &uniform_value[0]);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const glm::vec4& uniform_value)
{
    glUniform4fv(glGetUniformLocation(m_Id, uniform_name.c_str()), 1, &uniform_value[0]);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const glm::mat2& uniform_value)
{
    glUniformMatrix2fv(glGetUniformLocation(m_Id, uniform_name.c_str()), 1, GL_FALSE, &uniform_value[0][0]);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const glm::mat3& uniform_value)
{
    glUniformMatrix3fv(glGetUniformLocation(m_Id, uniform_name.c_str()), 1, GL_FALSE, &uniform_value[0][0]);
}

void Shader::mt_Set_Uniform(const std::string& uniform_name, const glm::mat4& uniform_value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, uniform_name.c_str()), 1, GL_FALSE, &uniform_value[0][0]);
}

bool Shader::mt_Compile_Shader(const std::string& shader_code, int shader_type, unsigned int& shader_id)
{
    bool l_b_Ret(false);
    const char* l_shader_code_c_str = shader_code.c_str();

    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &l_shader_code_c_str, nullptr);
    glCompileShader(shader_id);
    return mt_Check_Error(shader_id, "SHADER");
}

bool Shader::mt_Check_Error(unsigned int id, const std::string& type)
{
    bool l_b_Ret;
    GLchar l_buffer[512];
    int l_success;

    l_b_Ret = true;
    if (type == "PROGRAM")
    {
        glGetProgramiv(id, GL_LINK_STATUS, &l_success);
        if (l_success == 0)
        {
            glGetProgramInfoLog(id, sizeof(l_buffer), nullptr, l_buffer);
            std::cerr << "Linking failed: " << l_buffer << '\n';
        }
    }
    else
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &l_success);
        if (l_success == 0)
        {
            glGetShaderInfoLog(id, sizeof(l_buffer), nullptr, l_buffer);
            std::cerr << "Compilation failed: " << l_buffer << '\n';
            l_b_Ret = false;
        }
    }

    return l_b_Ret;
}

bool Shader::mt_Get_File_Content(const std::string& file, std::string& file_content) const
{
    std::ifstream l_Input_File;
    std::string l_File_Content;
    std::stringstream l_Buffer;

    l_Input_File.open(file);

    if (l_Input_File.is_open() == false)
    {
        LYS_LOG_CORE_ERROR("Failed to open file '%s'", file.c_str());
        return false;
    }

    l_Buffer << l_Input_File.rdbuf();
    file_content = l_Buffer.str();

    return true;
}

}
