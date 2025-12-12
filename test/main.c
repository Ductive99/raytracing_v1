/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/12 18:12:05 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	init_scene(t_scene *scene)
{
	scene->ambient.ratio = -1.0;
	scene->camera.fov = 0.0;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

void	print_scene(t_scene *scene)
{
	printf("\n=== SCENE PARSED ===\n");
	printf("Ambient: ratio=%.2f, color=(%d,%d,%d)\n", scene->ambient.ratio,
		scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	printf("Camera: pos=(%.1f,%.1f,%.1f), fov=%.1f\n", scene->camera.pos.x,
		scene->camera.pos.y, scene->camera.pos.z, scene->camera.fov);
	printf("===================\n\n");
}

void	cleanup_scene(t_scene *scene)
{
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->spheres, free);
	ft_lstclear(&scene->planes, free);
	ft_lstclear(&scene->cylinders, free);
}

int	main(int argc, char **argv)
{
	t_scene	scene = {0};

	if (argc != 2)
	{
		printf("Usage: %s <scene.rt>\n", argv[0]);
		return (1);
	}
	init_scene(&scene);
	if (parse_scene(argv[1], &scene) == PARSE_ERROR)
	{
		printf("Error: Failed to parse scene\n");
		return (1);
	}
	print_scene(&scene);
	printf("✅ Parsing successful!\n");
	cleanup_scene(&scene);
	return (0);
}
