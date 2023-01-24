/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handeling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:47:29 by lsun              #+#    #+#             */
/*   Updated: 2023/01/24 13:59:39 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

t_map	ft_create_2d_int(t_map input)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = -1;
	input.map_2d = ft_split(input.map_1d, '\n');
	free(input.map_1d);
	input.map_int = (int **)ft_calloc(sizeof(int *), input.size_y);
	if (!input.map_int)
		exit(1);
	while (++i < input.size_y)
	{
		input.map_int[i] = (int *)ft_calloc(sizeof(int), input.size_x);
		if (!input.map_int[i])
			exit(1);
		input.point = ft_split(input.map_2d[i], ' ');
		free(input.map_2d[i]);
		j = -1;
		while (++j < input.size_x && ++k < input.size_x * input.size_y)
		{
			input.map_int[i][j] = ft_atoi(input.point[j]);
			free(input.point[j]);
		}
	}
	free(input.map_2d);
	free(input.point);
	return (input);
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

t_map	ft_map_init(t_map input)
{
	input.size_x = 0;
	input.size_y = 0;
	input.zoom = 1;
	input.zoom_z = 1;
	return (input);
}

void	free_char(char **input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
}

t_map	ft_read_map(char **argv, t_map input)
{
	input.fd = open(argv[1], O_RDONLY);
	if (input.fd == -1)
		ft_printf("cann't open file");
	input = ft_map_init(input);
	input.line = get_next_line(input.fd);
	input.line_split = ft_split(input.line, ' ');
	while (input.line_split[input.size_x])
	{
		input.size_x++;
	}
	free_char(input.line_split);
	input.map_1d = ft_strdup(input.line);
	free(input.line);
	while (1)
	{
		input.line = get_next_line(input.fd);
		if (!input.line)
			break ;
		input.map_1d = ft_strjoin_gnl(input.map_1d, input.line);
		free(input.line);
	}
	free(input.line);
	input.size_y = ft_how_many(input.map_1d, '\n');
	input = ft_create_2d_int(input);
	close(input.fd);
	return (input);
}

t_map	map_handling(int argc, char **argv, t_map input)
{
	if (argc != 2)
	{
		ft_printf("incorrect map\n");
		exit(1);
	}
	input = ft_read_map(argv, input);
	ft_printf("my map's x dimension is \n %d\n", input.size_x);
	ft_printf("my map's y dimension is\n %d\n", input.size_y);
	return (input);
}
