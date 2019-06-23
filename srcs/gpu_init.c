#include "rtv1.h"


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
    print_error(gpu);
    return 0;
}

void relaese_gpu(t_gpu *gpu)
{
    clReleaseProgram(gpu->program);
    clReleaseKernel(gpu->kernel);
    clReleaseCommandQueue(gpu->commands);
    clReleaseContext(gpu->context);
}

int bind_data(t_gpu *gpu)
{
    int data_size = sizeof(t_vec3) * WIN_W * WIN_H;
    int w = WIN_W; //TODO use as parameter of struct, not macros
    int h = WIN_H;
    size_t global = w * h;
    const int count = global;
    int i;
    int j;
    static t_vec3 *h_a;//TODO push it inside t_gpu

    gpu->kernel = clCreateKernel(gpu->program, "init_calculations", &gpu->err);
    if (h_a == NULL) 
    {
        t_vec3 *h_a = (t_vec3 *)malloc(data_size);
        while (++j < WIN_H)
        {
            i = -1;
            while (++i < WIN_W)	
                h_a[j * WIN_W + i] = (t_vec3){(2 * (i + 0.5) / (float)w - 1) * tan(1.570796371F / 2.) * w / (float)h,
                -(2 * (j + 0.5) / (float)w - 1) * tan(1.570796371F / 2.), -1};
        }
    }
    t_vec3 *out = (t_vec3 *)malloc(data_size);

    cl_mem d_a;
    cl_mem d_out;
    j = -1;
    d_a = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,  data_size, h_a, &gpu->err);
    d_out = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY, data_size, NULL, &gpu->err);

    gpu->err = clSetKernelArg(gpu->kernel, 0, sizeof(cl_mem), &d_a);
    gpu->err |= clSetKernelArg(gpu->kernel, 1, sizeof(cl_mem), &d_out);
    gpu->err |= clSetKernelArg(gpu->kernel, 2, sizeof(unsigned int), &count);

    gpu->err = clEnqueueNDRangeKernel(gpu->commands, gpu->kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
    gpu->err = clEnqueueReadBuffer(gpu->commands, d_out, CL_TRUE, 0, sizeof(t_vec3)*count, out, 0, NULL, NULL);
    for (int i = 0; i < global; ++i)
        printf("%f, %f, %f\n", out[i].x, out[i].y, out[i].z);
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_out);
    relaese_gpu(gpu);
    return (0);
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

