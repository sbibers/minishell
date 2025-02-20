/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:20:20 by sbibers           #+#    #+#             */
/*   Updated: 2024/08/29 17:27:35 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				size;
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	func(unsigned int i, char c)
{
	printf("index : %d || char : %c\n", i, c);
	return (c);
}
// 
int	main(void)
{
	char	str[10];
	char	*result;

	str[10] = "hello.";
 	printf("The result is : %s\n", str);
 	result = ft_strmapi(str, func);
	printf("The result is : %s\n", result);
 	return (0);
}
*/
