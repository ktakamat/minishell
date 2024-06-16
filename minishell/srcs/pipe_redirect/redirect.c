/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/16 15:24:51 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void redirect_input(const char *filename) {
// 	int fd = open(filename, O_RDONLY);
// 	if (fd == -1) {
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (dup2(fd, STDIN_FILENO) == -1) {
// 		perror("dup2");
// 		exit(EXIT_FAILURE);
// 	}

// 	close(fd);
// }
// void	redirect_output(const char *filename)
// {
// 	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		exit(EXIT_FAILURE);
// 	}

// 	close(fd);
// }

// void redirect_append(const char *filename) 
// {
// 	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1) {
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		exit(EXIT_FAILURE);
// 	}

// 	close(fd);
// }


// void execute_here_document(const char *text)
// {
// 	size_t len = strlen(text);
// 	ssize_t written = write(STDOUT_FILENO, text, len);
// 	if (written != (ssize_t)len)	
// 	{
// 		perror("write");
// 		exit(EXIT_FAILURE);
// 	}
// }

int	open_redirect(t_redirect *redi)
{
	if (redi->type == INPUT_REDI)
		return (open(redi->file_name, O_RDONLY, 0));
	if (redi->type == OUTPUT_REDI)
		return (open(redi->file_name, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	return (open(redi->file_name, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

static void	here_doc(t_redirect *redi, int pipefd[2])
{
	char	*add_new_line;
	char	*tmp;
	char	*line;
	char	*res;

	res = ft_strdup("");
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (!ft_strncmp(line, redi->file_name, ft_strlen(redi->file_name)))
		{
			ft_free(line);
			break;
		}
		add_new_line = ft_strjoin(line, "\n");
		tmp = ft_strjoin(res, add_new_line);
		ft_free(res);
		ft_free(add_new_line);
		res = tmp;
		ft_free(line);
	}
	ft_putstr_fd(pipefd[PIPE_WRITE], res);
	ft_free(res);
}

// void	redirect(t_redirect *redi)
// {
// 	int		pipefd[2];
// 	int		backup;

// 	if (redi->type == INPUT_REDI | redi->type == OUTPUT_REDI
// 		|| redi->type == APPEND_OUTPUT_REDI)
// 	{
// 		redi->fd_backup = ft_dup(STDIN_FILENO);
// 		ft_dup2(redi->fd_file, redi->fd);
// 		return ;
// 	}
// 	else
// 	{
// 		backup = ft_dup(STDIN_FILENO);
// 		ft_pipe(pipefd);
// 		here_doc(redi, pipefd);
// 		ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
// 		ft_close(pipefd[PIPE_READ]);
// 		ft_close(pipefd[PIPE_WRITE]);
// 		ft_dup2(backup, STDIN_FILENO);
// 		close(backup);
// 	}
// 	return ;
// }
void redirect(t_redirect *redi)
{
    int pipefd[2];
    int backup;

    printf("Redirecting type: %d, file: %s\n", redi->type, redi->file_name);

    if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI || redi->type == APPEND_OUTPUT_REDI)
    {
        printf("Standard redirection\n");
        printf("Standard FD duplicated: %d to %d\n", redi->fd_file, redi->fd);
        redi->fd_backup = dup(STDIN_FILENO);
        dup2(redi->fd_file,STDOUT_FILENO);
        printf("Standard FD duplicated!: %d to %d\n", redi->fd_file, redi->fd);
        //close(redi->fd_file);
    }

    else
    {
        printf("Here document redirection\n");
        backup = dup(STDIN_FILENO);
        pipe(pipefd);
        here_doc(redi, pipefd);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        dup2(backup, STDIN_FILENO);
        close(backup);
    }
}

// int	exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
// {
// 	printf("exec_redirect\n");
// 	while (redi != NULL)
// 	{
// 		printf("redi->type: %d\n", redi->type);
// 		redi->file_name = expansion(redi->file_name, dir, env_var);
// 		if (redi->type != HEREDOC_REDI)
// 		{
// 			redi->fd_file = open_redirect(redi);
// 			if (redi->fd_file == -1)
// 			{
// 				dir->error.error_num = 1;
// 				return (FAILURE);
// 			}
// 		}
// 		redirect(redi);
// 		redi = redi->next;
// 	}
// 	return (SUCCESS);
// }

int exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
{
    printf("Entering exec_redirect\n");

    while (redi != NULL)
    {
        printf("redi->type: %d\n", redi->type);
        printf("Original redi->file_name: %s\n", redi->file_name);
        redi->file_name = expansion(redi->file_name, dir, env_var);
        printf("Expanded redi->file_name: %s\n", redi->file_name);

        if (redi->type != HEREDOC_REDI)
        {
            redi->fd_file = open_redirect(redi);
            if (redi->fd_file == -1)
            {
                dir->error.error_num = 1;
                printf("Failed to open redirect file\n");
                return FAILURE;
            }
        }

        printf("Redirecting...\n");
        //ここでコマンド実行する？
        redirect(redi);
        printf("Redirection done for type %d\n", redi->type);
        redi = redi->next;
    }

    return SUCCESS;
}

void	restore_fd(t_redirect *redi)
{
    printf("restore\n");
	if (redi == NULL)
		return ;
	if (redi->type == HEREDOC_REDI)
		return ;
    printf("restore\n");
	ft_dup2(redi->fd_backup, STDOUT_FILENO);
    ft_close(redi->fd_backup);
	redi->fd_backup = -1;
}