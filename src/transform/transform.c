#include "minirt.h"
#include "vector_math.h"
#include <math.h>

static void	translate_sphere(t_sphere *sp, t_vec3 delta)
{
	sp->center = vec_add(sp->center, delta);
}

static void	translate_plane(t_plan *pl, t_vec3 delta)
{
	pl->point = vec_add(pl->point, delta);
}

static void	translate_cylinder(t_cylinder *cy, t_vec3 delta)
{
	cy->center = vec_add(cy->center, delta);
}

static void	translate_light(t_light *li, t_vec3 delta)
{
	li->pos = vec_add(li->pos, delta);
}

void	translate_camera(t_scene *scene, t_vec3 delta)
{
	scene->camera.position = vec_add(scene->camera.position, delta);
}

void	translate_selection(t_scene *scene, t_vec3 delta)
{
	if (scene->selection.type == OBJ_NONE || !scene->selection.object)
		return ;
	if (scene->selection.type == OBJ_SPHERE)
		translate_sphere((t_sphere *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_PLANE)
		translate_plane((t_plan *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_CYLINDER)
		translate_cylinder((t_cylinder *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_LIGHT)
		translate_light((t_light *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_CAMERA)
		translate_camera(scene, delta);
}

static t_vec3	rotate_vec(t_vec3 v, t_vec3 axis, double angle)
{
	double	cos_a;
	double	sin_a;
	t_vec3	result;
	double	dot;

	angle = angle * M_PI / 180.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	axis = vec_normalize(axis);
	dot = vec_dot(v, axis);
	result.x = v.x * cos_a + (axis.y * v.z - axis.z * v.y) * sin_a + axis.x
		* dot * (1 - cos_a);
	result.y = v.y * cos_a + (axis.z * v.x - axis.x * v.z) * sin_a + axis.y
		* dot * (1 - cos_a);
	result.z = v.z * cos_a + (axis.x * v.y - axis.y * v.x) * sin_a + axis.z
		* dot * (1 - cos_a);
	return (vec_normalize(result));
}

static void	rotate_plane(t_plan *pl, t_vec3 axis, double angle)
{
	pl->normal = rotate_vec(pl->normal, axis, angle);
}

static void	rotate_cylinder(t_cylinder *cy, t_vec3 axis, double angle)
{
	cy->axis = rotate_vec(cy->axis, axis, angle);
}

void	rotate_camera(t_scene *scene, t_vec3 axis, double angle)
{
	scene->camera.dir = rotate_vec(scene->camera.dir, axis, angle);
}

void	rotate_selection(t_scene *scene, t_vec3 axis, double angle)
{
	if (scene->selection.type == OBJ_NONE || !scene->selection.object)
		return ;
	if (scene->selection.type == OBJ_PLANE)
		rotate_plane((t_plan *)scene->selection.object, axis, angle);
	else if (scene->selection.type == OBJ_CYLINDER)
		rotate_cylinder((t_cylinder *)scene->selection.object, axis, angle);
	else if (scene->selection.type == OBJ_CAMERA)
		rotate_camera(scene, axis, angle);
}

static void	resize_sphere(t_sphere *sp, double factor)
{
	sp->diameter *= factor;
	if (sp->diameter < 0.1)
		sp->diameter = 0.1;
}

static void	resize_cylinder(t_cylinder *cy, double factor)
{
	cy->diameter *= factor;
	cy->height *= factor;
	if (cy->diameter < 0.1)
		cy->diameter = 0.1;
	if (cy->height < 0.1)
		cy->height = 0.1;
}

void	resize_selection(t_scene *scene, double factor)
{
	if (scene->selection.type == OBJ_NONE || !scene->selection.object)
		return ;
	if (scene->selection.type == OBJ_SPHERE)
		resize_sphere((t_sphere *)scene->selection.object, factor);
	else if (scene->selection.type == OBJ_CYLINDER)
		resize_cylinder((t_cylinder *)scene->selection.object, factor);
}
