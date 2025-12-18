/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:03:07 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/18 11:24:13 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# define WIDTH 1600
# define HEIGHT 900

typedef enum e_parse_status
{
	PARSE_SUCCESS = 0,
	PARSE_ERROR = 1
}					t_parse_status;

/**
 * t_object_type - Type of object in scene
 */
typedef enum e_object_type
{
	OBJ_NONE = 0,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_LIGHT,
	OBJ_CAMERA
}					t_object_type;

/**
 * t_selection - Currently selected object for transformation
 *
 * @type: Type of object selected
 * @object: Pointer to the selected object
 */
typedef struct s_selection
{
	t_object_type	type;
	void			*object;
}					t_selection;

/**
 * t_button - Interactive button for HUD
 */
typedef struct s_button
{
	int				x;
	int				y;
	int				w;
	int				h;
	int				action;
	char			*label;
}					t_button;

# define BTN_MOVE_LEFT 1
# define BTN_MOVE_RIGHT 2
# define BTN_MOVE_UP 3
# define BTN_MOVE_DOWN 4
# define BTN_MOVE_FWD 5
# define BTN_MOVE_BACK 6
# define BTN_ROT_LEFT 7
# define BTN_ROT_RIGHT 8
# define BTN_ROT_UP 9
# define BTN_ROT_DOWN 10
# define BTN_SIZE_UP 11
# define BTN_SIZE_DOWN 12
# define BTN_DESELECT 13
# define BTN_QUIT 14
# define BTN_LIGHT_BASE 100
# define MAX_LIGHTS 8
# define NUM_BUTTONS 14

# define HUD_X (WIDTH - 280)
# define HUD_Y 10
# define HUD_W 270
# define HUD_H 560

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
 * @scene: Pointer to the scene (for cleanup in hooks)
 */
typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	void			*scene;
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

typedef t_vec3		t_point;
typedef t_vec3		t_dir;

/**
 * t_ray - Ray structure for ray tracing
 *
 * @origin: Startin point of the ray
 * @direction: Normalized direction vector of the ray
 */
typedef struct s_ray
{
	t_point			origin;
	t_dir			direction;
}					t_ray;

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
 * t_hit - Hit record for ray-object intersections
 *
 * @hit: Whether an intersection occurred
 * @t: Distance along the ray to the hit point
 * @point: 3D coordinates of the intersection point
 * @normal: Surface normal at the hit point (normalized, pointing outward)
 * @color: Color of the object at the hit point
 * @obj_type: Type of object hit
 * @object: Pointer to the hit object
 */
typedef struct s_hit
{
	bool			hit;
	double			t;
	t_point			point;
	t_vec3			normal;
	t_color			color;
	t_object_type	obj_type;
	void			*object;
}					t_hit;

typedef struct s_quadratic
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
}					t_quadratic;

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
	t_point			pos;
	double			ratio;
	t_color			color;
}					t_light;

/**
 * t_cam - Camera configuration (identifier: C)
 *
 * @position: x,y,z coordinates of the camera viewpoint
 * @dir: 3D normalized orientation vector for each axis
 * @fov: field of view in degrees
 * @viewport_u: viewport horizontal vector
 * @viewport_v: viewport vertical vector
 * @viewport_upper_left: upper-left corner
 * @pixel_delta_u: horizontal pixel spacing
 * @pixel_delta_v: vertical pixel spacing
 */
typedef struct s_cam
{
	t_point			position;
	t_vec3			dir;
	double			fov;
	t_vec3			viewport_u;
	t_vec3			viewport_v;
	t_vec3			viewport_upper_left;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
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
	t_point			center;
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
	t_point			point;
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
	t_point			center;
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
 * @selection: Currently selected object for transformation
 */
typedef struct s_scene
{
	t_ambient		ambient;
	t_cam			camera;
	t_list			*lights;
	t_list			*spheres;
	t_list			*planes;
	t_list			*cylinders;
	t_selection		selection;
}					t_scene;

/**
 * t_render_task - Thread rendering task structure
 *
 * @mlx: Pointer to MLX structure
 * @scene: Pointer to scene
 * @y_start: Starting row for this thread
 * @y_end: Ending row for this thread
 * @scale: Render scale (1 = full, 4 = fast)
 */
typedef struct s_render_task
{
	void			*mlx;
	void			*scene;
	int				y_start;
	int				y_end;
	int				scale;
}					t_render_task;

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
	const char		*id;
	int				id_len;
	t_parse_status	(*parser_func)(char **, t_scene *);
}					t_object_parser;

#endif /* STRUCTS_H */
