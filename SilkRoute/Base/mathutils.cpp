#include <SilkRoute/Base/mathutils.h>

#include <math.h>

double round2dp(double val)
{
    // Multiply pre-rounded value by 100 and then divide rounded by a value
    // 100, effectively rounding to 2 d.p.
    return round(val * 100) / 100;
}
