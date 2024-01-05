/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:19:42 by michang           #+#    #+#             */
/*   Updated: 2024/01/05 14:19:43 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BTIN_H
# define BTIN_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>

typedef struct s_envsp
{
	char			*key;
	char			*value;
	struct s_envsp	*next;
}	t_envs;

void	btin_env(t_envs *envsp);
t_envs	*btin_make_envsp(char **envp);
t_envs	*btin_find_node(t_envs *envsp, char *key);

#endif
