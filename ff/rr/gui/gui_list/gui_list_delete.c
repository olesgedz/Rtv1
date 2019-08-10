#include "gui_list.h"

void				gui_list_delete(t_gui_list **list)
{
	free(*list);
	*list = NULL;
}