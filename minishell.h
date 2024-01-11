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

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include "libft_s/libft_s.h"

# define MODE_SHELL 0
# define MODE_DEFAULT 1
# define MODE_IGNORE 2
# define APPEND 999

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

typedef struct s_envsp
{
	char			*key;
	char			*value;
	struct s_envsp	*next;
}	t_envs;

typedef struct s_parser_info {
	char		*line;
	t_token		*tk_head;
	t_tr_node	*root;
}	t_parser_info;

typedef struct s_cmds
{
	t_vector		**argv;
	char			*in_file;
	char			*out_file;
	int				prev_out;
	int				type;
	struct s_cmds	*next;
}	t_cmds;
int				g_errno;

void			set_signal(int sig_int, int sig_quit);
int				tk_tokenize(char *str, t_token **token_head);
int				mktr_make_tree(t_token *tk_head, t_tr_node **root);
void			trtv_start(t_tr_node *root, t_envs *envsp);

// tk
t_token			*tk_lstlast(t_token *lst);
void			tk_lstadd_back(t_token **lst, t_token *new_token);
t_token			*tk_alloc_s(t_token_type type, char *str);
t_token_type	tk_is_meta_char(char *str);

// mktr
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
int				trtv_comd_part_travel(t_tr_node *node, t_cmds *cmd);
void			trtv_comd_travel(t_tr_node *node, t_cmds *cmd);
void			trtv_list_travel(t_tr_node *node, t_envs *envsp);
int				trtv_pipe_travel(t_tr_node *node, t_vector *cmds, t_envs *envsp);

// btin
void			btin_pwd(int fork_flag);
void			btin_export(t_cmds *cmds, t_envs *envsp, int error_code, int fork_flag);
void			btin_unset(t_cmds *cmds, t_envs *envsp, int fork_flag);
void			btin_cd(t_cmds *cmds, t_envs *envsp, int fork_flag);
void			btin_echo(t_cmds *cmds, int fork_flag);
void			btin_env(t_envs *envsp, int fork_flag);
void			btin_exit(t_cmds *cmds, int fork_flag);
void			btin_out(int fork_flag, int error_code, char *errmsg);
int				btin_is_valid_identifier(char *str);
void			btin_print_declare_env(t_envs *envsp);
void			btin_free_key_and_value(char **key_and_value, char *key, char *value);
t_envs			*btin_make_envsp_node(char **key_and_value);
t_envs			*btin_make_envsp(char **envp);
t_envs			*btin_find_node(t_envs *envsp, char *key);
char			**btin_divide_key_and_value(char *env);

// ex
t_cmds			*ex_make_cmdsp(void);
void			ex_add_cmdsp_node(t_cmds *cmdsp, char **argv, char *in, char *out);
void			ex_process_command(t_cmds *cmdsp_head, t_envs *envsp);
void			ex_open_output_fd(t_cmds *cmdsp);
void			ex_open_input_fd(t_cmds *cmdsp);
void			ex_dup_to(int from, int to);
void			ex_execute(t_vector *cmds, t_envs *envsp, char **envp);
int				ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag);
char			*ex_strjoin_c(char const *s1, char const *s2, char c);
void			*ex_free_string_array(char **string_array);

// !test codes!
int				tk_print(t_token *tk);
int				test_tr_print_tree(t_tr_node *root, char *str);
void			test_print_node(t_tr_node *node);
void			test_print_command_part(t_tr_node *node);
void			test_cmds_print(t_vector *cmds);

#endif