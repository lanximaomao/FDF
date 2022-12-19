/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handeling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:47:29 by lsun              #+#    #+#             */
/*   Updated: 2022/12/19 21:12:04 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


//char	*get_next_line(int fd);

// make the hook work
// include libft and printf

int main(int argc, char**argv)
{
	int fd;

	if (argc != 2)
	{
		ft_printf("incorrect map");
		return(0);
	}
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd);
	return(0);
}
