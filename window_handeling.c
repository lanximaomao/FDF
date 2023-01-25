/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/25 12:00:06 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

/*
** fix the hooks
** fix the leaks
** add new functionalities, translation, zoom in and out, rotation
** norminette
*/

int	key_hook(int key, t_fdf *fdf)
{
	ft_printf("key %d ", key);
	if (key == 53)
		exit(0);
	else if (key == 69)
		fdf->input->zoom_z++;
	else if (key == 78)
		fdf->input->zoom_z--;
	return (0);
}

int	mouse_hook(int button, t_fdf *fdf)
{
	printf("my button is %d\n", button);
	if (button == 5)
		fdf->input->zoom++;
	if (button == 4)
		fdf->input->zoom--;
	return (0);
}

int	close_widow (t_fdf *fdf)
{
	fdf = NULL;
	exit(1);
	return (0);
}

//int loop_hook(t_fdf *fdf)
//{
//	//image data
//	return(1);
//}

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
	if ((x >= 0 && x <= WIN_SIZE_X) && (y >= 0 && y <= WIN_SIZE_Y))
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
		my_mlx_pixel_put(fdf->data, pos0.x, pos0.y, color_code);
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

int	zoom(t_map *input)
{
	int	len;
	int	num;
	int	min;

	if (WIN_SIZE_X > WIN_SIZE_Y)
		min = WIN_SIZE_Y;
	else
		min = WIN_SIZE_X;
	num = 1;
	len = 0.87 * (input->size_x + input->size_y);
	if (num * len > min)
	{
		while (num * len > min)
			num = num / 2;
	}
	else if (num * len < min)
	{
		while (num * len < min)
			num++;
	}
	input->zoom = num;
	return (num);
}

t_pos	pos_init(int x, int y, int z, t_pos pos)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_pos	apply_zoom(t_pos pos, int num, t_map *input)
{
	pos.x *= num;
	pos.y *= num;
	pos.z *= input->zoom_z;
	return (pos);
}

t_pos	conversion(t_pos pos, int num, t_map *input)
{
	pos.x -= input->size_x / 2;
	pos.y -= input->size_y / 2;
	pos = apply_zoom(pos, num, input);
	pos = isometric(pos);
	pos.x += WIN_SIZE_X / 2;
	pos.y += WIN_SIZE_Y / 2;
	return (pos);
}

int	which_color(t_pos pos1, t_pos pos2)
{
	int	color_code;

	if (pos1.z == 0 && pos2.z == 0)
		color_code = 0xFFFFFF; // white
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z == pos2.z)
		color_code = 0x020f0; // purple
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z != pos2.z)
		color_code = 0x8b0000; // dark red
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z == pos2.z)
		color_code = 0x00ffff; //cyan
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z != pos2.z)
		color_code = 0x1616ff; //blue
	else if ((pos1.z == 0 && pos2.z < 0) || (pos1.z < 0 && pos2.z == 0))
		color_code = (0x00ffff + 0xFFFFFF) / 2; // grey
	else if ((pos1.z == 0 && pos2.z > 0) || (pos1.z > 0 && pos2.z == 0))
		color_code = 0x013220; // light red
	else if ((pos1.z > 0 && pos2.z < 0) || (pos1.z < 0 && pos2.z > 0))
		color_code = (0x00ffff + 0xFFFFFF) / 2; // grey
	else
		color_code = 0x0000FF;
	return (color_code);
}

int	draw(t_fdf *fdf)
{
	int		i;
	int		j;
	t_pos	pos1;
	t_pos	pos2;
	int		num;

	num = zoom(fdf->input);
	i = -1;
	while (++i < fdf->input->size_y)
	{
		j = -1;
		while (++j < fdf->input->size_x)
		{
			pos1 = pos_init(j, i, fdf->input->map_int[i][j], pos1);
			pos1 = conversion(pos1, num, fdf->input);
			if (i != fdf->input->size_y - 1)
			{
				pos2 = pos_init(j, i + 1, fdf->input->map_int[i + 1][j], pos2);
				pos2 = conversion(pos2, num, fdf->input);
				bresenham_line(pos1, pos2, fdf, which_color(pos1, pos2));
			}
			if (j != fdf->input->size_x - 1)
			{
				pos2 = pos_init(j + 1, i, fdf->input->map_int[i][j + 1], pos2);
				pos2 = conversion(pos2, num, fdf->input);
				bresenham_line(pos1, pos2, fdf, which_color(pos1, pos2));
			}
		}
	}
	return (0);
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

int	image_handeling(t_fdf *fdf)
{
	t_img	*image;

	image = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!image)
		return (0);
	fdf->data = image;
	fdf->data->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!fdf->data)
		return(1);
	fdf->data->addr = (int *)mlx_get_data_addr(fdf->data->img_ptr,
												&fdf->data->bits_per_pixel,
												&fdf->data->line_length,
												&fdf->data->endian);
	//ft_printf("my image basics bpp %d line_len %d endian %d\n",
	//			fdf.data->bits_per_pixel,
	//			fdf.data->line_length,
	//			fdf.data->endian);
	draw(fdf);
	free_int(fdf->input->map_int, fdf->input->size_y);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->data->img_ptr, 0, 0);
	return (1);
}

int	register_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 2, 0, key_hook, fdf); // 2 is the event code for a key press
	mlx_hook(fdf->win_ptr, 17, 0, close_widow, fdf); // 17 is the mouse event code means for close button
	mlx_hook(fdf->win_ptr, 4, 0, mouse_hook, fdf); // 4 is mouse up
	mlx_hook(fdf->win_ptr, 5, 0, mouse_hook, fdf); // 5 is mouse down
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_map	*input;

	//init
	fdf = ft_calloc(1, sizeof(t_fdf));//remember to free
	if (!fdf)
		exit (1);
	input = ft_calloc(1, sizeof(t_map));
	if (!input)
		exit (1);
	fdf->input = input;

	//map, working on
	if (map_handling(argc, argv, fdf) == 0)
		return(1);
	// set up window
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		exit(1);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "FDF");
	if (!fdf->win_ptr)
		exit(1);
	//hook
	image_handeling(fdf);
	register_hooks(fdf);
	mlx_loop(fdf->mlx_ptr);

	// free stuff
	free(input);
	return (0);
}

/*
** https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/
