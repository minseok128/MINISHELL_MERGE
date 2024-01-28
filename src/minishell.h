/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:51 by michang           #+#    #+#             */
/*   Updated: 2024/01/26 20:30:14 by seonjo           ###   ########.fr       */
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
# include <dirent.h>
# include "../libft/libft.h"

# define MODE_SHELL 0
# define MODE_DEFAULT 1
# define MODE_IGNORE 2
# define MODE_HEREDOC 3
# define RD_AMBIGUOUS 256
# define RD_APPEND 512

typedef struct s_vector {
	void	**items;
	int		capacity;
	int		size;
}	t_vector;

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
	t_vector			*word_split;
}	t_tr_node;

typedef struct s_envsp
{
	char			*key;
	char			*value;
	struct s_envsp	*next;
}	t_envs;

typedef struct s_parser_info {
	char		*line;
	t_vector	*hdocs;
	t_token		*tk_head;
	t_tr_node	*root;
	int			eno;
}	t_parser_info;

typedef struct s_cmds
{
	t_vector		argv;
	char			*in_file;
	char			*out_file;
	int				prev_out;
	int				type;
	int				*enop;
	struct s_cmds	*next;
}	t_cmds;

int	*g_signal;

// default
void			parser_info_init(int argc, char **argv, t_parser_info *p_info);
void			parser_info_free(t_parser_info *p_info);
void			sig_set(int sig_int, int sig_quit);
void			sig_terminal_print_on(void);
void			sig_terminal_print_off(void);

// tk
int				tk_tokenize(char *str, t_token **token_head, int *eno);
t_token			*tk_lstlast(t_token *lst);
void			tk_lstadd_back(t_token **lst, t_token *new_token);
t_token			*tk_alloc_s(t_token_type type, char *str);
t_token_type	tk_is_meta_char(char *str);
void			tk_print_quote_error(char is_error);

// mktr
int				mktr_make_tree(t_parser_info *p_info, t_vector **hdocs);
int				mktr_print_unexpected(char *str, int *eno);
int				mktr_free_node(t_tr_node *node);
t_tr_node		*mktr_alloc_s(t_tr_type bnf_type, t_token *tk);
int				mktr_list(t_tr_node **head, t_token **tk_now, \
					t_parser_info *p_info, int *is_hs);
int				mktr_pipeline(t_tr_node **head, t_token **tk_now, \
					t_parser_info *p_info, int *is_hs);
int				mktr_command(t_tr_node **head, t_token **tk_now, \
					t_parser_info *p_info, int *is_hs);
int				mktr_command_part(t_tr_node **head, t_token **tk_now, \
					t_parser_info *p_info, int *is_hs);
int				mktr_heredoc(char **file_name, int *eno);
int				mktr_heredoc_open_file(char **file_name);
pid_t			mktr_heredoc_fork(int fd, char *limiter);

// trtv
int				trtv_list_travel(t_tr_node *node, t_envs *envsp, int *eno);
int				trtv_comd_part_travel(t_tr_node *node, t_cmds *cmd, \
					t_envs *envsp, int *eno);
int				trtv_comd_travel(t_tr_node *node, t_cmds *cmd, \
					t_envs *envsp, int *eno);
int				trtv_pipe_travel(t_tr_node *node, t_cmds *cmds_h, \
					t_envs *envsp, int *eno);
int				trtv_expansion(t_tr_node *node, t_envs *envsp, int *eno);
void			trtv_word_split(char *word, t_tr_node *node);
void			trtv_quotes_removal(t_vector *word_split);
void			trtv_wcard_expand(t_vector **word_split);
int				trtv_redir_l(t_cmds *cmd, t_vector *word_split);
int				trtv_redir_s_r(t_cmds *cmd, t_vector *word_split);
int				trtv_redir_d_r(t_cmds *cmd, t_vector *word_split);
char			*trtv_join_s(char *s1, char *s2);
void			trtv_node_free(t_tr_node *node);

// btin
void			btin_pwd(t_cmds *cmds, int fork_flag);
void			btin_export(t_cmds *cmds, t_envs *envsp, \
					int error_code, int fork_flag);
void			btin_unset(t_cmds *cmds, t_envs *envsp, int fork_flag);
void			btin_cd(t_cmds *cmds, t_envs *envsp, int fork_flag);
void			btin_echo(t_cmds *cmds, int fork_flag);
void			btin_env(t_cmds *cmds, t_envs *envsp, int fork_flag);
void			btin_exit(t_cmds *cmds, int fork_flag);
void			btin_out(int fork_flag, int error_code, char *errmsg, int *eno);
int				btin_is_valid_identifier(char *str);
void			btin_export_print(t_envs *envsp);
int				btin_export_error(t_cmds *cmds, char **key_value, char *str);
void			btin_free_key_and_value(char **key_and_value, \
					char *key, char *value);
t_envs			*btin_make_envsp_node(char **key_and_value);
t_envs			*btin_make_envsp(char **envp);
void			btin_free_envsp(t_envs *envsp);
t_envs			*btin_find_node(t_envs *envsp, char *key);
char			**btin_divide_key_and_value(char *env);
char			*btin_make_errmsg(char *s1, char *s2, char *s3);

// ex
t_cmds			*ex_cmdsp_init(int *eno);
t_cmds			*ex_cmdsp_add_back(t_cmds *cmdsp, int *eno);
void			ex_cmd_loop(t_cmds *cmdsp_head, t_envs *envsp);
void			ex_open_output_fd(t_cmds *cmdsp);
void			ex_open_input_fd(t_cmds *cmdsp);
void			ex_dup_to(t_cmds *cmds, int from, int to);
void			ex_execute(t_cmds *cmds, t_envs *envsp, char **envp);
int				ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag);
char			*ex_strjoin_c(char const *s1, char const *s2, char c);
void			*ex_free_string_array(char **string_array);
int				ex_open_btin_input_fd(t_cmds *cmds);
int				ex_open_btin_output_fd(t_cmds *cmds);
void			ex_all_close(t_cmds *cmdsp, char **envp);
int				ex_is_directory(char *cmd);
char			*ex_file_name_execute(t_cmds *cmds, t_envs *envsp, char *cmd);
void			ex_path_execute(t_cmds *cmds, char *cmd);

// libft_s
int				ft_jump_white_space(char *str);
int				ft_isspace(char c);
char			*ft_substr_s(char const *s, unsigned int start, size_t len);
char			*ft_itoa_s(int n);
char			*ft_strdup_s(const char *s1);
void			*ft_calloc_s(size_t count, size_t size);
char			*ft_strjoin_s(const char *s1, const char *s2);
void			vec_init(t_vector *v, int capacity);
void			vec_push_back(t_vector *v, void *item);
void			vec_free(t_vector *v);
void			vec_print(t_vector *v);
char			*ft_strchr_s(const char *s, int c);
char			**ft_split_s(const char *str, char c);
void			ft_parser_info_zero(t_parser_info *p_info);

#endif