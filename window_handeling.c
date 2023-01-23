/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/24 00:17:24 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

/*
** add new functionalities, translation, zoom in and out, rotation
** norminette
*/

int	deal_key(int key, t_fdf *fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(1);
	}
	ft_printf("%d ", key);
	return (0);
}

int	close_window(void *fdf)
{
	fdf = NULL;
	exit(1);
}

int ft_abs(int a)
{
	if (a < 0)
		return(-a);
	return(a);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color_code)
{
	int		dst;

	dst = y * (data->line_length/4) + x;
	if ((x >= 0 && x <= WIN_SIZE_X) && (y >= 0 && y<= WIN_SIZE_Y))
		data->addr[dst] = color_code;
}

t_line line_init(t_pos pos0, t_pos pos1)
{
	t_line	line;

	line.dx = ft_abs(pos1.x - pos0.x);
	if (pos0.x < pos1.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -ft_abs (pos1.y - pos0.y);
	if (pos0.y < pos1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	line.e2 = 2 *line.err;
	return(line);
}

int bresenham_line (t_pos pos0, t_pos pos1, t_fdf fdf, int color_code)
{
	t_line line;

	line = line_init(pos0, pos1);
  while (1)
  {
    my_mlx_pixel_put(fdf.data, pos0.x, pos0.y, color_code);
    if (pos0.x == pos1.x && pos0.y == pos1.y)
		break;
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

t_pos isometric(t_pos pos)
{
	int temp;

	temp =pos.x;

	pos.x = (pos.x - pos.y) * 0.87; // cos30
	pos.y = -pos.z + (temp + pos.y) * 0.50; // sin30
	//ft_printf("after isometric %d and %d\n", pos.x, pos.y);
	return(pos);
}

int zoom( t_map input)
{
	int len;
	int num;

	num = 1;
	len = 0.87 * (input.size_x + input.size_y);

	if (num * len > WIN_SIZE_X)
	{
		while (num * len > WIN_SIZE_X)
			num= num/2;
	}
	else if (num * len < WIN_SIZE_X)
	{
		while (num * len < WIN_SIZE_X)
			num++;
	}
	//ft_printf("num is %d\n", num);
	return (num);
}

t_pos pos_init(int x, int y, int z, t_pos pos)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	return(pos);
}

t_pos apply_zoom(t_pos pos, int num)
{
	pos.x *= num;
	pos.y *= num;
	//ft_printf("after zoom %d %d\n", pos.x, pos.y);
	return (pos);
}
t_pos conversion(t_pos pos, int num, t_map input)
{
	pos.x -= input.size_x / 2;
	pos.y -= input.size_y / 2;
	pos = apply_zoom(pos, num);
	pos = isometric(pos);
	pos.x += WIN_SIZE_X / 2;
	pos.y += WIN_SIZE_Y / 2;
	return(pos);
}

int which_color(t_pos pos1, t_pos pos2)
{
	int color_code;

	if (pos1.z == 0 && pos2.z == 0)
		color_code = 0xFFFFFF; // white
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z == pos2.z)
		color_code = 0xff0000; // red
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z != pos2.z)
		color_code = 0xffcccb; // light red?
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z == pos2.z)
		color_code = 0x00ffff;//cyan
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z != pos2.z)
		color_code = 0x00ffff;//cyan-- change?
	else if ((pos1.z ==  0 && pos2.z < 0) || (pos1.z < 0 && pos2.z == 0))
		color_code = (0x00ffff + 0xFFFFFF)/2; // grey
	else if ((pos1.z ==  0 && pos2.z > 0) || (pos1.z > 0 && pos2.z == 0))
		color_code = 0xffcccb; // light red
	else if ((pos1.z >  0 && pos2.z < 0) || (pos1.z < 0 && pos2.z > 0))
		color_code = (0x00ffff + 0xFFFFFF)/2; // grey
	else
		color_code = 0x0000FF;
	return(color_code);
}

int	draw(t_map input, t_fdf fdf)
{
	int		i;
	int		j;
	int		color_code;
	t_pos	pos1;
	t_pos	pos2;
	int		num;

	num = zoom(input);
	i = 0;
	while (i < input.size_y)
	{
		j = 0;
		while (j < input.size_x)
		{
			pos1 = pos_init(j, i, input.map_int[i][j], pos1);
			pos1 = conversion(pos1, num, input);
			if (i != input.size_y - 1)
			{
				pos2 = pos_init(j, i + 1, input.map_int[i+1][j], pos2);
				pos2 = conversion(pos2, num, input);
				color_code = which_color(pos1, pos2);
				bresenham_line(pos1, pos2, fdf, color_code);
			}
			if (j != input.size_x - 1)
			{
				pos2 = pos_init(j + 1, i, input.map_int[i][j+1], pos2);
				pos2 = conversion(pos2, num, input);
				color_code = which_color(pos1, pos2);
				bresenham_line(pos1, pos2, fdf, color_code);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int image_handeling(t_map input, t_fdf fdf)
{
	t_img	*image;

	image = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!image)
		return(0);
	fdf.data = image;
	fdf.data->img_ptr = mlx_new_image(fdf.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	fdf.data->addr = (int *)mlx_get_data_addr(fdf.data->img_ptr, &fdf.data->bits_per_pixel, &fdf.data->line_length, &fdf.data->endian);
	ft_printf("my image basics bpp %d line_len %d endian %d\n", fdf.data->bits_per_pixel, fdf.data->line_length, fdf.data->endian);
	draw(input, fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.data->img_ptr, 0, 0);
	return(1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_map	*input;

	input = ft_calloc(1, sizeof(t_map));
	if (!input)
		return (0);
	*input = map_handling(argc, argv, *input);
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "FDF");
	image_handeling(*input, fdf);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf);      //key press
	mlx_hook(fdf.win_ptr, 17, 0, close_window, &fdf); //mouse click
	mlx_loop(fdf.mlx_ptr);
	free(input);
	return (0);
}

/*
** https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/
