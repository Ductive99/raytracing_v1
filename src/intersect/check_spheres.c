/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:40:24 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 17:42:06 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

void	check_spheres(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_list	*node;
	t_hit	current;

	node = scene->spheres;
	while (node)
	{
		if (hit_sphere(ray, (t_sphere *)node->obj, &current))
		{
			if (current.t > 0.001 && current.t < closest->t)
			{
				*closest = current;
				closest->obj_type = OBJ_SPHERE;
				closest->object = node->obj;
			}
		}
		node = node->next;
	}
}
