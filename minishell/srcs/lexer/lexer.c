/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:25:57 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/13 06:19:46 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_kind(t_token *lexer, int j)
{
	t_token	*tmp;
	int	i;

	(void)j;
	i = 0;
	tmp = lexer;
	// while (tmp != NULL && i < j && tmp->kind != TK_PIPE)
	while (tmp != NULL)
	{
		// if (tmp->kind == TK_CMD)
		// 	tmp->kind = TK_PIPE;
		tmp = tmp->next;
		i++;
	}
}

t_token	*lexer(char *line)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lexer = NULL;
	while (*line != '\0' && line)
	{
		if (split_space(&line, line))
			continue ;
		else if (*line == '<' || *line == '>')
			token = split_red(&line, line);
		else if (*line == '|')
		{
			printf("split_pipe %s\n",line);
			j = i;
			token = split_pipe(&line, line);
		}
		else if (check_word(line))
			token = split_word(&line, line);
		else
			ft_error();
		if (lexer == NULL)
			lexer = token;
		else
		{
			tmp->next = token;
		}
		i++;
		tmp = token;
	}
	pipe_kind(lexer, j);
	tmp = lexer;
	while (tmp!= NULL)
	{
		i = 0;
		///<! printf使っていいので、ft_printfわざわざ入れなくて良さそう
		printf("%d :%s:%d\n", i, tmp->str, tmp->kind);
		tmp = tmp->next;
		i++;
	}
	return (lexer);
}

t_token	*create_token(char *line, t_token_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->str = line;
	token->kind = kind;
	token->next = NULL;
	//free(line);
	return (token);
}


//<! 動くけど、レビュワーによっては「文字列のポインタをすすめる機能と空白判定を一緒にするな」とか、
//<! 「もうちょっと関数名考えろ」と指摘してくるかも。余力があれば治した方がいいかも？


bool	split_space(char **tmp, char *line)
{
	if (!(*line && (*line == ' ' || *line == '\t' || *line == '\n')))
		return (false);
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	*tmp = line;
	return (true);
}

t_token	*split_pipe(char **tmp, char *line)
{
	char	*set;
	t_token	*token;

	set = ft_strdup("|");
	//<! １文字進めるのであれば、*tmp += 1;とした方がわかりやすそう
	*tmp = &line[1];
	token = create_token(set, TK_PIPE);
	return (token);
}

t_token	*split_red(char **tmp, char *line)
{
	char	*set;

	if (*line == '<')
	{
		if (line[1] == '<')
		{
			set = ft_strdup("<<");
			*tmp = &line[2];
			//<! このぐらいであればcreate_token("<<", TK_DLESS)と直打ちしても問題ない気がします。
			//<! setの存在意義そんなにないと叩かれそう
			return (create_token(set, TK_DLESS));
		}
		else
		{
			set = ft_strdup("<");
			*tmp = &line[1];
			return (create_token(set, TK_LESS));
		}
	}
	else if (*line == '>')
	{
		if (line[1] == '>')
		{
			set = ft_strdup(">>");
			*tmp += 2;
			return (create_token(">>", TK_DGREAT));
		}
		else
		{
			set = ft_strdup(">");
			*tmp = &line[1];
			return (create_token(set, TK_GREAT));
		}
	}
	exit(0);
}

bool	is_redirect(char c)
{
	if (c == TK_GREAT || c == TK_LESS || c == TK_DGREAT || c == TK_DLESS)
	{
		printf("is_redirect\n");
		return (true);
	}
	return (false);
}

t_token	*split_squote(char **tmp, char *line)
{
	int		i;
	int		a;
	char	*set;

	i = 1;
	a = 0;
	i++;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			break ;
		}
		i++;
	}
	set = (char *)malloc(sizeof(char) * (i + 1));
	//<! ヒープオーバーフローが発生するので変更
	//<! a <= i -> a < i
	while (a < i)
	{
		set[a] = *line;
		a++;
		line++;
	}
	set[a] = '\0';
	*tmp = line;
	return (create_token(set, TK_SQUOTE));
}

t_token	*split_dquote(char **tmp, char *line)
{
	int		i;
	//<! aは流石に変えた方がいいかも...
	int		a;
	char	*set;

	i = 1;
	a = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			break ;
		}
		i++;
	}
	//<! こいつのNULL処理どうしよう...
	set = (char *)malloc(sizeof(char) * (i + 1));
	//<! ヒープオーバーフローが発生するので変更
	//<! a <= i -> a < i
	while (a < i)
	{
		set[a] = *line;
		a++;
		line++;
	}
	set[a] = '\0';
	printf("set!!!%s\n",set);
	*tmp = line;
	return (  create_token(set, TK_DQUOTE));
}

t_token	*split_word(char **tmp, char *line)
{
	char	*set;
	int		i;

	if (*line == '\'')
	{
		return (split_squote(tmp, line));
	}
	else if (*line == '\"')
	{
		return (split_dquote(tmp, line));
	}
	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	set = (char *)ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (line[i] != ' ' && line[i])
	{
		set[i] = line[i];
		i++;
	}
	*tmp = &line[i];
	return (create_token(set, TK_CMD));
}

bool	is_quoted(char *cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\'' || cmd[j] == '\"')
			return (true);
		j++;
	}
	return (false);
}

bool	check_word(char	*line)
{
	return (*line && !ft_strchr("|&;()\t\n",*line));
}

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(0);
}

void	remove_squote(t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;

	if (token->str[0] != '\'' || token == NULL)
		return ;
	tmp = token->str;
	i = ft_strlen(token->str);
	new = ft_calloc(i-2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i]  != '\'' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}

	if (*tmp == '\0')
	{
		ft_error();
		free(token->str);
	}
	token->str = new;
	return ;
}

void	remove_dquote(t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;

	if (token->str[0] != '\"' || token == NULL)
		return ;
	tmp = token->str;
	i = ft_strlen(token->str);
	new = ft_calloc(i-2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i]  != '\"' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}

	if (*tmp == '\0')
		ft_error();	free(token->str);
	token->str = new;
	return ;
}

void	expand(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->str[0] == '\'')
			remove_squote(token);
		else if (token->str[0] == '\"')
			remove_dquote(token);
		token = token->next;
	}
}
