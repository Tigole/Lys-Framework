#ifndef _LYS_MODULE_FRAME_HPP
#define _LYS_MODULE_FRAME_HPP 1

#include <chrono>

namespace lys
{

class Frame
{
public:
    static void Initialize(void)
    {
        lastFramePoint  = std::chrono::high_resolution_clock::now();
        frameTime       = 0.0f;
        applicationTime = 0.0f;
        frameIdx        = 0;
    }

    /// Call at the begining of a new frame
    static void On_New_Frame(void)
    {
        frameTime =
            0.001f *
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - lastFramePoint).count();
        applicationTime += frameTime;
        lastFramePoint = std::chrono::high_resolution_clock::now();
        frameIdx++;
    }

    /// Get current frame time
    static float Get_Frame_Time(void)
    {
        return frameTime;
    }

    /// Get total application time since call to Initialize
    static float Get_Application_Time(void)
    {
        return applicationTime;
    }

    /// Get frame count since call to Initialize
    static uint32_t Get_Frame_Idx(void)
    {
        return frameIdx;
    }

private:
    inline static std::chrono::time_point<std::chrono::high_resolution_clock> lastFramePoint;
    inline static float frameTime;
    inline static float applicationTime;
    inline static uint32_t frameIdx;
};

}  // namespace lys

#endif  // _LYS_MODULE_FRAME_HPP
