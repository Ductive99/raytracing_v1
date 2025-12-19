/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:41:23 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 17:42:18 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

void	check_planes(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_list	*node;
	t_hit	current;

	node = scene->planes;
	while (node)
	{
		if (hit_plane(ray, (t_plan *)node->obj, &current))
		{
			if (current.t > 0.001 && current.t < closest->t)
			{
				*closest = current;
				closest->obj_type = OBJ_PLANE;
				closest->object = node->obj;
			}
		}
		node = node->next;
	}
}
