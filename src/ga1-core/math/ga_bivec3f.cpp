#include "ga_bivec3f.h"
#include "ga_vec3f.h"

ga_bivec3f ga_wedge_product(ga_vec3f a, ga_vec3f b) {
    ga_bivec3f result;
    result.yz = a.y * b.z - a.z * b.y;
    result.zx = a.z * b.x - a.x * b.z;
    result.xy = a.x * b.y - a.y * b.x;
    return result;
}
