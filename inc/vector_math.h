/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:53:56 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:49:29 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "structs.h"
# include <stdio.h>
# include <math.h>

# define EPSILON 0.001
# define M_PI		3.14159265358979323846

t_vec3	vec_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec_scale(double scale, t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
double	vec_len(t_vec3 v);

double	vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);

void	get_cylinder_basis(t_vec3 axis, t_vec3 *right, t_vec3 *fwd);
t_vec3	get_radial_vector(t_vec3 hit, t_vec3 center, t_vec3 axis);
double	get_angle_u(t_vec3 radial, t_vec3 right, t_vec3 fwd);
double	clamp_v(double v);

#endif /* VECTOR_MATH_H */
