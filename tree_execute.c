/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:17:18 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 22:54:55 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tr_strjoin(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len1;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1) + 1;
	str = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	**tr_get_input_envp(t_envp *envp, int len, int i)
{
	t_envp	*tmp;
	char	**input_envp;

	tmp = envp;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	input_envp = malloc(sizeof(char *) * (len + 1));
	if (input_envp == NULL)
		bi_error();
	tmp = envp;
	while (tmp != NULL)
	{
		input_envp[i] = tr_strjoin(tmp->key, tmp->value, '=');
		if (input_envp[i] == NULL)
			bi_error();
		i++;
		tmp = tmp->next;
	}
	input_envp[i] = NULL;
	return (input_envp);
}

void	*tr_free2(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	return (NULL);
}

char	*tr_check_path(char *cmd, t_envp *envp, int i)
{
	char	**envp_path;
	char	*path;

	while (envp != NULL && strncmp(envp->key, "PATH", 5) != 0)
		envp = envp->next;
	if (envp == NULL) // 환경 변수에 PATH가 없는 경우
		return (cmd);
	envp_path = ft_split(envp->key, ':');
	i = 0;
	while (envp_path[i] != NULL)
	{
		path = tr_strjoin(envp_path[i++], cmd, '/');
		if (path == NULL)
			bi_error();
		if (access(path, F_OK) == 0)
		{
			free(cmd);
			tr_free2(envp_path);
			return (path);
		}
		free(path);
	}
	tr_free2(envp_path);
	return (cmd);
}

void	tr_execute(t_tree *tree, t_envp *envp)
{
	char	**cmd;
	char	**input_envp;

	// printf("%s\n", tree->str);
	cmd = ft_split(tree->str, ' ');
	if (cmd == NULL)
		bi_error();
	if (access(cmd[0], F_OK) == -1)
		cmd[0] = tr_check_path(cmd[0], envp->next, 0);
	input_envp = tr_get_input_envp(envp->next, 0, 0);
	if (execve(cmd[0], cmd, input_envp) == -1)
		bi_error();
}
