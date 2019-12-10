#include "rt.h"

int print_error(t_gpu *gpu)
{
	size_t  len;
	char    *buffer;

	if (gpu->err != CL_SUCCESS)
	{
		buffer = ft_strnew(99999);
		clGetProgramBuildInfo(gpu->program, gpu->device_id, CL_PROGRAM_BUILD_LOG, 100000, buffer, &len);
		ft_putstr(buffer);
		ft_strdel(&buffer);
		return EXIT_FAILURE;
	}
	return (0);
}