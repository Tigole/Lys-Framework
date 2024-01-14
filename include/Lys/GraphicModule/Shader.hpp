#ifndef _SHADER_HPP
#define _SHADER_HPP 1

#include "Lys/LysConfig.hpp"

#include <string>

#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace lys
{

class LYS_API Shader
{
public:
    Shader(const char* camera_uniform_name, const char* model_matrix_attribute_name);

    void mt_Use(void);
    bool mt_Create_From_File(const std::string& vertex_shader_file, const std::string& fragment_shader_file);
    bool mt_Create_From_String(const std::string& vertex_shader_code, const std::string& fragment_shader_code);

    const char* mt_Get_Camera_Uniform_Name(void) const;
    const char* mt_Get_Model_Matrix_Attribute_Name(void) const;

    void mt_Set_Uniform(const std::string& uniform_name, bool uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, int uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, unsigned int uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, float uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const sf::Color& uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const glm::vec2& uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const glm::vec3& uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const glm::vec4& uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const glm::mat2& uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const glm::mat3& uniform_value);
    void mt_Set_Uniform(const std::string& uniform_name, const glm::mat4& uniform_value);

private:

    bool mt_Compile_Shader(const std::string& shader_code, int shader_type, unsigned int& shader_id);
    bool mt_Check_Error(unsigned int id, const std::string& type);

    bool mt_Get_File_Content(const std::string& file, std::string& file_content) const;

    unsigned int m_Id = -1;
    const char* m_Camera_Uniform_Name = "";
    const char* m_Model_Matrix_Attribute_Name = "";
};

}


#endif // _SHADER_HPP
