#ifndef _LYS_MATH_CORE_HPP
#define _LYS_MATH_CORE_HPP 1

#include "Lys/LysConfig.hpp"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif // M_PI

#define POW_2(x) (x*x)
#define DEG_TO_RAD(deg) (deg * M_PI / 180.0)

namespace lys
{

float LYS_API fn_Lerp(float a, float b, float t);

}

#endif // _LYS_MATH_CORE_HPP
