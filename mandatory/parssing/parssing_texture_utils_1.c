/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture_utils_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:37:11 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/30 14:44:26 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_block_rgb(t_rgb_info *bloc_2)
{
	if (bloc_2->type_color && (!ft_strncmp(bloc_2->type_color, "C", 2)
			|| !ft_strncmp(bloc_2->type_color, "F", 2)))
		return (0);
	else
		return (1);
}

void	valid_format_1(char c, bool *intoken, int *digit)
{
	if (c >= '0' && c <= '9')
	{
		(*intoken) = true;
		(*digit)++;
	}
}

void	valid_format_2(int intoken, int *digit, int *token)
{
	if (intoken)
	{
		(*digit)++;
		(*token)++;
	}
}

bool	valid_format(const char *input)
{
	int		token;
	int		digit;
	bool	intoken;
	int		i;

	i = -1;
	token = 0;
	digit = 0;
	intoken = false;
	while (input[++i] != '\0')
	{
		if (input[i] == ',')
		{
			if (!intoken)
				return (false);
			intoken = false;
			token++;
		}
		else if (input[i] == ' ' || (input[i] >= '0' && input[i] <= '9'))
			valid_format_1(input[i], &intoken, &digit);
		else
			return (false);
	}
	valid_format_2(intoken, &digit, &token);
	return (token == 3 && digit >= 3);
}

void	cont_of_coma(char *rgb)
{
	int	i;
	int	cont;

	cont = 0;
	i = 0;
	while (rgb[i] && rgb[i] == 32)
		i++;
	while (rgb[i])
	{
		if (rgb[i] == ',')
			cont++;
		i++;
	}
	if (cont != 2)
	{
		printf("ERROR\ninvalid form rgb");
		exit(1);
	}
	else
	{
		if (!valid_format(rgb))
		{
			(printf("ERROR\ninvalid form rgb"), exit(1));
		}
	}
}
