#ifndef CL_COMPILATION_H
# define CL_COMPILATION_H

# define CL_SILENCE_DEPRECATION
# pragma OPENCL EXTENSION cl_khr_fp64 : enable

# define CL_FLAGS						"-I ./parameters/"

# define CL_MAIN_FUNCTION				"cl_main"

# define CL_SOURCE_FOLDER				"./cl_source/"

# define CL_SOURCE_F4					"cl_f4"
# define CL_SOURCE_SETTINGS				"cl_settings"
# define CL_SOURCE_RANDOM				"cl_random"
# define CL_SOURCE_RAY					"cl_ray"
# define CL_SOURCE_CAMERA				"cl_camera"
# define CL_SOURCE_COLOR				"cl_color"
# define CL_SOURCE_MATERIAL				"cl_material"
# define CL_SOURCE_INTERSECTION			"cl_intersection"
# define CL_SOURCE_OBJECT				"cl_object"
# define CL_SOURCE_OBJECT_SPHERE		"cl_object_sphere"
# define CL_SOURCE_OBJECT_PLANE			"cl_object_plane"
# define CL_SOURCE_OBJECT_INTERSECT		"cl_object_intersect"
# define CL_SOURCE_OBJECT_NORMAL		"cl_object_normal"
# define CL_SOURCE_SCENE				"cl_scene"
# define CL_SOURCE_SAMPLE				"cl_sample"
# define CL_SOURCE_RADIANCE_EXPLICIT	"cl_radiance_explicit"
# define CL_SOURCE_RADIANCE				"cl_radiance"
# define CL_SOURCE_MAIN					"cl_main"

#endif
