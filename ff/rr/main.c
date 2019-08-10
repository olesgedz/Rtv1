#include "gui.h"
#include "cl_renderer.h"
#include "material_list.h"

void				scene_test(t_scene *scene)
{
	object_build(
		scene_get_space(scene), object_sphere,
		MATERIAL_RED,
		(RT_F4_API){-10., -10., -55.}, 2.);
	object_build(
		scene_get_space(scene), object_sphere,
		MATERIAL_RED,
		(RT_F4_API){10., -10., -55.}, 2.);
	object_build(
		scene_get_space(scene), object_sphere,
		MATERIAL_RED,
		(RT_F4_API){-10., 10., -55.}, 2.);
	object_build(
		scene_get_space(scene), object_sphere,
		MATERIAL_RED,
		(RT_F4_API){10., 10., -55.}, 2.);
	object_build(
		scene_get_space(scene), object_sphere,
		MATERIAL_LIGHT,
		(RT_F4_API){0., 0., -40.}, 3.);
	object_build(
		scene_get_space(scene),
		object_plane,
		MATERIAL_WHITE,
		(RT_F4_API){0., 0., -70.},
		(RT_F4_API){0., 0., 1.});
}

int					main(int argc, char **argv)
{
	t_gui			*gui;

	gui = gui_new(&argc, &argv);
	scene_test(gui->renderer->data_host.scene);
	gui_connect_renderer(gui);
	gui_loop(gui);
	gui_delete(&gui);
	return (0);
}