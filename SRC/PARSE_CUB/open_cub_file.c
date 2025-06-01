/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 17:02:51 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	error_msg(int fd, char *msg, char **cub)
{
	if (fd >= 0)
		close(fd);
	ft_putstr_fd("Error - ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (cub != NULL)
		ft_str_arr_free(&cub);
	return (false);
}

bool	load_cub_file_contents(char ***cub, int fd)
{
	char	*line;
	char	**tmp;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		tmp = ft_str_arr_add(*cub, line);
		free(line);
		if (tmp == NULL)
		{
			ft_putstr_fd("Error - failed to add line \
				to cub double array.\n", 2);
			ft_str_arr_free(cub);
			return (false);
		}
		*cub = tmp;
	}
	return (true);
}

bool	open_cub_file_and_copy_data(t_cube *data, char *filename)
{
	char	**cub;
	int		fd;

	fd = open(filename, O_RDONLY);
	cub = NULL;
	if (fd < 0)
		return (error_msg(fd, "parse_main() failed to open .cub.", cub));
	cub = ft_str_arr_init();
	if (!cub)
		return (error_msg(fd, "cub array failed to init.", cub));
	if (!load_cub_file_contents(&cub, fd))
		return (error_msg(fd, "load_cub_file() failed to load.", cub));
	if (ft_str_arr_len((const char **)cub) < 7)
		return (error_msg(fd, "cub file is not long enough.", cub));
	data->map.data = ft_str_arr_dup(cub);
	ft_str_arr_free(&cub);
	close(fd);
	return (true);
}
