/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:45:51 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/16 16:45:51 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	 envi_error(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

int	 envi_find_equal(char *str)
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

char	**envi_divide_key_and_value(char *data)
{
	int		key_len;
	int		val_len;
	char	**key_and_value;

	key_len =  envi_find_equal(data) + 1;
	if (key_len == 0)
		return (NULL);
	val_len = ft_strlen(data) - key_len + 1;
	key_and_value = malloc(sizeof(char *) * 2);
	if (key_and_value == NULL)
		 envi_error();
	key_and_value[0] = malloc(sizeof(char) * key_len);
	if (key_and_value[0] == NULL)
		 envi_error();
	key_and_value[1] = malloc(sizeof(char) * val_len);
	if (key_and_value[1] == NULL)
		 envi_error();
	ft_strlcpy(key_and_value[0], data, key_len);
	ft_strlcpy(key_and_value[1], &data[key_len], val_len);
	return (key_and_value);
}

t_envp	*envi_make_list(char **key_and_value)
{
	t_envp	*lst;

	lst = malloc(sizeof(t_envp));
	if (lst == NULL)
		envi_error();
	if (key_and_value != NULL)
	{
		lst->key = key_and_value[0];
		lst -> value = key_and_value[1];
	}
	lst -> next = NULL;
	return (lst);
}

t_envp	*envi_make_linkedlist(char **envp)
{
	t_envp	*head;
	t_envp	*ptr;
	char	**key_and_value;
	int		i;

	head = envi_make_list(NULL);
	ptr = head;
	i = 0;
	while (envp[i] != NULL)
	{
		key_and_value = envi_divide_key_and_value(envp[i]);
		ptr -> next = envi_make_list(key_and_value);
		free(key_and_value);
		ptr = ptr -> next;
		i++;
	}
	return (head);
}

