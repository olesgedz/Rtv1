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

	// fd = open("srcs/intersect.cl", O_RDONLY); // read mode
	// if (fd < 0)
	// 	exit(EXIT_FAILURE);
	// gpu->kernel_source = ft_strnew(0);
	// while (get_next_line(fd, &line) > 0)
	// {
	// 	line = ft_strjoin(line, "\n");
	// 	gpu->kernel_source = ft_strjoin(gpu->kernel_source, line);
	// 	ft_strdel(&line);
	// }
	// close(fd);
	gpu->kernel_source = read_file(open("srcs/cl_files/main.cl", O_RDONLY), 0);
	gpu->program = clCreateProgramWithSource(gpu->context, 1, (const char **)&gpu->kernel_source, NULL, &gpu->err);
	gpu->err = clBuildProgram(gpu->program, 0, NULL, "-w -I includes/cl_headers/ -I srcs/cl_files/", NULL, NULL);
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
	clReleaseMemObject(gpu->cl_bufferOut);
	clReleaseMemObject(gpu->cl_cpuSpheres);
}

int bind_data(t_gpu *gpu, t_main_obj *main)
{
	int data_size = sizeof(t_vec3) * WIN_W * WIN_H;
	int w = WIN_W; //TODO use as parameter of struct, not macros
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;
	const int count = global;
	const int n_spheres = 9;
	int i;
	int j;
	static t_vec3 *h_a;//TODO push it inside t_gpu
	gpu->vec_temp = ft_memalloc(sizeof(cl_float3) * global);
	gpu->camera = camera_new(WIN_W, WIN_H);
	gpu->cl_cpu_vectemp = clCreateBuffer(gpu->context, CL_MEM_READ_WRITE, count * sizeof(cl_float3), NULL, &gpu->err);
	gpu->cl_bufferOut = clCreateBuffer(gpu->context, CL_MEM_WRITE_ONLY, count * sizeof(cl_int), NULL, &gpu->err);
	gpu->cl_cpuSpheres= clCreateBuffer(gpu->context, CL_MEM_READ_ONLY, n_spheres * sizeof(t_obj), NULL, &gpu->err);
	gpu->cl_cpu_camera= clCreateBuffer(gpu->context, CL_MEM_READ_ONLY, sizeof(t_camera), NULL, &gpu->err);
	gpu->err = clEnqueueWriteBuffer(gpu->commands, gpu->cl_cpu_camera, CL_TRUE, 0,
			sizeof(t_camera), &gpu->camera, 0, NULL, NULL);
	gpu->err = clEnqueueWriteBuffer(gpu->commands, gpu->cl_cpuSpheres, CL_TRUE, 0,
			n_spheres * sizeof(t_obj), gpu->spheres, 0, NULL, NULL);
	gpu->err |= clSetKernelArg(gpu->kernel, 0, sizeof(cl_mem), &gpu->cl_bufferOut);
	gpu->err |= clSetKernelArg(gpu->kernel, 1, sizeof(cl_int), &w);
	gpu->err |= clSetKernelArg(gpu->kernel, 2, sizeof(cl_int), &h);
	gpu->err |= clSetKernelArg(gpu->kernel, 3, sizeof(cl_int), &n_spheres);
	gpu->err |= clSetKernelArg(gpu->kernel, 4, sizeof(cl_mem), &gpu->cl_cpuSpheres);
	gpu->err |= clSetKernelArg(gpu->kernel, 5, sizeof(cl_mem), &gpu->cl_cpu_vectemp);
	gpu->err |= clSetKernelArg(gpu->kernel, 6, sizeof(cl_int), &gpu->samples);
	gpu->err |= clSetKernelArg(gpu->kernel, 7, sizeof(cl_mem), &gpu->cl_cpu_camera);

	BLURT;
    //clReleaseMemObject(cl_bufferOut);
    //release_gpu(gpu);
	return (0);
}

