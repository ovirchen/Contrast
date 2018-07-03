/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:47:25 by ovirchen          #+#    #+#             */
/*   Updated: 2018/02/04 22:53:01 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_thpool.h"

void		ft_error(void)
{
	write(1, "error\n", 6);
	exit(0);
}

static int	ft_usage(t_file file)
{
	if (file.infile)
		close(file.infile);
	write(1,
"Usage : > ft_contrast -f <input_file> -c <0..100> -o <output_file>\n", 67);
	return (1);
}

static int	check_input(int ac, char **av, t_file **zile)
{
	int		i;
	t_file	*file;

	i = 1;
	file = *zile;
	file->contrast = -1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-f") && ++i < ac && !file->infile)
		{
			if ((file->infile = open(av[i], O_RDONLY)) == -1)
				ft_error();
			file->outfile = av[i];
		}
		if (ft_strequ(av[i], "-c") && ++i < ac && ft_isdigit(av[i][0]))
			file->contrast = ft_atoi(av[i]);
		if (ft_strequ(av[i], "-o") && ++i < ac)
			file->outfile = av[i];
		i++;
	}
	if (file->contrast > 100 || file->contrast == -1
		|| !file->infile || !file->outfile)
		return (0);
	return (1);
}

static void	get_inform(t_file **file)
{
	char	*buf;
	char	*tmp;
	int		i;

	i = 1;
	while (i < 4 && get_next_line((*file)->infile, &buf) > 0)
	{
		tmp = buf;
		(*file)->comments = join_free((*file)->comments, buf);
		(*file)->comments = join_free((*file)->comments, "\n");
		if (buf[0] == '#')
			i--;
		if (i == 2)
		{
			(*file)->size_x = ft_atoi(buf);
			while (*buf && *buf != ' ')
				buf++;
			if (!((*file)->size_y = ft_atoi(buf)) || !(*file)->size_x)
				ft_error();
		}
		if (i++ == 3)
			(*file)->max = ft_atoi(buf);
		free(tmp);
	}
}

int			main(int ac, char **av)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	ft_bzero(file, sizeof(t_file));
	if (ac == 1 || check_input(ac, av, &file) == 0)
		return (ft_usage(*file));
	file->comments = ft_strnew(0);
	get_inform(&file);
	ft_get_image(&file);
	free(file->comments);
	free(file);
	return (0);
}
