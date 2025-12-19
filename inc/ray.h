/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:02:31 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:51:46 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structs.h"

bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);
bool	hit_plane(t_ray ray, t_plan *plane, t_hit *hit);
bool	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit);
bool	hit_cylinder_caps(t_ray ray, t_cylinder *cyl, t_hit *hit);
bool	hit_cone(t_ray ray, t_cone *cone, t_hit *hit);
bool	hit_cone_cap(t_ray ray, t_cone *cone, t_hit *hit);
t_vec3	ray_at(t_ray ray, double t);
t_color	trace_ray(t_ray ray, t_scene *scene);
t_hit	trace_ray_select(t_ray ray, t_scene *scene);
t_ray	init_shadow_ray(t_vec3 hit_point, t_vec3 normal, t_vec3 dir);

#endif /* RAY_H */
