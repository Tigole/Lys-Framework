#ifndef _CAMERA_HPP
#define _CAMERA_HPP 1

#include "Lys/LysConfig.hpp"
#include "Lys/MathModule/Vector2.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include <SFML/Graphics.hpp>

namespace lys
{

struct LYS_API CameraData
{
    CameraData() {}
    CameraData(float fov, const lys::Vector2u& window_size, float near, float far)
     :  m_fov(fov),
        m_aspect(static_cast<float>(window_size.x) / window_size.y),
        m_frustum_near(near),
        m_frustum_far(far)
    {}

    float m_fov = glm::radians(45.0f);
    float m_aspect = 1920.0f / 1080.0f;
    float m_frustum_near = 0.01f;
    float m_frustum_far = 1000.0f;
};

enum class CameraDirection
{
    None,
    Up,
    Down,
    Left,
    Right,
    Fwd,
    Back,
};

struct LYS_API CameraControl
{
    sf::Vector2i m_Old_Mouse_Pos;
    float m_Pitch_Magnitude;
    float m_Yaw_Magnitude;
    float m_Mouvement_Speed;
    glm::vec3 m_Direction;
};

class LYS_API Camera
{
public:

    Camera();

    void mt_Set_Data(const CameraData& data);
    void mt_Set(const glm::vec3& position, float pitch, float yaw);
    glm::mat4 mt_Get_ViewProjection_Matrix(void) const;
    glm::mat4 mt_Get_View_Matrix(void) const;
    glm::mat4 mt_Get_Projection_Matrix(void) const;
    glm::vec3 mt_Get_Position(void) const;
    glm::vec3 mt_Get_Fwd() const;
    glm::vec3 mt_Get_Up() const;
    glm::vec3 mt_Get_Right() const;
    const CameraData& mt_Get_Data(void);

    float mt_Get_Yaw(void) const;
    float mt_Get_Pitch(void) const;

    void mt_MoveBy(CameraDirection direction, float magnitude);
    void mt_MoveBy(const glm::vec3& direction);
    void mt_Rotate(float x_pitch, float y_yaw);


private:

    void mt_Recalculate_Perspective(void);

    void mt_Update_Vectors(void);

    CameraData m_Data = {};
    glm::vec3 m_Position = {0.0f, 0.0f, 10.0f};
    glm::vec3 m_Fwd_Dir = {0.0f, 0.0f, -1.0f};
    glm::vec3 m_Up_Dir = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_Right_Dir = {1.0f, 0.0f, 0.0f};
    glm::vec3 m_World_Up = {0.0f, 1.0f, 0.0f};
    glm::mat4 m_Perspective_Matrix = {};
    float m_Pitch = 0.0f;
    float m_Yaw = -90.0f;
};

}

#endif // _CAMERA_HPP
