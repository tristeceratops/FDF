/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ewoillar <ewoillar@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/13 18:11:42 by ewoillar		  #+#	#+#			 */
/*   Updated: 2024/05/13 18:20:22 by ewoillar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

int	get_max_height(t_dot **tableau, int rows, int columns)
{
	int	maximum;
	int	i;
	int	j;

	maximum = tableau[0][0].z;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (tableau[i][j].z > maximum)
				maximum = tableau[i][j].z;
			j++;
		}
		i++;
	}
	return (maximum);
}

int	get_min_height(t_dot **tableau, int rows, int columns)
{
	int	minimum;
	int	i;
	int	j;

	minimum = tableau[0][0].z;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (tableau[i][j].z < minimum)
				minimum = tableau[i][j].z;
			j++;
		}
		i++;
	}
	return (minimum);
}

int	get_rows(t_dot **table)
{
	int	rows;

	rows = 0;
	while (table[rows] != NULL)
		rows++;
	return (rows);
}

int	get_columns(t_dot **table)
{
	int	columns;

	columns = 0;
	while (table[0][columns].is_last_in_line != 1)
		columns++;
	if (table[0][columns].is_last_in_line == 1)
		columns++;
	return (columns);
}

void	free_map(t_dot **table)
{
	int	rows;

	rows = 0;
	while (table[rows] != NULL)
	{
		free(table[rows]);
		rows++;
	}
	free(table);
}
