/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:02:31 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/18 02:26:23 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structs.h"

bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);
bool	hit_plane(t_ray ray, t_plan *plane, t_hit *hit);
bool	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit);
bool	hit_cylinder_caps(t_ray ray, t_cylinder *cyl, t_hit *hit);
t_vec3	ray_at(t_ray ray, double t);
t_color	trace_ray(t_ray ray, t_scene *scene);

#endif /* RAY_H */
