/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thpool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:35:07 by ovirchen          #+#    #+#             */
/*   Updated: 2018/02/04 21:51:51 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_THPOOL_H
# define FT_THPOOL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>

# define SPACE(x) x == '\n' || x == '\t' || x == '\v' || x == '\f' || x == '\r'
# define THRDS 8
# define COUNTER 100000

typedef struct		s_file
{
	int				infile;
	int				contrast;
	unsigned char	*image;
	char			*result;
	char			*comments;
	int				size_x;
	int				size_y;
	int				max;
	size_t			cur_pos;
	char			*outfile;
	size_t			size;
	pthread_cond_t	lock;
	pthread_mutex_t	mut;
}					t_file;

char				*join_free(char *s1, char *s2);
void				ft_get_image(t_file **zile);
void				ft_error(void);
void				ft_get_by_pool(t_file **file);

#endif
