/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/17 14:51:27 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * put_pixel - Put a pixel in the image buffer at given coordinates
 * @img: Pointer to image structure
 * @x: X coordinate of the pixel
 * @y: Y coordinate of the pixel
 * @color: Color value (0xRRGGBB format)
 *
 * This function writes a pixel directly to the image buffer.
 * It's faster than mlx_pixel_put() which updates the window immediately.
 * The image must be pushed to the window with mlx_put_image_to_window()
 * to see the changes.
 *
 * Note: Checks boundaries to prevent segmentation faults.
 */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * rgb_to_int - Convert RGB values to integer color
 * @r: Red component (0-255)
 * @g: Green component (0-255)
 * @b: Blue component (0-255)
 *
 * Return: Integer color in 0xRRGGBB format
 */
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
