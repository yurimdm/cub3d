/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_attrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:13:38 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:13:38 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

void	parse_texture(char **dst, char *s)
{
	char	*trimmed;

	if (*dst)
		error_exit("Duplicate texture definition");
	s = skip_spaces(s);
	if (!*s)
		error_exit("Empty texture path");
	trimmed = ft_strtrim(s, " \t");
	if (!trimmed)
		error_exit("Memory error");
	if (!*trimmed)
	{
		free(trimmed);
		error_exit("Empty texture path");
	}
	*dst = trimmed;
}

static int	parse_component(char **s)
{
	int	val;

	if (!ft_isdigit(**s))
		error_exit("Invalid color value");
	val = 0;
	while (ft_isdigit(**s))
	{
		val = val * 10 + (**s - '0');
		if (val > 255)
			error_exit("Color value out of range [0,255]");
		(*s)++;
	}
	return (val);
}

static void	expect_comma(char **s, int idx)
{
	*s = skip_spaces(*s);
	if (idx < 2)
	{
		if (**s != ',')
			error_exit("Color must be in R,G,B format");
		(*s)++;
	}
}

static void	parse_rgb(int *rgb, char *s)
{
	int	i;

	s = skip_spaces(s);
	i = 0;
	while (i < 3)
	{
		s = skip_spaces(s);
		rgb[i] = parse_component(&s);
		expect_comma(&s, i);
		i++;
	}
	if (*s != '\0')
		error_exit("Trailing characters in color value");
}

void	parse_color(int *rgb, int *set_flag, char *s)
{
	if (*set_flag)
		error_exit("Duplicate color definition");
	parse_rgb(rgb, s);
	*set_flag = 1;
}
