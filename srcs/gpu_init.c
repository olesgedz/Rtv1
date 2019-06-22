#include "rtv1.h"

int    gpu_read_kernel(t_gpu *gpu)
{
    char    ch;
    int     fd;
    char    *line;
    size_t  len;
    char    buffer[2048];

    fd = open("srcs/intersect.cl", O_RDONLY); // read mode
    if (fd < 0)
        exit(EXIT_FAILURE);
    gpu->kernel_source = ft_strnew(0);
    while (get_next_line(fd, &line) > 0)
    {
        line = ft_strjoin(line, "\n");
        gpu->kernel_source = ft_strjoin(gpu->kernel_source, line);
        ft_strdel(&line);
    }
    close(fd);
    gpu->program = clCreateProgramWithSource(gpu->context, 1, &gpu->kernel_source, NULL, &gpu->err);
    gpu->err = clBuildProgram(gpu->program, 0, NULL, NULL, NULL, NULL);
    if (gpu->err != CL_SUCCESS)
    {
        clGetProgramBuildInfo(gpu->program, gpu->device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        return EXIT_FAILURE;
    }
    return 0;
}

int opencl_init(t_gpu *gpu)
{
    int     i;
    
    i = -1;
    gpu->err = clGetPlatformIDs(0, NULL, &gpu->numPlatforms);
    if (gpu->numPlatforms == 0)
        return (EXIT_FAILURE);
    cl_platform_id Platform[gpu->numPlatforms];
    gpu->err = clGetPlatformIDs(gpu->numPlatforms, Platform, NULL);
    while (++i < gpu->numPlatforms)
    {
        gpu->err = clGetDeviceIDs(Platform[i], DEVICE, 1, &gpu->device_id, NULL);
        if (gpu->err == CL_SUCCESS)
            break;
    }
    if (gpu->device_id == NULL)
        return (1);
    gpu->context = clCreateContext(0, 1, &gpu->device_id, NULL, NULL, &gpu->err);
    gpu->commands = clCreateCommandQueue(gpu->context, gpu->device_id, 0, &gpu->err);
    gpu_read_kernel(gpu);
    return (gpu->err);
}

