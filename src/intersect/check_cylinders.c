/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:42:35 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 20:47:41 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

static void	check_cylinder(t_ray ray, t_cylinder *cy,
	t_hit *current, t_hit *closest)
{
	if (hit_cylinder(ray, cy, current))
	{
		if (current->t > 0.001 && current->t < closest->t)
		{
			*closest = *current;
			closest->obj_type = OBJ_CYLINDER;
			closest->object = cy;
		}
	}
	if (hit_cylinder_caps(ray, cy, current))
	{
		if (current->t > 0.001 && current->t < closest->t)
		{
			*closest = *current;
			closest->obj_type = OBJ_CYLINDER_CAP;
			closest->object = cy;
		}
	}
}

void	check_cylinders(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_list	*node;
	t_hit	current;

	node = scene->cylinders;
	while (node)
	{
		check_cylinder(ray, (t_cylinder *)node->obj, &current, closest);
		node = node->next;
	}
}
