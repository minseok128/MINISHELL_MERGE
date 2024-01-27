/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:59:53 by michang           #+#    #+#             */
/*   Updated: 2024/01/25 15:59:54 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*trtv_join_s(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!new)
		exit(1);
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcat(new + s1_len, s2, s1_len + s2_len + 1);
	free(s1);
	free(s2);
	return (new);
}

void	trtv_node_free(t_tr_node *node)
{
	int	i;

	if (!node)
		return ;
	trtv_node_free(node->left);
	trtv_node_free(node->right);
	if (node->word_split)
	{
		i = 0;
		while (i < node->word_split->size)
		{
			if (node->word_split->items[i])
				free(node->word_split->items[i]);
			i++;
		}	
		vec_free(node->word_split);
		free(node->word_split);
	}
	free (node);
}
