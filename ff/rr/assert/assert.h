#ifndef FT_ASSERT_H
# define FT_ASSERT_H

# include "libft_ft_printf.h"

# define ASSERT(statement)						\
	if (!(statement))							\
    {											\
		ft_printf("{red!}assertion failed\n");	\
        ft_printf("file : %s\n", __FILE__);		\
        ft_printf("function : %s\n", __func__);	\
        ft_printf("line : %d\n", __LINE__);		\
        exit(1);								\
    }


#endif
