#include "cl_renderer.h"

void				cl_renderer_log(t_cl_renderer *renderer)
{
	char			*log;
	u_long			log_length;
	FILE			*file;

	clGetProgramBuildInfo(renderer->program.program, renderer->device_id,
		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_length);
	log = ft_strnew(log_length);
	clGetProgramBuildInfo(renderer->program.program, renderer->device_id,
		CL_PROGRAM_BUILD_LOG, log_length + 1, log, NULL);
	printf("cl compilation log (%d): \n%s\n", renderer->program.error, log);
	free(log);
	file = fopen("./cl_build", "w");
	fprintf(file, "%s\n", renderer->program.buffer);
	fclose(file);
	exit(1);
}