/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:16:00 by afarapon          #+#    #+#             */
/*   Updated: 2018/02/03 23:20:17 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char		*end;

	if (s)
	{
		while ((*s == ' ' || *s == '\n' || *s == '\t') && *s)
			s++;
		end = (char*)s + ft_strlen((char*)s) - 1;
		while (*end == ' ' || *end == '\n' || *end == '\t')
			end--;
		return (ft_strsub(s, 0, end - s - 1));
	}
	return (NULL);
}
