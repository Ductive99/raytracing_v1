/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:27:27 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/17 16:30:32 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structs.h"

void	setup_camera(t_cam *cam, int width, int height);
t_ray	get_camera_ray(t_cam *cam, int x, int y);
void	render_scene(t_scene *scene, t_mlx *mlx);

#endif /* CAMERA_H */
