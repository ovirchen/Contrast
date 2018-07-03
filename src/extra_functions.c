/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 16:19:21 by ovirchen          #+#    #+#             */
/*   Updated: 2018/02/04 22:48:53 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_thpool.h"

static void		get_next_lie(t_file **zile)
{
	char				*temp;
	unsigned char		*tmp;
	char				*forfree;
	t_file				*file;
	int					ret;

	file = *zile;
	file->size = file->size_x * file->size_y;
	tmp = file->image;
	temp = (char*)malloc(sizeof(char) * file->size * 7);
	if ((ret = read(file->infile, temp, file->size * 7)) == -1)
		ft_error();
	temp[ret] = '\0';
	forfree = temp;
	while (*temp)
	{
		if (ft_isdigit(*temp))
			*tmp++ = ft_atoi(temp);
		while (*temp && ft_isdigit(*temp))
			temp++;
		while (*temp && (SPACE(*temp) || *temp == ' '))
			temp++;
	}
	free(forfree);
}

char			*join_free(char *s1, char *s2)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

static void		ft_put_data(t_file *file)
{
	int		out;

	if ((out = open(file->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_error();
	write(out, file->comments, ft_strlen(file->comments));
	printf("Save into file...\n");
	dprintf(out, "%s\n", file->result);
	free(file->result);
	free(file->image);
	printf("Done...\n");
	close(out);
}

void			ft_get_image(t_file **zile)
{
	t_file			*file;

	file = *zile;
	file->image = (unsigned char*)malloc(sizeof(unsigned char) *
		(file->size_x * file->size_y + 1));
	printf("Reading...\n");
	get_next_lie(zile);
	close(file->infile);
	printf("Calculation...\n");
	ft_get_by_pool(zile);
	ft_put_data(file);
}
