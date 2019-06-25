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

void release_gpu(t_gpu *gpu)
{
	clReleaseProgram(gpu->program);
	clReleaseKernel(gpu->kernel);
	clReleaseCommandQueue(gpu->commands);
	clReleaseContext(gpu->context);
}

int bind_data(t_gpu *gpu, t_main_obj *main)
{
	int data_size = sizeof(t_vec3) * WIN_W * WIN_H;
	int w = WIN_W; //TODO use as parameter of struct, not macros
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;
	const int count = global;
	int i;
	int j;
	static t_vec3 *h_a;//TODO push it inside t_gpu
	
	gpu->cpuOutput = malloc(sizeof(int) * (w * h)); 
	
	cl_mem cl_bufferOut = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY, global * sizeof(cl_int), NULL, &gpu->err);
	gpu->err |= clSetKernelArg(gpu->kernel, 0, sizeof(cl_mem), &cl_bufferOut);
	gpu->err |= clSetKernelArg(gpu->kernel, 1, sizeof(int), &w);
	gpu->err |= clSetKernelArg(gpu->kernel, 2, sizeof(int), &h);
	gpu->err = clEnqueueNDRangeKernel(gpu->commands, gpu->kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
    gpu->err = clEnqueueReadBuffer(gpu->commands, cl_bufferOut, CL_TRUE, 0, global * sizeof(cl_int), gpu->cpuOutput, 0, NULL, NULL);
	// for (int i = 0; i < numElements; i++)
	// {
	// 	printf("%f + %f = %f\n", cpuArrayA[i], cpuArrayB[i], cpuOutput[i]);
	// }
	
    clReleaseMemObject(cl_bufferOut);
    release_gpu(gpu);
	return (0);
	}
//     if (h_a == NULL) 
//     {
//         t_vec3 *h_a = (t_vec3 *)malloc(data_size);
//         while (++j < WIN_H)
//         {
//             i = -1;
//             while (++i < WIN_W)	
//                 h_a[j * WIN_W + i] = (t_vec3){(2 * (i + 0.5) / (float)WIN_W - 1) * tan(1.570796371F / 2.) * WIN_W / (float)WIN_H,
//                 -(2 * (j + 0.5) / (float)WIN_H - 1) * tan(1.570796371F / 2.), -1};
//         }
//     }
//     t_vec3 *out = (t_vec3 *)malloc(data_size);
//     // void *figs = malloc(sizeof(void *) * main->figures_num);
//     // for (int i = 0; i < main->figures_num; ++i)
//     // {
//     //     figs[i] = main->figures[i].object;
//     // }
//     j = -1;
//     d_a = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//         sizeof(t_vec3) * WIN_W * WIN_H, h_a, &gpu->err);
//     d_obj = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//         sizeof(t_object) * main->figures_num, main->figures, &gpu->err);
//     d_light = clCreateBuffer(gpu->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//         sizeof(t_light) * main->elum_num, main->lights, &gpu->err);
//     d_out = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY, data_size, NULL, &gpu->err);

//     gpu->err = clSetKernelArg(gpu->kernel, 0, sizeof(cl_mem), &d_a);
//     gpu->err |= clSetKernelArg(gpu->kernel, 1, sizeof(cl_mem), &d_obj);
//     gpu->err |= clSetKernelArg(gpu->kernel, 2, sizeof(cl_mem), &d_light);

//     gpu->err |= clSetKernelArg(gpu->kernel, 3, sizeof(int), &main->figures_num);
//     gpu->err |= clSetKernelArg(gpu->kernel, 4, sizeof(int), &main->elum_num);
//     gpu->err |= clSetKernelArg(gpu->kernel, 5, sizeof(cl_mem), &d_out);
//     gpu->err |= clSetKernelArg(gpu->kernel, 6, sizeof(unsigned int), &count);
//     // print_error(gpu);
// 	printf("outside: number of lights: %i, number of objects:%i\n", main->elum_num, main->figures_num);

//     gpu->err = clEnqueueNDRangeKernel(gpu->commands, gpu->kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
//     gpu->err = clEnqueueReadBuffer(gpu->commands, d_out, CL_TRUE, 0, sizeof(t_vec3)*count, out, 0, NULL, NULL);
//     // for (int i = 0; i < main->elum_num; ++i)
//     // {
//     //     printf("inside: %i - %f, %f, %f\n", i, main->lights[i].position.x,
//     //                                             main->lights[i].position.y,
//     //                                             main->lights[i].position.z);
//     // }
//     // for (int i = 0; i < global; ++i)
//     //     printf("%f, %f, %f\n", out[i].x, out[i].y, out[i].z);
//     clReleaseMemObject(d_a);
//     clReleaseMemObject(d_out);
//     release_gpu(gpu);
//     return (0);
// }

int opencl_init(t_gpu *gpu, t_game *game)
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
	gpu->kernel = clCreateKernel(gpu->program, "init_calculations", &gpu->err);
   // bind_data(gpu, &game->main_objs);
    return (gpu->err);
}

