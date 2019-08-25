#include "cl_renderer.h"

static void			cl_program_allocate(t_cl_program *program)
{
	program->length = 0;
	program->capacity = 128;
	program->buffer = malloc(program->capacity);
}

static void			cl_program_reallocate(t_cl_program *program)
{
	ft_realloc((void **)&program->buffer,
		program->capacity, program->capacity * 2);
	program->capacity *= 2;
}

static void			cl_program_read
					(t_cl_program *program, const char *file)
{
	int				fd;
	char			file_full[64];
	int 			read_length;
	int 			nl_counter;

	ft_strcpy(file_full, CL_SOURCE_FOLDER);
	ft_strcat(file_full, file);
	fd = open(file_full, O_RDONLY);
	ASSERT(fd != -1)
	while (1)
	{
		if ((program->length + 64.) / program->capacity > 0.5)
			cl_program_reallocate(program);
		if ((read_length = read(fd, program->buffer + program->length, 64)) < 1)
			break ;
		program->length += read_length;
	}
	nl_counter = 0;
	nl_counter += program->buffer[program->length - 2] != '\n';
	nl_counter += program->buffer[program->length - 1] != '\n';
	while (nl_counter-- > 0)
		program->buffer[program->length++] = '\n';
	close(fd);
}

static int			cl_program_finish
					(t_cl_program *program, cl_context *context)
{
	program->buffer[program->length] = '\0';
	program->program = clCreateProgramWithSource(*context, 1,
		(const char **)&program->buffer, &program->length, &program->error);
	ASSERT(program->error == 0)
	program->error =
		clBuildProgram(program->program, 0, NULL, CL_FLAGS, NULL, NULL);
	if (program->error != 0)
		return (program->error);
	free(program->buffer);
	program->buffer = NULL;
	program->capacity = 0;
	program->length = -1;
	return (0);
}

void				cl_renderer_create_program(t_cl_renderer *renderer)
{
	cl_program_allocate(&renderer->program);
	cl_program_read(&renderer->program, CL_SOURCE_F4);
	cl_program_read(&renderer->program, CL_SOURCE_SETTINGS);
	cl_program_read(&renderer->program, CL_SOURCE_RANDOM);
	cl_program_read(&renderer->program, CL_SOURCE_RAY);
	cl_program_read(&renderer->program, CL_SOURCE_CAMERA);
	cl_program_read(&renderer->program, CL_SOURCE_COLOR);
	cl_program_read(&renderer->program, CL_SOURCE_MATERIAL);
	cl_program_read(&renderer->program, CL_SOURCE_INTERSECTION);
	cl_program_read(&renderer->program, CL_SOURCE_OBJECT);
	cl_program_read(&renderer->program, CL_SOURCE_OBJECT_SPHERE);
	cl_program_read(&renderer->program, CL_SOURCE_OBJECT_PLANE);
	cl_program_read(&renderer->program, CL_SOURCE_OBJECT_INTERSECT);
	cl_program_read(&renderer->program, CL_SOURCE_OBJECT_NORMAL);
	cl_program_read(&renderer->program, CL_SOURCE_SCENE);
	cl_program_read(&renderer->program, CL_SOURCE_SAMPLE);
	cl_program_read(&renderer->program, CL_SOURCE_RADIANCE_EXPLICIT);
	cl_program_read(&renderer->program, CL_SOURCE_RADIANCE);
	cl_program_read(&renderer->program, CL_SOURCE_MAIN);
	if (cl_program_finish(&renderer->program, &renderer->context))
		cl_renderer_log(renderer);
}
