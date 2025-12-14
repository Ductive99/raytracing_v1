/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:53:56 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/14 15:50:12 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "structs.h"
# include <stdio.h>
# include <math.h>

# define EPSILON 0.001

t_vec3	vec_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec_scale(double scale, t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
double	vec_len(t_vec3 v);

double	vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);

#endif /* VECTOR_MATH_H */
