#include "f4.h"

RT_F4_API			f4_sub(RT_F4_API a, RT_F4_API b)
{
	return ((RT_F4_API){
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
			a.w - b.w
	});
}