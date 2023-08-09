/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/09 20:18:33 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_split_pos(char *str, char c, int pos)
{
	char	**tab;
	int		delimiter_pos;
	int		current_pos;
	int		i;

	i = 0;
	ft_strlen(str);
	tab = (char **)malloc(3 * sizeof(char *));
	delimiter_pos = -1;
	current_pos = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == c)
		{
			current_pos++;
			if (current_pos == pos)
			{
				delimiter_pos = i;
				break ;
			}
		}
		i++;
	}
	if (delimiter_pos == -1)
	{
		printf("ERROR\n");
		exit(1);
	}
	tab[0] = ft_substr(str, 0, delimiter_pos);
	tab[1] = ft_substr(str, delimiter_pos, ft_strlen(str));
	tab[2] = NULL;
	return (tab);
}

// int	main(void)
// {
// 	char	*input;
// 	char	**result;

// 	input = "abcd,77777,dddd";
// 	result = ft_split_pos(input, ',', 4);
// 	for (int i = 0; result[i] != NULL; i++)
// 	{
// 		printf("tab[%d] = %s\n", i, result[i]);
// 		free(result[i]);
// 	}
// 	free(result);
// 	return (0);
// }
