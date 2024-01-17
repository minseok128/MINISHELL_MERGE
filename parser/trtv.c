/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:37:45 by michang           #+#    #+#             */
/*   Updated: 2024/01/17 14:59:00 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trtv_redir_s_l(t_cmds *cmd, char *file)
{
	int	fd;
	
	// 1. 만약 heredoc이 열려있으면 파일 삭제
	if ((cmd->type & RD_HEREDOC) != 0)
		if (unlink(cmd->in_file) == -1)
			exit(1);
	// 2. 구조체에 in_file과 type 초기화
	if (cmd->in_file != NULL)
		free(cmd->in_file);
	cmd->in_file = ft_strdup_s(file);
	cmd->type &= ~RD_HEREDOC;
	// 3. 파일 오픈
	fd = open(cmd->in_file, O_RDONLY);
	// 4. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 5. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}

int	trtv_redir_s_r(t_cmds *cmd, char *file)
{
	int	fd;
	
	// 1. 구조체에 out_file과 type 초기화
	if (cmd->out_file != NULL)
		free(cmd->out_file);
	cmd->out_file = ft_strdup_s(file);
	cmd->type &= ~RD_APPEND;
	// 2. 파일 오픈
	fd = open(cmd->out_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	// 3. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 4. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}

pid_t	trtv_redir_d_l_fork(int fd, char *limiter)
{
	char	*line;
	pid_t	pid;

	set_signal(MODE_IGNORE, MODE_IGNORE);
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		set_signal(MODE_HEREDOC, MODE_IGNORE);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
			{
				printf("\033[1A"); // 1줄 위로가는 ANSI 이스케이프 시퀀스
				printf("> ");
				exit(0);
			}
			else if (ft_strncmp(limiter, line, ft_strlen(line) + 1) == 0)
				exit(0);
			ft_putstr_fd(line, fd);
			free(line);
		}
	}
	return (pid);
}

int	trtv_redir_d_l_make_tmp_file(t_cmds *cmd)
{
	int		fd;
	int		num;
	char	*num_str;
	char	*file_name;

	num = 0;
	while (num < 2147483647)
	{
		num_str = ft_itoa_s(num);
		file_name = ft_strjoin_s("tmp", num_str);
		free(num_str);
		if (access(file_name, F_OK) == 0)
			num++;
		else
		{
			cmd->in_file = ft_strdup_s(file_name);
			fd = open(file_name, O_RDONLY);
			return (fd);
		}
		free(file_name);
	}
	cmd->in_file = ft_strdup_s("heredoc"); // 파일 만들기 실패시 heredoc 파일이 없다는 메시지
	return (-1);// heredoc파일을 못만들었을때 처리 방법 생각하기
}

int	trtv_redir_d_l(t_cmds *cmd, char *limiter)
{
	int		fd;
	int		status;
	
	// 1. 만약 heredoc이 열려있으면 파일 삭제
	if ((cmd->type & RD_HEREDOC) != 0)
		if (unlink(cmd->in_file) == -1)
			exit(1);
	// 2. 구조체에 in_file과 type 초기화
	// 		2a. 임시파일 이름을 확인하며 만들기
	if (cmd->in_file != NULL)
		free(cmd->in_file);
	fd = trtv_redir_d_l_make_tmp_file(cmd);
	if (fd == -1)
		return (-1);
	cmd->type |= RD_HEREDOC;
	waitpid(trtv_redir_d_l_fork(fd, limiter), &status, 0);
	set_signal(MODE_SHELL, MODE_SHELL);
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 1)
	{
		return (-1);
		// 구조체 만들기 종료
	}
	if (WIFSIGNALED(status) != 0)
	{
		return (-2);
		// 입력받은 트리 순회 종료
	}
	return (0);
}

int	trtv_redir_d_r(t_cmds *cmd, char *file)
{
	int	fd;
	
	// 1. 구조체에 out_file과 type 초기화
	if (cmd->out_file != NULL)
		free(cmd->out_file);
	cmd->out_file = ft_strdup_s(file);
	cmd->type |= RD_APPEND;
	// 2. 파일 오픈
	fd = open(cmd->out_file, O_APPEND | O_WRONLY);
	// 3. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 4. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}

int	trtv_comd_part_travel(t_tr_node *node, t_cmds *cmd)
{
	int	i;

	if (node->tk->type == T_WORD)
	{
		i = 0;
		while (i < node->word_split.size)
		{
			if (node->word_split.items[i])
				vec_push_back(&(cmd->argv), node->word_split.items[i]); 
			i++;
		}
	}
	if (node->tk->type == T_REDIR_S_L)
		trtv_redir_s_l(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_S_R)
		trtv_redir_s_r(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_D_L)
		trtv_redir_d_l(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_D_R)
		trtv_redir_d_r(cmd, node->tk->str);
	return (0);
}

void	trtv_comd_travel(t_tr_node *node, t_cmds *cmd)
{
	if (node->left && node->left->bnf_type == TR_COMMAND)
		trtv_comd_travel(node->left, cmd);
	else if (node->left && node->left->bnf_type == TR_COMMAND_PART)
		trtv_comd_part_travel(node->left, cmd);
	if (node->right && node->right->bnf_type == TR_COMMAND_PART)
		trtv_comd_part_travel(node->right, cmd);
}

int	trtv_pipe_travel(t_tr_node *node, t_cmds *cmds_h, t_envs *envsp)
{
	t_cmds		*cmd;

	if (node->left && node->left->bnf_type == TR_LIST)
	{
		trtv_list_travel(node->left, envsp);
		return (1);
	}
	else if (node->left && node->left->bnf_type == TR_PIPELINE)
		trtv_pipe_travel(node->left, cmds_h, envsp);
	if (node->left && node->left->bnf_type == TR_COMMAND)
	{
		cmd = ex_cmdsp_add_back(cmds_h);
		vec_init(&(cmd->argv), 1);
		trtv_comd_travel(node->left, cmd);
		vec_push_back(&(cmd->argv), 0);
	}
	if (node->right && node->right->bnf_type == TR_COMMAND)
	{
		cmd = ex_cmdsp_add_back(cmds_h);
		vec_init(&(cmd->argv), 1);
		trtv_comd_travel(node->right, cmd);
		vec_push_back(&(cmd->argv), 0);
	}
	return (0);
}

void	trtv_list_travel(t_tr_node *node, t_envs *envsp)
{
	t_cmds	*cmds_h;

	if (node->left && node->left->bnf_type == TR_LIST)
		trtv_list_travel(node->left, envsp);
	cmds_h = ex_cmdsp_init();
	if (node->left && node->left->bnf_type == TR_PIPELINE)
	{
		if (!trtv_pipe_travel(node->left, cmds_h, envsp))
		{
			// test_cmds_print(cmds_h);
			ex_cmd_loop(cmds_h, envsp);
		}
	}
	if (node->right && node->right->bnf_type == TR_PIPELINE)
	{
		if (!trtv_pipe_travel(node->right, cmds_h, envsp))
		{
			// test_cmds_print(cmds_h);
			ex_cmd_loop(cmds_h, envsp);
		}
	}
}

void	trtv_expansion_travel(t_tr_node *node, t_envs *envsp)
{
	char	*e_w;

	if (!node)
		return ;
	if (node->bnf_type == TR_COMMAND_PART)
	{
		e_w = ft_calloc_s(1, sizeof(char));
		trtv_env_cmdp(node->tk->str, &e_w, envsp);
		free(node->tk->str);
		node->tk->str = e_w;
		vec_init(&(node->word_split), 1);
		trtv_word_split(node->tk->str, node);
		trtv_quotes_removal(&(node->word_split));
	}
	trtv_expansion_travel(node->left, envsp);
	trtv_expansion_travel(node->right, envsp);
}

void	trtv_start(t_tr_node *root, t_envs *envsp)
{
	trtv_expansion_travel(root, envsp);
	trtv_list_travel(root, envsp);
}
