#ifndef OBJECT_INTERACTION_H
# define OBJECT_INTERACTION_H

# include "assert.h"
# include "object_definition.h"
# include "object_list.h"
# include "rt_float.h"

# include <stdarg.h>

void				object_build(
					t_object *space,
					t_object_type type,
					t_material material,
					...);

void				object_sphere_build(t_object *space, va_list *args);
void				object_plane_build(t_object *space, va_list *args);

#endif
