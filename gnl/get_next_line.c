/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:17:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/07 14:55:16 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char     *ft_malloc_size(char **line, char *buf)
{
    char    *ret;
    int         line_len;
    int         buf_len;

    line_len = 0;
    while (*line &&(*line)[line_len] && (*line)[line_len] != '\n')
        line_len++;
    buf_len = 0;
    while (*buf && buf[buf_len] && buf[buf_len] != '\n')
        buf_len++;
    ret = malloc(sizeof(char) * (line_len + buf_len + 1));
    if (!ret)
        return (NULL);
    return (ret);
}

static int      ft_add_to_line(char **line, char *buf)
{
    char    *tmp;
    int         i;
    int         j;

    tmp = ft_malloc_size(line, buf);
    if (!tmp)
        return (-1);
    i = 0;
    j = 0;
    while (*line && (*line)[i] && (*line)[i] != '\n')
        tmp[i++] = (*line)[j++];
    j = 0;
    while (buf[j] && buf[j] != '\n')
        tmp[i++] = buf[j++];
    tmp[i] = buf[j];
    free(*line);
    *line = tmp;
    i = 0;
    while (buf[j])
        buf[i++] = buf[++j];
    buf[i] = '\0';
    i = 0;
    while ((*line)[i] && (*line)[i] != '\n')
        i++;
    return (i);
}

static int      ft_get_next_line(int fd, char **line)
{
    static char     buf[FD_MAX][BUFFER_SIZE + 1];
    int             ret;

    *line = NULL;
    ret = ft_add_to_line(line, buf[fd]);
    while (ret != -1 && (*line)[ret] != '\n')
    {
        ret = read(fd, buf[fd], BUFFER_SIZE);
        if (ret < 1)
        {
            if (ret < 0)
            {
                free(*line);
                *line = NULL;
            }
            return (ret);
        }
        buf[fd][ret] = '\0';
        ret = ft_add_to_line(line, buf[fd]);
    }
    if (ret == -1)
        return (-1);
    (*line)[ret] = '\0';
    return (1);
}
//return 0 when end of file reached, less than 0 when error and 1 when the line is read and the end of file is not reached.
int             get_next_line(int fd, char **line)
{
    if (fd < 0 || !line || BUFFER_SIZE <= 0)
        return (-1);
    return (ft_get_next_line(fd, line));
}