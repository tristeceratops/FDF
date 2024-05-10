/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:24:20 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/10 15:40:47 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		count_words(char *str, char separator)
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

//allocate the matrix of dot to fit the size of the map
t_dot	**allocate_matrix(char *path)
{
	int		fd;
	int		x;
	int		y;
	char	*buffer;
	t_dot	**matrix;

	x = 0;
	y = 1;
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		ft_error("files does not exist.");
	get_next_line(fd , &buffer);
	x = count_words(buffer, ' ');
	while (get_next_line(fd, &buffer) > 0)
	{
		y++;
		free(buffer);
	}
	free(buffer);
	matrix = (t_dot **)malloc(sizeof(t_dot *) * (++y + 1));
	while (y > 0)
		matrix[--y] = (t_dot *)malloc(sizeof(t_dot) * (x + 1));
	close(fd);
	return (matrix);
}

int		parse_line(char *buffer, t_dot **dot_matrix, int y)
{
	int		x;
	char	**split;

	if (buffer == NULL)
		return (-1);
	split = ft_split(buffer, ' ');
	x = 0;
	while (split[x])
	{
		dot_matrix[y][x].x_pad = 500;
		dot_matrix[y][x].y_pad = 500;
		dot_matrix[y][x].zoom = 25;
		dot_matrix[y][x].x = x;
		dot_matrix[y][x].y = y;
		dot_matrix[y][x].z = ft_atoi(split[x]);
		dot_matrix[y][x].is_last_in_line = 0;
		free(split[x]);
		x++;
	}
	free(split);
	free(buffer);
	dot_matrix[y][--x].is_last_in_line = 1;
	return (x);
}

//parse la map et intégrer chaque point dans le tableau 2D 
t_dot	**read_map(char *path)
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
    while (get_next_line(fd, &buffer) > 0)
		parse_line(buffer, dot_matrix, y++);
	parse_line(buffer, dot_matrix, y);
	//free(buffer);
	close(fd);
	return (dot_matrix);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char *path = "test.txt"; // Replace "your_map_file.txt" with the path to your map file
    t_dot **dot_matrix = read_map(path);

    // Print the matrix for testing
    int i = 0;
    int j = 0;
    while (dot_matrix[i] != NULL) {
        j = 0;
        while (dot_matrix[i][j].is_last_in_line == 0) {
            printf("(%d %d %d) ", (int)dot_matrix[i][j].x, (int)dot_matrix[i][j].y, (int)dot_matrix[i][j].z);
			j++;
        }
		printf("(%d %d %d) ", (int)dot_matrix[i][j].x, (int)dot_matrix[i][j].y, (int)dot_matrix[i][j].z);
        printf("\n");
        i++;
    }
    // Free memory
    i = 0;
    while (dot_matrix[i] != NULL) {
        free(dot_matrix[i]);
        i++;
    }
    free(dot_matrix);    
    return 0;
}*/