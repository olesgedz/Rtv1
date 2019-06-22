#include "rtv1.h"

int    gpu_read_kernel(t_gpu *gpu)
{
    char    ch;
    int     fd;
    char    *line;
    size_t  len;
    char    *buffer;

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

    gpu->program = clCreateProgramWithSource(gpu->context, 1, (const char **)&gpu->kernel_source, NULL, &gpu->err);
    gpu->err = clBuildProgram(gpu->program, 0, NULL, NULL, NULL, NULL);
    //TODO delete after debug
    if (gpu->err != CL_SUCCESS)
    {
        buffer = ft_strnew(9999);
        clGetProgramBuildInfo(gpu->program, gpu->device_id, CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
        printf("%s\n", buffer);
        ft_strdel(&buffer);
        return EXIT_FAILURE;
    }
    return 0;
}

int print_error(t_gpu *gpu)
{
    size_t  len;
    char    *buffer;

    if (gpu->err != CL_SUCCESS)
    {
        buffer = ft_strnew(99999);
        clGetProgramBuildInfo(gpu->program, gpu->device_id, CL_PROGRAM_BUILD_LOG, 100000, buffer, &len);
        printf("%s\n", buffer);
        ft_strdel(&buffer);
        return EXIT_FAILURE;
    }
    return (0);
}

int bind_data(t_gpu *gpu)
{
    int data_size = sizeof(t_vec3) * WIN_W * WIN_H;
    int w = WIN_W;
    int h = WIN_H;
    const unsigned int global = w * h;
    int i;
    int j;

    gpu->kernel = clCreateKernel(gpu->program, "init_calculations", &gpu->err);

    t_vec3 *h_a = (t_vec3 *)malloc(data_size);
    t_vec3 *out = (t_vec3 *)malloc(data_size);

    cl_mem d_a;
    cl_mem out_vec;
    j = -1;
    while (++j < WIN_H)
	{
		i = -1;
		while (++i < WIN_W)	
		{
	        float x = (2 * (i + 0.5) / (float)w - 1) * tan(1.570796371F / 2.) * w / (float)h;
	        float y = -(2 * (j + 0.5) / (float)w - 1) * tan(1.570796371F / 2.);
            h_a[j * WIN_W + i] = x + y;
            // printf("%f, %f, %f\n", h_a[j * WIN_W + i].x, h_a[j * WIN_W + i].y, h_a[j * WIN_W + i].z);
        }
    }
    d_a = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,  data_size, h_a, &gpu->err);
    out_vec = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY, data_size, NULL, &gpu->err);
    gpu->err = clSetKernelArg(gpu->kernel, 0, sizeof(cl_mem), &d_a);
    // gpu->err |= clSetKernelArg(gpu->kernel, 1, sizeof(int), &w);
    // if (print_error(gpu) != 0)
    //     return 1;
    // gpu->err |= clSetKernelArg(gpu->kernel, 2, sizeof(int), &h);
    // if (print_error(gpu) != 0)
    //     return 1;
    gpu->err |= clSetKernelArg(gpu->kernel, 1, sizeof(cl_mem), &out_vec);
    gpu->err |= clSetKernelArg(gpu->kernel, 2, sizeof(const unsigned int), &global);

    gpu->err = clEnqueueNDRangeKernel(gpu->commands, gpu->kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
    gpu->err = clEnqueueReadBuffer(gpu->commands, out_vec, CL_TRUE, 0, data_size, out, 0, NULL, NULL);
    for (int i = 0; i < global; ++i)
        printf("%f\n", out[i]);
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
    bind_data(gpu);
    return (gpu->err);
}

