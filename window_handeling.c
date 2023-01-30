/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/30 12:06:34 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

/*
** fix the leaks
** translation? rotation?
** norminette
**
** NOTE
** 1) 17 is the mouse event code means for close button;
** 2) https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color_code)
{
	int	dst;

	dst = y * (data->line_length / 4) + x;
	if ((x >= 0 && x < WIN_SIZE_X) && (y >= 0 && y < WIN_SIZE_Y))
		data->addr[dst] = color_code;
}

t_line	line_init(t_pos pos0, t_pos pos1)
{
	t_line	line;

	line.dx = ft_abs(pos1.x - pos0.x);
	if (pos0.x < pos1.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -ft_abs(pos1.y - pos0.y);
	if (pos0.y < pos1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	line.e2 = 2 * line.err;
	return (line);
}

int	bresenham_line(t_pos pos0, t_pos pos1, t_fdf *fdf, int color_code)
{
	t_line	line;

	line = line_init(pos0, pos1);
	while (1)
	{
		my_mlx_pixel_put(fdf->img, pos0.x, pos0.y, color_code);
		if (pos0.x == pos1.x && pos0.y == pos1.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			pos0.x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			pos0.y += line.sy;
		}
	}
	return (1);
}

t_pos	isometric(t_pos pos)
{
	int	temp;

	temp = pos.x;
	pos.x = (pos.x - pos.y) * 0.87;
	pos.y = -pos.z + (temp + pos.y) * 0.50;
	return (pos);
}

t_pos	pos_init(int x, int y, int z, t_pos pos)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_pos	apply_zoom(t_pos pos, t_fdf *fdf)
{
	pos.x *= fdf->input->zoom;
	pos.y *= fdf->input->zoom;
	pos.z *= fdf->input->zoom_z;
	return (pos);
}

t_pos	conversion(t_pos pos, t_fdf *fdf)
{
	pos.x -= fdf->input->size_x / 2;
	pos.y -= fdf->input->size_y / 2;
	pos = apply_zoom(pos, fdf);
	pos = isometric(pos);
	pos.x += WIN_SIZE_X / 2;
	pos.y += WIN_SIZE_Y / 2;
	return (pos);
}

int	which_color(t_pos pos1, t_pos pos2)
{
	int	color_code;

	if (pos1.z == 0 && pos2.z == 0)
		color_code = 0xffffff; // white
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z == pos2.z)
		color_code = 0x020f0; // purple
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z != pos2.z)
		color_code = 0x8b0000; // dark red
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z == pos2.z)
		color_code = 0x00ffff; //cyan
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z != pos2.z)
		color_code = 0x1616ff; //blue
	else if ((pos1.z == 0 && pos2.z < 0) || (pos1.z < 0 && pos2.z == 0))
		color_code = (0x00ffff + 0xffffff) / 2; // grey
	else if ((pos1.z == 0 && pos2.z > 0) || (pos1.z > 0 && pos2.z == 0))
		color_code = 0x013220; // light red
	else if ((pos1.z > 0 && pos2.z < 0) || (pos1.z < 0 && pos2.z > 0))
		color_code = (0x00ffff + 0xffffff) / 2; // grey
	else
		color_code = 0x0000FF;
	return (color_code);
}

void	free_int(int **input, int height)
{
	int	j;

	j = 0;
	while (j < height)
	{
		free(input[j]);
		j++;
	}
	free(input);
}

int	draw(t_fdf *fdf)
{
	int		i;
	int		j;
	t_pos	pos1;
	t_pos	pos2;

	i = -1;
	while (++i < fdf->input->size_y)
	{
		j = -1;
		while (++j < fdf->input->size_x)
		{
			pos1 = pos_init(j, i, fdf->input->map_int[i][j], pos1);
			pos1 = conversion(pos1, fdf);
			if (i != fdf->input->size_y - 1)
			{
				pos2 = pos_init(j, i + 1, fdf->input->map_int[i + 1][j], pos2);
				pos2 = conversion(pos2, fdf);
				bresenham_line(pos1, pos2, fdf, which_color(pos1, pos2));
			}
			if (j != fdf->input->size_x - 1)
			{
				pos2 = pos_init(j + 1, i, fdf->input->map_int[i][j + 1], pos2);
				pos2 = conversion(pos2, fdf);
				bresenham_line(pos1, pos2, fdf, which_color(pos1, pos2));
			}
		}
	}
	return (0);
}

int	image_handeling(t_fdf *fdf)
{
	fdf->img = (t_img *)ft_calloc(sizeof(t_img), 1);//free?
	if (!fdf->img)
		return (0);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!fdf->img->img_ptr)
		return(1);
	fdf->img->addr = (int *)mlx_get_data_addr(fdf->img->img_ptr,
												&fdf->img->bits_per_pixel,
												&fdf->img->line_length,
												&fdf->img->endian);
	return (1);
}

int	loop_hook(t_fdf *fdf)
{
	draw(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
	return (1);
}

void clean(t_fdf *fdf)
{
	if(!fdf)
		exit(1);
	if (fdf->mlx_ptr && fdf->img->img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	if (fdf->mlx_ptr && fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free(fdf->img);
	fdf->img = NULL;
	//input
	//free(fdf->input->line);
	//free(fdf->input->map_1d);
	//free_char(fdf->input->map_2d);
	//free_char(fdf->input->line_split);
	free_int(fdf->input->map_int, fdf->input->size_y);
	free(fdf->input);
	fdf->input = NULL;
	free(fdf);
	fdf = NULL;
	exit(1);
}

int	refresh_image(t_fdf *fdf)//
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	free(fdf->img);
	image_handeling(fdf);
	loop_hook(fdf);
	return (1);
}


void	register_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 17, 0, close_widow, fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, fdf);
	mlx_mouse_hook(fdf->win_ptr, mouse_hook, fdf);
	loop_hook(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		clean(fdf);
	fdf->input = ft_calloc(1, sizeof(t_map));
	if (!fdf->input)
		clean(fdf);
	if (map_handling(argc, argv, fdf) == 0)
		clean(fdf);
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		clean(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "FDF");
	if (!fdf->win_ptr)
		clean(fdf);
	if (image_handeling(fdf)== 0)
		clean(fdf);
	register_hooks(fdf);
	mlx_loop(fdf->mlx_ptr);
	clean(fdf);
	return (0);
}
