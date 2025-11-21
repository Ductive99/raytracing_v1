/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:03:07 by esouhail          #+#    #+#             */
/*   Updated: 2025/11/21 23:06:34 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * t_img - Image buffer structure for pixel manipulation
 *
 * @img_ptr: MLX image pointer returned by mlx_new_image()
 * @addr: Starting address of the image buffer
 * @bits_per_pixel: Number of bits used to represent a pixel's color
 * @line_len: Number of bytes used to store one line of the image
 * @endian: Byte order (0 = little endian, 1 = big endian)
 */
typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_img;

/**
 * t_mlx - Main MLX context structure
 *
 * @mlx_ptr: MLX instance pointer returned by mlx_init()
 * @win_ptr: Window pointer returned by mlx_new_window()
 * @img: Image buffer structure for rendering
 */
typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
}					t_mlx;

/**
 * t_vec3 - 3D vector/point structure for geometric calculations
 *
 * @x: X-axis component
 * @y: Y-axis component (vertical in world space)
 * @z: Z-axis component (depth)
 */
typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef t_vec3		t_pos;
typedef t_vec3		t_dir;

/**
 * t_color - RGB color structure for final pixel values
 *
 * @r:   Red component (0 - 255)
 * @g: Green component (0 - 255)
 * @b:  Blue component (0 - 255)
 */
typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

/**
 * t_list - Linked list
 * 
 * @obj: pointer to current node
 * @next: pointer to the next node
 */
typedef struct s_list
{
	void			*obj;
	struct s_list	*next;
}					t_list;

/**
 * t_ambient - Ambient lighting configuration (identifier: A)
 *
 * @ratio: Ambient lighting intensity ratio [0.0-1.0]
 * @color: RGB color values [0-255] for ambient light
 */
typedef struct s_ambient
{
	double			ratio;
	t_color			color;
}					t_ambient;

/**
 * t_light - Point light source (identifier: L)
 *
 * @pos: x,y,z coordinates of the light point
 * @dir: Brightness ratio (unused in mandatory part)
 * @color: RGB color values [0-255] for light (unused in mandatory part)
 */
typedef struct s_light
{
	t_pos			pos;
	double			ratio;
	t_color			color;
}					t_light;

/**
 * t_cam - Camera configuration (identifier: C)
 *
 * @pos: x,y,z coordinates of the camera viewpoint
 * @dir: 3D normalized orientation vector [-1,1] for each axis
 * @fov: Horizontal field of view in degrees [0-180]
 */
typedef struct s_cam
{
	t_pos			pos;
	t_dir			dir;
	double			fov;
}					t_cam;

/**
 * t_sphere - Sphere object (identifier: sp)
 *
 * @center: x,y,z coordinates of the sphere center
 * @diameter: Sphere diameter (not radius)
 * @color: RGB color values [0-255]
 */
typedef struct s_sphere
{
	t_pos			center;
	double			diameter;
	t_color			color;
}					t_sphere;

/**
 * t_plan - Plane object (identifier: pl)
 *
 * @point: x,y,z coordinates of a point in the plane
 * @normal: 3D normalized normal vector [-1,1] for each axis
 * @color: RGB color values [0-255]
 */
typedef struct s_plan
{
	t_pos			point;
	t_vec3			normal;
	t_color			color;
}					t_plan;

/**
 * t_cylinder - Cylinder object (identifier: cy)
 *
 * @center: x,y,z coordinates of the cylinder center
 * @axis: 3D normalized vector of cylinder axis [-1,1] for each axis
 * @diameter: Cylinder diameter
 * @height: Cylinder height
 * @color: RGB color values [0-255]
 */
typedef struct s_cylinder
{
	t_pos			center;
	t_vec3			axis;
	double			diameter;
	double			height;
	t_color			color;
}					t_cylinder;

/**
 * t_scene - Complete scene structure containing all rendering elements
 * 
 * @ambient: Ambient lighting
 * @camera: Camera viewpoint and configuration
 * @lights: Linked list of point light sources in the scene
 * @spheres: Linked list of sphere objects to render
 * @planes: Linked list of plane objects to render
 * @cylinders: Linked list of cylinder objects to render
 */
typedef struct s_scene
{
	t_ambient		ambient;
	t_cam			camera;
	t_list			*lights;
	t_list			*spheres;
	t_list			*planes;
	t_list			*cylinders;
}					t_scene;

/**
 * t_object_parser - Object parsing structure
 * 
 * @id: Object identifier
 * @id_len: length of identifier
 * @parser_func: pointer to the corresponding parsing function
 * 
 */
typedef struct s_object_parser
{
	const char	*id;
	int			id_len;
	void		(*parser_func)(char **, t_scene *);
}		t_object_parser;

#endif /* STRUCTS_H */
