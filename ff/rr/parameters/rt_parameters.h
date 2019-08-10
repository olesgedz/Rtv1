#ifndef OPTIONS_H
# define OPTIONS_H

# include "rt_float.h"

# define OBJECT_DATA_CAPACITY		32

# define SCENE_OBJECTS_CAPACITY		16

# define GI_DEFAULT_WIDTH			480
# define GI_DEFAULT_HEIGHT			480

# define INTERSECTION_MAX			INFINITY

#ifdef RT_FLOAT
#  define INTERSECTION_MIN			0.0001
#endif

#ifdef RT_DOUBLE
#  define INTERSECTION_MIN			0.000001
#endif

# define CL_PATH_DEPTH				1
# define CL_SAMPLES					2
# define CL_RUSSIAN_DEPTH			10
# define CL_SRGB					0
# define CL_LIGHT_PB				1
# define CL_LIGHT_EXPLICIT			1

# define RT_DEBUG					0
# define RT_DEBUG_QUEUE_LENGTH		2000

#endif
