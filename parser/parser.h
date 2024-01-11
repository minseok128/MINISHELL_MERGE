/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:51 by michang           #+#    #+#             */
/*   Updated: 2023/09/09 14:46:52 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft_s/libft_s.h"
# include "../btin/btin.h"

// tokenizer
typedef enum e_token_type {
	T_AND = 101,
	T_OR,
	T_PIPE,
	T_PARENT_L,
	T_PARENT_R,
	T_REDIR_S_L,
	T_REDIR_S_R,
	T_REDIR_D_L,
	T_REDIR_D_R,
	T_WORD,
	T_NEWLINE,
	T_UNDEFINED = 199
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}	t_token;

t_token			*tk_lstlast(t_token *lst);
void			tk_lstadd_back(t_token **lst, t_token *new_token);
t_token			*tk_alloc_s(t_token_type type, char *str);
t_token_type	tk_is_meta_char(char *str);

// tree maker
typedef enum e_tr_type {
	TR_LIST = 201,
	TR_PIPELINE,
	TR_COMMAND,
	TR_COMMAND_PART
}	t_tr_type;

typedef struct s_tr_node {
	t_tr_type			bnf_type;
	t_token				*tk;
	struct s_tr_node	*left;
	struct s_tr_node	*right;
	t_vector			word_split;
}	t_tr_node;

int				mktr_print_unexpected(char *str);
int				mktr_free_node(t_tr_node *node);
t_tr_node		*mktr_alloc_s(t_tr_type bnf_type, t_token *tk);
int				mktr_list(t_tr_node **head, t_token **tk_now);
int				mktr_pipeline(t_tr_node **head, t_token **tk_now);
int				mktr_command(t_tr_node **head, t_token **tk_now);
int				mktr_command_part(t_tr_node **head, t_token **tk_now);

// trtv
void			trtv_env_cmdp(char *word, char **e_w, t_envs *envsp);
void			trtv_word_split(char *word, t_tr_node *node);
void			trtv_quotes_removal(t_vector *word_split);
int				trtv_comd_part_travel(t_tr_node *node, t_cmd *cmd);
void			trtv_comd_travel(t_tr_node *node, t_cmd *cmd);
void			trtv_list_travel(t_tr_node *node);
int				trtv_pipe_travel(t_tr_node *node, t_vector *cmds);

# define APPEND 999

typedef struct s_cmd
{
	t_vector		argv;
	char			*in_file;
	char			*out_file;
	int				prev_out;
	int				type;
}	t_cmd;

// test
int				test_tr_print_tree(t_tr_node *root, char *str);
void			test_print_node(t_tr_node *node);
void			test_print_command_part(t_tr_node *node);
void			test_cmds_print(t_vector *cmds);

typedef struct s_parser_info {
	char		*line;
	t_token		*tk_head;
	t_tr_node	*root;
}	t_parser_info;

#endif