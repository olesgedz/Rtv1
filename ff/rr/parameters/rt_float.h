#ifndef CL_FLOAT_H
# define CL_FLOAT_H

# define _RT_PI			3.14159265358979323846264338327950288
# define _RT_PI_2		1.57079632679489661923132169163975144
# define _RT_PI_4		0.785398163397448309615660845819875721
# define _RT_1_PI		0.318309886183790671537767526745028724
# define _RT_2_PI		0.636619772367581343075535053490057448

# define RT_FLOAT

# ifdef RT_FLOAT
#  define RT_F			float
#  define RT_F4			float4
#  define RT_F4_API		cl_float4
#  define RT_SQRT		sqrt
#  define RT_SIN		sin
#  define RT_COS		cos
#  define RT_MIN		fmin
#  define RT_MAX		fmax
#  define RT_PI			(float)_RT_PI
#  define RT_PI_2		(float)_RT_PI_2
#  define RT_PI_4		(float)_RT_PI_4
#  define RT_1_PI		(float)_RT_1_PI
#  define RT_2_PI		(float)_RT_2_PI
# endif

# ifdef RT_DOUBLE
#  define RT_F			double
#  define RT_F4			double4
#  define RT_F4_API		cl_double4
#  define RT_SQRT		sqrt
#  define RT_SIN		sin
#  define RT_COS		cos
#  define RT_MIN		fmin
#  define RT_MAX		fmax
#  define RT_PI			_RT_PI
#  define RT_PI_2		_RT_PI_2
#  define RT_PI_4		_RT_PI_4
#  define RT_1_PI		_RT_1_PI
#  define RT_2_PI		_RT_2_PI
# endif


#endif
