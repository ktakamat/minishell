/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/15 13:32:46 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redirect(t_redirect *redi)
{
	if (redi->type == INPUT_REDI)
		return (open(redi->file_name, O_RDONLY, 0));
	if (redi->type == OUTPUT_REDI)
		return (open(redi->file_name, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	return (open(redi->file_name, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

static char*	here_doc(t_redirect *redi)
{
	char	*add_new_line;
	char	*tmp;
	char	*line;
	char	*res;

	res = ft_strdup("");
    printf("\x1b[31mheredoc\x1b[39m\n");
	while (true)
	{
		line = readline("> ");
       // printf("[%s] %s\n", line, redi->file_name);
       // dup2(pipefd[1], STDIN_FILENO);
		if (line == NULL)
		{
			break;
		}
        
       // printf("%s %s %zu \n", line, redi->file_name,ft_strlen(redi->file_name));
		if (!ft_strncmp(line, redi->file_name, ft_strlen(redi->file_name)))
		{
			//ft_free(line);
			break;
		}
        
      //  printf("here:%s\n",line);
		add_new_line = ft_strjoin(line, "\n");
		tmp = ft_strjoin(res, add_new_line);
       // printf("here  :%s\n",tmp);
        //dup2(backup, STDIN_FILENO);
        //free(res);
		//ft_free(add_new_line);
		res = tmp;
		//ft_free(line);
	}
    // printf("\x1b[31mheredoc\x1b[39m\n");
    // printf("\x1b[31m %s %zu\x1b[39m\n",res, ft_strlen(res));
   // write(pipefd[0], res, ft_strlen(res));
	//ft_putstr_fd(pipefd[PIPE_WRITE], res);
    //ft_strlcpy(redi->heredoc_input, res, ft_strlen(res));
    return (res);
	//ft_free(res);
    //ft_free(add_new_line);
    //ft_free(line);
}

void	redirect(t_redirect *redi)
{
	// int	pipefd[2];
	// int	backup;

	if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI
		|| redi->type == APPEND_OUTPUT_REDI)
	{
		redi->fd_backup = dup(redi->fd);
		dup2(redi->fd_file, redi->fd);
		redi->heredoc_input = "";
		//close(redi->fd_file);
	}
	else
	{
		printf("Here document redirection\n");
		redi->heredoc_input = here_doc(redi);
		// backup = dup(STDIN_FILENO);
		// pipe(pipefd);
		// here_doc(redi, pipefd);
		// dup2(pipefd[0], STDIN_FILENO);
		// close(pipefd[0]);
		// close(pipefd[1]);
		// dup2(backup, STDIN_FILENO);
		// close(backup);
	}
}

int	exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
{
	while (redi != NULL)
	{
		printf("(%s)\n",redi->file_name);
		redi->file_name = expansion(redi->file_name, dir, env_var);
		printf("(%s)\n",redi->file_name);
		if (redi->type != HEREDOC_REDI)
		{
			printf("(%s)!!!\n",redi->file_name);
			redi->fd_file = open_redirect(redi);
			printf("(%d)\n",redi->fd_file);
			if (redi->fd_file == -1)
			{
				dir->error.error_num = 1;
				return (FAILURE);
			}
		}

		redirect(redi);	
		redi = redi->next;
	}
	return (SUCCESS);
}

void	restore_fd(t_redirect *redi)
{
	if (redi == NULL)
		return ;
	printf("んな\n");
	if (redi->fd_backup != -1) // バックアップが有効な場合にのみ復元
	{
		ft_dup2(redi->fd_backup, redi->fd); // 元のファイルディスクリプタに戻す
		printf("んな？\n");
		ft_close(redi->fd_backup);
		printf("んな電鉄\n");
		redi->fd_backup = -1; // 無効な状態にリセット
	}
}
