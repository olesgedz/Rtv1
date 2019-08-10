cmake_minimum_required(VERSION 3.14)
project(rt C)

set(CMAKE_CFLAGS "${CMAKE_CFALGS} -Wall -Wextra")

set(BREW /usr/local/)

set(GTK_INCLUDES
	${BREW}/Cellar/libffi/3.2.1/lib/libffi-3.2.1/include
	${BREW}/Cellar/gtk+3/3.24.10/include/gtk-3.0/
	${BREW}/Cellar/glib/2.60.6/include/gio-unix-2.0
	${BREW}/Cellar/cairo/1.16.0_2/include/cairo
	${BREW}/Cellar/libepoxy/1.5.3/include
	${BREW}/Cellar/pango/1.42.4_2/include/pango-1.0
	${BREW}/Cellar/harfbuzz/2.5.3/include/harfbuzz
	${BREW}/Cellar/graphite2/1.3.13/include
	${BREW}/Cellar/pango/1.42.4_2/include/pango-1.0
	${BREW}/Cellar/fribidi/1.0.5/include/fribidi
	${BREW}/Cellar/atk/2.32.0_1/include/atk-1.0
	${BREW}/Cellar/cairo/1.16.0_2/include/cair
	${BREW}/Cellar/pixman/0.38.4/include/pixman-1
	${BREW}/Cellar/fontconfig/2.13.1/include
	${BREW}/opt/freetype/include/freetype2
	${BREW}/Cellar/libpng/1.6.37/include/libpng16
	${BREW}/Cellar/gdk-pixbuf/2.38.1_1/include/gdk-pixbuf-2.0
	${BREW}/Cellar/glib/2.60.6/include
	${BREW}/Cellar/glib/2.60.6/include/glib-2.0
	${BREW}/Cellar/glib/2.60.6/lib/glib-2.0/include
	${BREW}/opt/gettext/include
	${BREW}/Cellar/pcre/8.43/include)

set(GTK_LINKS
	${BREW}/Cellar/gtk+3/3.24.10/lib
	${BREW}/Cellar/pango/1.42.4_2/lib
	${BREW}/Cellar/atk/2.32.0_1/lib
	${BREW}/Cellar/cairo/1.16.0_2/lib
	${BREW}/Cellar/gdk-pixbuf/2.38.1_1/lib
	${BREW}/Cellar/glib/2.60.6/lib
	${BREW}/opt/gettext/lib)


include_directories(
	${GTK_INCLUDES}
	../21_libft/includes/
	./parameters/
	./gui/
	./gui/gui/
	./gui/gui_scene/
	./gui/gui_object/
	./gui/gui_object_base/
	./gui/gui_list/
	./gui/gui_image/
	./gui/gui_signal/
	./color/
	./light/
	./object/
	./object_list/
	./scene/
	./cl_renderer/
	./f4/
	./camera/
	./ray/
	./intersection/
	./open_cl_manager/
	./assert
	./material)

link_directories(
	${GTK_LINKS}
	../21_libft/)

link_libraries(
	"ft"
	"gtk-3"
	"gdk-3"
	"pangocairo-1.0"
	"pango-1.0"
	"atk-1.0"
	"cairo-gobject"
	"cairo"
	"gdk_pixbuf-2.0"
	"gio-2.0"
	"gobject-2.0"
	"glib-2.0"
	"intl"
	"-framework Cocoa"
	"-framework Carbon"
	"-framework CoreGraphics"
	"-framework OpenCL")

set(SOURCE_MAIN
	./main.c)

set(SOURCE_GUI_GUI
	./gui/gui/gui_new.c
	./gui/gui/gui_delete.c
	./gui/gui/gui_connect_renderer.c
	./gui/gui/gui_loop.c)

set(SOURCE_GUI_LIST
	./gui/gui_list/gui_list_new.c
	./gui/gui_list/gui_list_delete.c)

set(SOURCE_GUI_OBJECT
	./gui/gui_object/gui_object_new.c
	./gui/gui_object/gui_object_delete.c
	./gui/gui_object_base/gui_object_base_init.c
	./gui/gui_object_list/gui_object_sphere.c
	./gui/gui_object_list/gui_object_plane.c)

set(SOURCE_GUI_IMAGE
	./gui/gui_image/gui_image_new.c
	./gui/gui_image/gui_image_delete.c)

set(SOURCE_GUI_SIGNAL
	./gui/gui_signal/gui_signal_connect.c
	./gui/gui_signal/gui_s_obj_selected.c
	./gui/gui_signal/gui_s_sphere_pos.c
	./gui/gui_signal/gui_s_key.c
	./gui/gui_signal/gui_s_sphere_rad.c
	./gui/gui_signal/gui_s_plane_pos.c
	./gui/gui_signal/gui_s_plane_norm.c
	./gui/gui_signal/gui_s_obj_add.c)

set(SOURCE_GUI
	${SOURCE_GUI_GUI}
	${SOURCE_GUI_LIST}
	${SOURCE_GUI_OBJECT}
	${SOURCE_GUI_IMAGE}
	${SOURCE_GUI_SIGNAL})

set(SOURCE_CL_RENDERER
	./cl_renderer/cl_renderer_new.c
	./cl_renderer/cl_renderer_delete.c
	./cl_renderer/cl_renderer_init_device.c
	./cl_renderer/cl_renderer_init_context.c
	./cl_renderer/cl_renderer_create_program.c
	./cl_renderer/cl_renderer_create_queue.c
	./cl_renderer/cl_renderer_create_kernel.c
	./cl_renderer/cl_renderer_init_data.c
	./cl_renderer/cl_renderer_set_arguments.c
	./cl_renderer/cl_renderer_render.c
	./cl_renderer/cl_renderer_log.c
	./cl_renderer/cl_renderer_update.c
	./cl_renderer/cl_renderer_camera_move.c)

set(SOURCE_SCENE
	./scene/scene_new.c
	./scene/scene_get_space.c
	./scene/scene_delete.c)

set(SOURCE_OBJECT
	./object/object_build.c
	./object_list/sphere.c
	./object_list/plane.c
	./gui/gui_signal/gui_s_key.c)

set(SOURCE_F4
	./f4/f4_add.c
	./f4/f4_sub.c
	./f4/f4_mul.c)

set(SOURCE_CAMERA
	./camera/camera_new.c
	./camera/camera_delete.c
	./camera/camera_move.c)

set(SOURCE_RAY
	./ray/ray)

add_executable(rt
	${SOURCE_MAIN}
	${SOURCE_GUI}
	${SOURCE_CL_RENDERER}
	${SOURCE_SCENE}
	${SOURCE_OBJECT}
	${SOURCE_F4}
	${SOURCE_CAMERA}
	${SOURCE_ASSERT})