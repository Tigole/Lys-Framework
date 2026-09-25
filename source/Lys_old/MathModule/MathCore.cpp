#include "Lys/MathModule/MathCore.hpp"

namespace lys
{

float fn_Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

}
