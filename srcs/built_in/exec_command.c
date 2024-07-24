/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:36:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/24 18:31:09 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_heredoc_cat(t_redirect *redirect, t_directory *dir,
// 			t_env **env_var)
// {
// 	int		file;
// 	char	**args;

// 	file = open("./tmp", O_RDWR | O_CREAT | O_TRUNC,
// 			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	write(file, redirect->heredoc_input, strlen(redirect->heredoc_input));
// 	close(file);
// 	args = malloc(sizeof(char *) * 3);
// 	args[0] = strdup("cat");
// 	args[1] = strdup("tmp");
// 	args[2] = NULL;
// 	execute_from_path(args, dir, env_var);
// 	free(args[0]);
// 	free(args[1]);
// 	free(args);
// 	unlink(strcat(dir->path, "/tmp"));
// }

// void	handle_heredoc_grep(t_parser *node, t_redirect *redirect,
// 				t_directory *dir, t_env **env_var)
// {
// 	int		file;
// 	char	**args;

// 	file = open("./tmp", O_RDWR | O_CREAT | O_TRUNC,
// 			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	write(file, redirect->heredoc_input, strlen(redirect->heredoc_input));
// 	close(file);
// 	args = malloc(sizeof(char *) * 4);
// 	args[0] = strdup("grep");
// 	args[1] = strdup(node->cmd[1]);
// 	args[2] = strdup("tmp");
// 	args[3] = NULL;
// 	execute_from_path(args, dir, env_var);
// 	free(args[0]);
// 	free(args[1]);
// 	free(args[2]);
// 	free(args);
// 	unlink(strcat(dir->path, "/tmp"));
// }

// void	handle_heredoc(t_parser *node, t_redirect *redirect,
// 					t_directory *dir, t_env **env_var)
// {
// 	if (!strcmp(node->cmd[0], "cat"))
// 		handle_heredoc_cat(redirect, dir, env_var);
// 	else if (!strcmp(node->cmd[0], "grep"))
// 		handle_heredoc_grep(node, redirect, dir, env_var);
// }

// void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
// {
// 	t_redirect	*head;

// 	head = node->redirect;
// 	if (exec_redirect(node->redirect, dir, env_var) == FAILURE)
// 		return ;
// 	if (is_builtins(node->cmd[0]))
// 		exec_builtin(node->cmd, dir, env_var);
// 	else if (!node->redirect || node->redirect->type != HEREDOC_REDI)
// 		execute_from_path(node->cmd, dir, env_var);
// 	else
// 		handle_heredoc(node, node->redirect, dir, env_var);
// 	restore_fd(head);
// }

// void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
// {
// 	t_redirect	*head;

// 	head = node->redirect;
// 	if (exec_redirect(node->redirect, dir, env_var) == FAILURE)
// 		return ;
// 	if (!node->cmd[0])
// 	{
// 		restore_fd(head);
// 		return ;
// 	}
// 	if (is_builtins(node->cmd[0]))
// 		exec_builtin(node->cmd, dir, env_var);
// 	else
// 	{
// 		if (!node->redirect || node->redirect->type != HEREDOC_REDI)
// 			execute_from_path(node->cmd, dir, env_var);
// 		else
// 		{
// 			head = node->redirect->next;
// 			if (!ft_strcmp(node->cmd[0], "cat"))
// 			{
// 				int file;
//    				file = open("./tmp",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR
						// | S_IWUSR | S_IRGRP | S_IROTH);
// 				write(file, node->redirect->heredoc_input,
					// ft_strlen(node->redirect->heredoc_input));
// 				close(file);
// 				char **a;
// 				a = malloc(sizeof(char *) * 3);
// 				a[0] = malloc(sizeof(char) * 4);
// 				a[1] = malloc(sizeof(char) * 4);
// 				a[2] = 0;
// 				ft_strcpy(a[0],"cat");
// 				ft_strcpy(a[1],"tmp");
// 				execute_from_path(a, dir, env_var);
// 				free(a[0]);
// 				free(a[1]);
// 				free(a[2]);
// 				free(a);
// 				unlink(ft_strcat(dir->path,"/tmp"));
// 			}
// 			if (!ft_strcmp(node->cmd[0], "grep"))
// 			{
// 				int file;
//    				file = open("./tmp",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR
						// | S_IWUSR | S_IRGRP | S_IROTH);
// 				write(file, node->redirect->heredoc_input,
					// ft_strlen(node->redirect->heredoc_input));
// 				close(file);
// 				char **a;
// 				a = malloc(sizeof(char *) * 4);
// 				a[0] = malloc(sizeof(char) * 5);
// 				printf("%lu %s}}}\n",strlen(node->redirect->file_name),
						// node->redirect->file_name);
// 	a[1] = malloc(sizeof(char) * (strlen(node->redirect->file_name) + 1));
// 				a[2] = malloc(sizeof(char) * 4);
// 			 	a[3] = 0;
// 				ft_strcpy(a[0], "grep");
// 				ft_strcpy(a[1], node->redirect->file_name);
// 				ft_strcpy(a[2], "tmp");
// 				execute_from_path(a, dir, env_var);
// 				free(a[0]);
// 				free(a[1]);
// 				free(a[2]);
// 				free(a[3]);
// 				free(a);
// 				unlink(ft_strcat(dir->path,"/tmp"));
// 			}
// 		}
// 	}
// 	return (restore_fd(head));
// }

void	write_tmp_file(int file, t_redirect *redirect)
{
	while (49)
	{
		write(file, redirect->heredoc_input, ft_strlen(redirect->heredoc_input));
		if (redirect->next != NULL && redirect->next->type == HEREDOC_REDI)
			redirect = redirect->next;
		else{
			close(file);
			break;
		}
	}
}

void	handle_cat_heredoc(t_redirect *redirect, t_directory *dir,
		t_env **env_var)
{
	int		file;
	char	**args;

	args = malloc(sizeof(char *) * 3);
	file = open("./tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	// heredocのノード一個の内容しか読み込んでなかったのが原因なので、その後に続くheredocも再起的に書き込むようにした
	write_tmp_file(file, redirect);
	args = malloc(sizeof(char *) * 3);
	args[0] = malloc(sizeof(char) * 4);
	args[1] = malloc(sizeof(char) * 4);
	args[2] = NULL;
	ft_strcpy(args[0], "cat");
	ft_strcpy(args[1], "tmp");
	execute_from_path(args, dir, env_var);
	free(args[0]);
	free(args[1]);
	free(args[2]);
	free(args);
	unlink(ft_strcat(dir->path, "/tmp"));
}

void	handle_grep_heredoc(t_redirect *redirect, t_directory *dir,
		t_env **env_var)
{
	int		file;
	char	**args;

	file = open("./tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	//write(file, redirect->heredoc_input, ft_strlen(redirect->heredoc_input));
	// こっちにもいる予感がした。いらなかったら↑のに戻してください
	write_tmp_file(file, redirect);
	close(file);
	args = malloc(sizeof(char *) * 4);
	args[0] = malloc(sizeof(char) * 5);
	args[1] = malloc(sizeof(char) * (strlen(redirect->file_name) + 1));
	args[2] = malloc(sizeof(char) * 4);
	args[3] = NULL;
	ft_strcpy(args[0], "grep");
	ft_strcpy(args[1], redirect->file_name);
	ft_strcpy(args[2], "tmp");
	execute_from_path(args, dir, env_var);
	free(args[0]);
	free(args[1]);
	free(args[2]);
	free(args[3]);
	free(args);
	unlink(ft_strcat(dir->path, "/tmp"));
}

void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
{
	t_redirect	*head;

	head = node->redirect;
	if (exec_redirect(node->redirect, dir, env_var) == FAILURE)
		return ;
	//printf("sss%s %s",node->cmd[0], node->redirect->heredoc_input);
	if (!node->cmd[0])
	{
		return (restore_fd(head));
	}
	if (is_builtins(node->cmd[0]))
		exec_builtin(node->cmd, dir, env_var);
	else
	{
		// if (!node->redirect || node->redirect->type != HEREDOC_REDI)
			execute_from_path(node->cmd, dir, env_var);
	// 	else
	// 	{
	// 		// restore対象のファイルディスクリプタを、heredocじゃないとこまで飛ばす
	// 		//　HEREDOC_REDIかどうかで判定すればよかった...
	// 		while (49)
	// 		{
	// 			if (head->next == NULL)
	// 				break;
	// 			head = head->next;
	// 			if (head->type != HEREDOC_REDI)
	// 				break;
	// 		}
	// 		if (!ft_strcmp(node->cmd[0], "cat"))
	// 			handle_cat_heredoc(node->redirect, dir, env_var);
	// 		else if (!ft_strcmp(node->cmd[0], "grep"))
	// 			handle_grep_heredoc(node->redirect, dir, env_var);
	// 	}	
	}
	restore_fd(head);
}
