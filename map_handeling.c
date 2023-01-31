/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handeling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:47:29 by lsun              #+#    #+#             */
/*   Updated: 2023/01/31 15:23:53 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

int	ft_create_2d_int(t_fdf *fdf)
{
	fdf->input->map_2d = ft_split(fdf->input->map_1d, '\n');
	fdf->input->map_int = (int **)ft_calloc(sizeof(int *), fdf->input->size_y);
	if (!fdf->input->map_int)
		return (0);
	while (++fdf->i < fdf->input->size_y)
	{
		fdf->input->map_int[fdf->i] = (int *)ft_calloc(sizeof(int),
				fdf->input->size_x);
		if (!fdf->input->map_int[fdf->i])
			return (0);
		fdf->input->point = ft_split(fdf->input->map_2d[fdf->i], ' ');
		fdf->j = -1;
		while (++fdf->j < fdf->input->size_x && ++fdf->k < fdf->input->size_x
			* fdf->input->size_y)
			fdf->input->map_int[fdf->i][fdf->j] = ft_atoi(fdf->input->point[fdf->j]);
		free_char(fdf->input->point);
	}
	free(fdf->input->map_1d);
	free_char(fdf->input->map_2d);
	return (1);
}

int	ft_how_many(char *str, char c)
{
	int	num;

	num = 0;
	while (*str != '\0')
	{
		if (*str == c)
			num++;
		str++;
	}
	return (num);
}

void	ft_map_init(t_fdf *fdf)
{
	fdf->input->size_x = 0;
	fdf->input->size_y = 0;
	fdf->input->zoom = 1;
	fdf->input->zoom_z = 1;
	fdf->i = -1;
	fdf->j = -1;
	fdf->k = -1;
}

int	ft_read_map(char **argv, t_fdf *fdf)
{
	fdf->input->fd = open(argv[1], O_RDONLY);
	if (fdf->input->fd == -1)
	{
		ft_printf("cann't open file");
		return (0);
	}
	ft_map_init(fdf);
	fdf->input->line = get_next_line(fdf->input->fd);
	fdf->input->line_split = ft_split(fdf->input->line, ' ');
	while (fdf->input->line_split[fdf->input->size_x])
	{
		fdf->input->size_x++;
	}
	free_char(fdf->input->line_split);
	fdf->input->map_1d = ft_strdup(fdf->input->line);
	free(fdf->input->line);
	while (1)
	{
		fdf->input->line = get_next_line(fdf->input->fd);
		if (!fdf->input->line)
			break ;
		fdf->input->map_1d = ft_strjoin_gnl(fdf->input->map_1d,
				fdf->input->line);
		free(fdf->input->line);
	}
	fdf->input->size_y = ft_how_many(fdf->input->map_1d, '\n');
	if (ft_create_2d_int(fdf) == 0)
		return (0);
	close(fdf->input->fd);
	return (1);
}

int	map_handling(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
	{
		ft_printf("incorrect map\n");
		exit(1);
	}
	if (ft_read_map(argv, fdf) == 0)
		return (0);
	zoom_init(fdf);
	return (1);
}
