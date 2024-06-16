/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/17 07:09:37 by flaghata         ###   ########.fr       */
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
        printf("[%s] %s\n", line, redi->file_name);
       // dup2(pipefd[1], STDIN_FILENO);
		if (line == NULL)
			break;
        
        printf("%s %s %zu \n", line, redi->file_name,ft_strlen(redi->file_name));
		if (!ft_strncmp(line, redi->file_name, ft_strlen(redi->file_name)))
		{
            printf("end!!!!\n");
			//ft_free(line);
			break;
		}
        
        printf("here:%s\n",line);
		add_new_line = ft_strjoin(line, "\n");
		tmp = ft_strjoin(res, add_new_line);
        printf("here  :%s\n",tmp);
        //dup2(backup, STDIN_FILENO);
        //free(res);
		//ft_free(add_new_line);
		res = tmp;
		//ft_free(line);
	}
    printf("\x1b[31mheredoc\x1b[39m\n");
    printf("\x1b[31m %s %zu\x1b[39m\n",res, ft_strlen(res));
   // write(pipefd[0], res, ft_strlen(res));
	//ft_putstr_fd(pipefd[PIPE_WRITE], res);
    return (res);
	//ft_free(res);
    //ft_free(add_new_line);
    //ft_free(line);
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
    //int pipefd[2];
    //int backup;
    static char *z;

    printf("Redirecting type: %d, file: %s\n", redi->type, redi->file_name);

    if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI || redi->type == APPEND_OUTPUT_REDI)
    {
        printf("Standard redirection\n");
        printf("Standard FD duplicated: %d to %d\n", redi->fd_file, redi->fd);
        redi->fd_backup = dup(STDIN_FILENO);
        dup2(redi->fd_file,STDOUT_FILENO);
        if (z)
        {
            printf("%s\n", z);
            z = "\0";
        }
        printf("Standard FD duplicated!: %d to %d\n", redi->fd_file, redi->fd);
        dup2(redi->fd_backup,STDOUT_FILENO);
        close(redi->fd_file);
    }
    //heredoc
    else
    {
        printf("Here document redirection\n");
        //pipe(pipefd);
        //dup2(redi->fd_file, STDIN_FILENO);
        //close(pipefd[0]);
        z = here_doc(redi);
        printf("z=%s\n",z);
        //dup2(pipefd[0], STDIN_FILENO);
        // close(pipefd[1]);
        //close(backup);
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
	// if (redi->type == HEREDOC_REDI)
	// 	return ;
    printf("restore\n");
	ft_dup2(redi->fd_backup, STDOUT_FILENO);
    ft_close(redi->fd_backup);
	redi->fd_backup = -1;
}