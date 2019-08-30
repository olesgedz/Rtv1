#ifndef  CL_ERROR_H
# define CL_ERROR_H

#include <stdlib.h>
#define BLURT printf ("This is line %d of file \"%s\" (function <%s>)\n",\
                      __LINE__, __FILE__, __func__)
# define ERROR(data)						\
	if ((data))							\
	{											\
		printf("{red!}Error\n");	\
		printf("file : %s\n", __FILE__);		\
		printf("function : %s\n", __func__);	\
		printf("line : %d\n", __LINE__);		\
		exit(1);								\
	}
#endif
