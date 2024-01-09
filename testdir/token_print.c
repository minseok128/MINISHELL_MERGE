/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:43:00 by michang           #+#    #+#             */
/*   Updated: 2024/01/01 21:43:04 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	tk_print(t_vector *tokens)
{
	int	i;

	printf("\n[TOKEN] DONE!\n");
	return (0);
	while (i < tokens->size)
	{
		printf("%s[%d]", ((t_token *)(tokens->items[i]))->str);
		printf("[%d]", ((t_token *)(tokens->items[i]))->type);
		if (i + 1 != tokens->size)
			printf(" ==> ");
		i++;
	}
	printf("\n");
	return (0);
}