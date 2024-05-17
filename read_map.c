/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   read_map.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ewoillar <ewoillar@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/07 13:24:20 by ewoillar		  #+#	#+#			 */
/*   Updated: 2024/05/14 12:48:17 by ewoillar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *str, char separator)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == separator && str[i] != '\n')
			i++;
		if (str[i] != separator && str[i] != '\n' && str[i] != '\0')
			words++;
		while (str[i] && str[i] != separator && str[i] != '\n')
			i++;
	}
	return (words);
}

t_dot	**allocate_matrix2(int x, int y)
{
	t_dot	**matrix;

	matrix = (t_dot **)malloc(sizeof(t_dot *) * (++y + 1));
	matrix[--y] = NULL;
	while (y > 0)
		matrix[--y] = (t_dot *)malloc(sizeof(t_dot) * (x + 1));
	return (matrix);
}

//allocate the matrix of dot to fit the size of the map
t_dot	**allocate_matrix(char *path)
{
	int		fd;
	int		x;
	int		y;
	char	*buffer;
	t_dot	**matrix;

	x = -1;
	y = 0;
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		ft_error("files does not exist.");
	while (get_next_line(fd, &buffer) > 0 || ft_strlen(buffer) > 0)
	{
		if (ft_strlen(buffer) > 0)
			y++;
		if (x < 0)
			x = count_words(buffer, ' ');
		else if (x != count_words(buffer, ' '))
			ft_error("Bad map format\n");
		free(buffer);
	}
	free(buffer);
	matrix = allocate_matrix2(x, y);
	close(fd);
	return (matrix);
}

int	parse_line(char *buffer, t_dot **dot_matrix, int y, t_data data)
{
	int		x;
	char	**split;
	char	**dot;
	int		j;

	if (buffer == NULL)
		return (-1);
	split = ft_split(buffer, ' ');
	x = 0;
	while (split[x])
	{
		dot = ft_split(split[x], ',');
		dot_matrix[y][x].x_pad = data.x_pad;
		dot_matrix[y][x].y_pad = data.y_pad;
		dot_matrix[y][x].zoom = data.zoom;
		dot_matrix[y][x].x = x;
		dot_matrix[y][x].y = y;
		dot_matrix[y][x].z = ft_atoi(split[x]);
		dot_matrix[y][x].is_last_in_line = 0;
		dot_matrix[y][x].color = -1;
		if (dot[1] != NULL)
			dot_matrix[y][x].color = hexarraytoint(dot[1]);
		j = 0;
		while (dot[j])
			free(dot[j++]);
		free(dot);
		free(split[x]);
		x++;
	}
	free(split);
	free(buffer);
	dot_matrix[y][--x].is_last_in_line = 1;
	return (x);
}

//parse la map et intégrer chaque point dans le tableau 2D 
t_dot	**read_map(char *path, t_data data)
{
	int		fd;
	t_dot	**dot_matrix;
	char	*buffer;
	int		y;

	dot_matrix = allocate_matrix(path);
	fd = open(path, O_RDONLY);
	y = 0;
	buffer = NULL;
	if (fd <= 0)
		ft_error("file does not exist.");
	while (get_next_line(fd, &buffer) > 0 || ft_strlen(buffer) > 0)
		parse_line(buffer, dot_matrix, y++, data);
	free(buffer);
	close(fd);
	return (dot_matrix);
}
