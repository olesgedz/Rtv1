#include "f4.h"

RT_F4_API			f4_mul(RT_F4_API v, RT_F f)
{
	return ((RT_F4_API){
			v.x * f,
			v.y * f,
			v.z * f,
			v.w * f
	});
}