void ft_run_gpu(t_gpu *gpu)
{
	size_t global = WIN_W * WIN_H;
	const int count = global;
	gpu->samples +=15;
	gpu->err |= clSetKernelArg(gpu->kernel, 6, sizeof(cl_int), &gpu->samples);
	gpu->err = clEnqueueNDRangeKernel(gpu->commands, gpu->kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
	// clFinish(gpu->commands);
	gpu->err = clEnqueueReadBuffer(gpu->commands, gpu->cl_bufferOut, CL_TRUE, 0, count * sizeof(cl_int), gpu->cpuOutput, 0, NULL, NULL);
}

cl_float3 create_cfloat3 (float x, float y, float z)
{
	cl_float3 re;

	re.v4[0] = x;
	re.v4[1] = y;
	re.v4[2] = z;
	return re;
}

void initScene(t_obj* cpu_spheres)
{
	// left sphere
	cpu_spheres[0].radius   = 0.1f;
	cpu_spheres[0].position = create_cfloat3 (-0.4f, -0.f, -0.1f);
	cpu_spheres[0].color    = create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[0].v = create_cfloat3 (0.f, 1.0f, 0.0f);
	cpu_spheres[0].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[0].type = CYLINDER;
	cpu_spheres[0].reflection = 0.f;

	// right sphere
	cpu_spheres[1].radius   = 0.16f;
	cpu_spheres[1].position = create_cfloat3 (0.0f, -0.f, 0.1f);
	cpu_spheres[1].color    = create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[1].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[1].v = create_cfloat3 (0.0f, 1.0f, 0.0f);
	cpu_spheres[1].type = SPHERE;
	cpu_spheres[1].reflection = 3.f;

	// lightsource
	cpu_spheres[2].radius   = 0.3f; 
	cpu_spheres[2].position = create_cfloat3 (0.0f, 0.3f, 0.0f);
	cpu_spheres[2].color    = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[2].emission = create_cfloat3 (9.0f, 8.0f, 6.0f);
	cpu_spheres[2].type = SPHERE;
	cpu_spheres[2].reflection = 0;

		// left wall
	cpu_spheres[6].radius	= 200.0f;
	cpu_spheres[6].position = create_cfloat3 (-1.0f, 0.0f, 0.0f);
	cpu_spheres[6].color    = create_cfloat3 (0.75f, 0.25f, 0.25f);
	cpu_spheres[6].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[6].type = PLANE;
	cpu_spheres[6].reflection = 0;
	cpu_spheres[6].plane_d = -0.6f;

	// right wall
	cpu_spheres[7].radius	= 200.0f;
	cpu_spheres[7].position = create_cfloat3 (200.6f, 0.0f, 0.0f);
	cpu_spheres[7].color    = create_cfloat3 (0.25f, 0.25f, 0.75f);
	cpu_spheres[7].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[7].type = SPHERE;
	cpu_spheres[7].reflection = 0;

	// floor
	cpu_spheres[8].radius	= 200.0f;
	cpu_spheres[8].position = create_cfloat3 (0.0f, 1.f, 0.0f);
	cpu_spheres[8].color	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[8].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[8].type = PLANE;
	cpu_spheres[8].reflection = 0;
	cpu_spheres[8].plane_d = 0.4f;
	// ceiling
	cpu_spheres[3].radius	= 200.0f;
	cpu_spheres[3].position = create_cfloat3 (0.0f, 1.0f, 0.0f);
	cpu_spheres[3].color	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[3].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[3].type = PLANE;
	cpu_spheres[3].reflection = 0;
	cpu_spheres[3].plane_d = -0.35f;


	// back wall
	cpu_spheres[4].radius   = 200.0f;
	cpu_spheres[4].position = create_cfloat3 (0.0f, 0.0f, -200.4f);
	cpu_spheres[4].color    = create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[4].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[4].type = SPHERE;
 	cpu_spheres[4].reflection = 0;
	cpu_spheres[4].reflection = 0;


	// front wall 
	cpu_spheres[5].radius   = 200.0f;
	cpu_spheres[5].position = create_cfloat3 (0.0f, 0.0f, 202.0f);
	cpu_spheres[5].color    = create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[5].emission = create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[5].type = SPHERE;
	cpu_spheres[5].reflection = 0;
}

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
	gpu->kernel = clCreateKernel(gpu->program, "render_kernel", &gpu->err);
	gpu->cpuOutput = malloc(sizeof(int) * (WIN_H * WIN_H));
	gpu->spheres = malloc(sizeof(t_obj) * 9);
	gpu->samples = 0;
	initScene(gpu->spheres);
	bind_data(gpu, &game->main_objs);
    return (gpu->err);
}

