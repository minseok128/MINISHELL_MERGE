/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_list_fuc1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 21:41:46 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_error(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

int	bi_find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**bi_divide_key_and_value(char *data)
{
	int		key_len;
	int		val_len;
	char	**key_and_value;

	key_len = bi_find_equal(data) + 1;
	if (key_len == 0)
		return (NULL);
	val_len = ft_strlen(data) - key_len + 1;
	key_and_value = malloc(sizeof(char *) * 2);
	if (key_and_value == NULL)
		bi_error();
	key_and_value[0] = malloc(sizeof(char) * key_len);
	if (key_and_value[0] == NULL)
		bi_error();
	key_and_value[1] = malloc(sizeof(char) * val_len);
	if (key_and_value[1] == NULL)
		bi_error();
	ft_strlcpy(key_and_value[0], data, key_len);
	ft_strlcpy(key_and_value[1], &data[key_len], val_len);
	return (key_and_value);
}

t_envp	*bi_make_list(char **key_and_value)
{
	t_envp	*lst;

	lst = malloc(sizeof(t_envp));
	if (lst == NULL)
		bi_error();
	if (key_and_value != NULL)
	{
		lst->key = key_and_value[0];
		lst -> value = key_and_value[1];
	}
	lst -> next = NULL;
	return (lst);
}

t_envp	*bi_make_linkedlist(char **envp)
{
	t_envp	*head;
	t_envp	*ptr;
	char	**key_and_value;
	int		i;

	head = bi_make_list(NULL);
	ptr = head;
	i = 0;
	while (envp[i] != NULL)
	{
		key_and_value = bi_divide_key_and_value(envp[i]);
		ptr -> next = bi_make_list(key_and_value);
		free(key_and_value);
		ptr = ptr -> next;
		i++;
	}
	return (head);
}
