/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:03:13 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:31:24 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	clean(t_fdf *fdf)
{
	if (!fdf)
		exit(1);
	if (fdf->mlx_ptr && fdf->img->img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	if (fdf->mlx_ptr && fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free(fdf->img);
	fdf->img = NULL;
	free_int(fdf->input->map_int, fdf->input->size_y);
	free(fdf->input);
	fdf->input = NULL;
	free(fdf);
	fdf = NULL;
	exit(1);
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
	free(input);
}
