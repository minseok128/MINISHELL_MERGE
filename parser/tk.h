/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:51 by michang           #+#    #+#             */
/*   Updated: 2023/09/09 14:46:52 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TK_H
# define TK_H
# include "../minishell.h"

typedef enum e_token_type {
	T_AND = 10,
	T_OR,
	T_PIPE,
	T_PARENT_L,
	T_PARENT_R,
	T_REDIR_S_L,
	T_REDIR_S_R,
	T_REDIR_D_L,
	T_REDIR_D_R,
	T_WORD,
	T_NULL = 98,
	T_UNDEFINED = 99
} t_token_type;

typedef	struct s_token {
	t_token_type	type;
	int				flag;
	char			*str;
	struct s_token *next;
} t_token;

int				ft_isspace(char	c);
t_token			*tk_lstlast(t_token *lst);
void			tk_lstadd_back(t_token **lst, t_token *new_token);
t_token			*tk_alloc_s(t_token_type type, char *str);
void			tk_print(t_token *tk);
t_token_type	tk_is_meta_char(char *str);

#endif
