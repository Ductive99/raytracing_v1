/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:02:31 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/14 15:39:15 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structs.h"
# include <stdbool.h>

bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);
t_vec3	ray_at(t_ray ray, double t);

#endif /* RAY_H */
