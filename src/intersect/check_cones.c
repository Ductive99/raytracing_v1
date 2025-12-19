/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:33:29 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 17:40:10 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

static void	check_cone(t_ray ray, t_cone *cone, t_hit *current, t_hit *closest)
{
	if (hit_cone(ray, cone, current))
	{
		if (current->t > 0.001 && current->t < closest->t)
		{
			*closest = *current;
			closest->obj_type = OBJ_CONE;
			closest->object = cone;
		}
	}
	if (hit_cone_cap(ray, cone, current))
	{
		if (current->t > 0.001 && current->t < closest->t)
		{
			*closest = *current;
			closest->obj_type = OBJ_PLANE;
			closest->object = cone;
		}
	}
}

void	check_cones(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_list	*node;
	t_hit	current;

	node = scene->cones;
	while (node)
	{
		check_cone(ray, (t_cone *)node->obj, &current, closest);
		node = node->next;
	}
}
