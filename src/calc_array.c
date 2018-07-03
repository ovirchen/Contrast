/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:47:27 by afarapon          #+#    #+#             */
/*   Updated: 2018/02/04 22:50:03 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_thpool.h"

void		*ft_calc_pixel(void *zile)
{
	t_file			*file;
	size_t			cur;
	int				num;
	size_t			target;

	file = *(t_file**)zile;
	cur = file->cur_pos;
	file->cur_pos += COUNTER;
	target = cur + COUNTER;
	pthread_cond_signal(&file->lock);
	while (cur < target)
	{
		if (cur >= (file->size))
			pthread_exit(0);
		num = ((file->image[cur] - file->max / 2) *
			file->contrast / 100) + file->max / 2;
		num = num >= file->max ? file->max : num;
		sprintf(file->result + (cur * 4), "%03d%c",
			num, (cur % 20) ? ' ' : '\n');
		cur++;
	}
	pthread_exit(0);
}

void		ft_get_by_pool(t_file **zile)
{
	pthread_t		thrds[THRDS];
	int				i;
	size_t			size;
	t_file			*file;

	file = *zile;
	pthread_mutex_init(&file->mut, NULL);
	pthread_cond_init(&file->lock, NULL);
	size = file->size_x * file->size_y;
	file->result = ft_strnew(sizeof(char) * (size * 4 + 1));
	while (file->cur_pos < size)
	{
		i = -1;
		ft_memset(&thrds, 0, sizeof(pthread_t) * THRDS);
		while (++i < THRDS && pthread_create(&thrds[i], NULL,
			&ft_calc_pixel, &file))
			pthread_cond_wait(&file->lock, &file->mut);
		i = -1;
		while (++i < THRDS)
			pthread_join(thrds[i], NULL);
	}
}
