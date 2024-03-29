#ifndef _LYS_RENDERER_HPP
#define _LYS_RENDERER_HPP 1

#include "Lys/LysConfig.hpp"
#include "Lys/Core/Core.hpp"
#include "Lys/MathModule/Rect.hpp"
#include "Lys/GraphicModule/Shader.hpp"
#include "Lys/GraphicModule/VertexArray.hpp"

#include "glm/glm.hpp"
#include <map>

#include <memory>
#include <SFML/Graphics.hpp>

#include <memory>

namespace sf
{

class RenderWindow;

}

namespace lys
{

class Window;

struct LineSettings;
struct RectangleSettings;
struct CircleSettings;
struct HexagonSettings;
struct Sprite;
namespace gui
{
struct TextSettings;
}
struct VertexArray;
struct TextureData;
struct Texture;
struct Material;
struct Shader;
class Camera;

class LYS_API Renderer
{
    LYS_CLASS_NO_COPY(Renderer)
public:
    ~Renderer();

    static void smt_Create(Window* wnd);
    static void smt_Destroy(void);
    static Renderer& smt_Get(void);

public:

    void mt_Set_Camera(Camera* camera);
    void mt_Begin_Scene(float elapsed_time);

    void mt_End_Scene(void);

    void mt_Draw_Line(const LineSettings& line_settings);
    void mt_Draw_Rectangle(const RectangleSettings& rectangle_settings);
    void mt_Draw_Circle(const CircleSettings& circle_settings);
    void mt_Draw_Hexagon(const HexagonSettings& hexagon_settings);
    Rectf mt_Draw_Text(const char* text, const Vector2f& screen_pos, const gui::TextSettings& text_settings);
    void mt_Draw_VertexArray(VertexArray* va, Material* material, const glm::mat4& model_matrix);
    void mt_Draw_VertexArray(const sf::VertexArray& va, const Texture* texture);

    const sf::Font& mt_Get_Default_Font(void) const;
    Shader& mt_Get_Default_Shader(void);

    sf::RenderWindow& mt_Get_SFML_RenderWindow(void) {return *m_Wnd;}

    std::unique_ptr<VertexBuffer> m_Instanced_Buffer;

private:

    Camera* m_Camera = nullptr;

    void mt_Set_Texture(sf::Shape& s, const TextureData& data);

    sf::RenderWindow* m_Wnd;

    sf::Font m_Default_Font;
    Shader m_Default_Shader;

    static std::unique_ptr<Renderer> sm_Renderer;
    Renderer(Window* wnd);


    std::map<std::pair<VertexArray*, Material*>, std::vector<glm::mat4>> m_Mesh_Material_Render_Buffer = {};
    void mt_Flush_Mesh_Material(void);

    template<typename T>
    inline void mt_Send_To_Shader(Shader* s, std::map<std::string, T>& m);
};

}

#endif // _LYS_RENDERER_HPP
