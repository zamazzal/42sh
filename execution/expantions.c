#include "../includes/exec.h"

char		*ms_expand_arg(char *arg);


char	*ft_strojoin(char **s1, char *s2, int overwrite)
{
	char	*tmp;

	if (overwrite)
	{
		tmp = ft_strjoin(*s1, s2);
		ft_strdel(s1);
		(*s1) = tmp;
		return (NULL);
	}
	return (ft_strjoin(*s1, s2));
}

int		ft_tablen(char **array)
{
	int len;

	len = 0;
	if (!array)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}

int		ft_skipspaces(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

void	ft_putintab(char ***a_chain, char *entry)
{
	char	**new;
	size_t	size;
	size_t	i;

	size = ft_tablen(*a_chain);
	if (!(new = (char **)malloc(sizeof(char *) * (size + 2))))
		return ;
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup((*a_chain)[i]);
		i++;
	}
	new[i] = ft_strdup(entry);
	i++;
	new[i] = NULL;
	ft_freetable(a_chain);
	*a_chain = new;
}

char	*ft_strappend(char **a_s1, char c, int overwrite)
{
	char	*new;
	int		i;

	SAFE(new = (char *)malloc(sizeof(char) * (ft_strlen(*a_s1) + 2)));
	i = 0;
	while (*a_s1 && (*a_s1)[i])
	{
		new[i] = (*a_s1)[i];
		i++;
	}
	new[i] = c;
	new[++i] = '\0';
	if (overwrite == 1)
	{
		ft_strdel(a_s1);
		*a_s1 = new;
		return (NULL);
	}
	return (new);
}

void	ms_set_quote(int *quoted, char *quote, char c)
{
	if (c == '\'' && (*quoted) == FALSE)
	{
		(*quoted) = TRUE;
		(*quote) = c;
	}
	else if (c == '\'' && (*quoted) == TRUE && (*quote) == '\'')
	{
		(*quoted) = FALSE;
		(*quote) = 0;
	}
	else if (c == '\"' && (*quoted) == FALSE)
	{
		(*quoted) = TRUE;
		(*quote) = c;
	}
	else if (c == '\"' && (*quoted) == TRUE && (*quote) == '\"')
	{
		(*quoted) = FALSE;
		(*quote) = 0;
	}
}

static char	*ms_quote_content(char *str)
{
	int		i;
	char	quote;
	char	*content;

	i = 0;
	quote = str[0];
	content = ft_strnew(0);
	while (str[i])
	{
		if (str[i] == quote && i != 0)
			break ;
		ft_strappend(&content, str[i], TRUE);
		i++;
	}
	return (content);
}

static char	**ms_expand_args(char **args)
{
	char	**buffer;
	char	*tmp;
	int		i;

	tmp = NULL;
	buffer = NULL;
	i = 0;
	while (args[i])
	{
		tmp = ms_expand_arg(args[i]);
		ft_putintab(&buffer, tmp);
		ft_strdel(&tmp);
		i++;
	}
	return (buffer);
}

char		*ms_get_arg(char *line)
{
	int		i;
	char	*arg;
	char	*quote_content;

	i = 0;
	arg = ft_strnew(0);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			break ;
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote_content = ms_quote_content(line + i);
			ft_strojoin(&arg, quote_content, TRUE);
			i = i + ft_strlen(quote_content);
			ft_strdel(&quote_content);
			ft_strappend(&arg, line[i], TRUE);
		}
		else
			ft_strappend(&arg, line[i], TRUE);
		i++;
	}
	return (arg);
}

char		**ms_parse(char *line)
{
	int		i;
	char	**buffer;
	char	**args;
	char	*arg;

	i = ft_skipspaces(line);
	if (!(buffer = NULL) && line[i] && (i--) != -1)
	{
		while (line[++i])
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				arg = ms_get_arg(line + i);
				ft_putintab(&buffer, arg);
				i = i + ft_strlen(arg) - 1;
				ft_strdel(&arg);
			}
		}
		args = ms_expand_args(buffer);
		ft_freetable(&buffer);
		return (args);
	}
	return (NULL);
}

char		*ms_expand_quotes(char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	quote = 0;
	i = 0;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (quoted == FALSE && ft_strchr("\'\"", arg[i]))
			i++;
		else if (arg[i] != quote)
			ft_strappend(&result, arg[i++], TRUE);
		else
			i++;
	}
	return (result);
}

static int	ms_expand_dollar(char **buffer, char *arg)
{
	int		i;
	char	*var_name;
	char	*val;

	var_name = ft_strnew(0);
	i = 0;
	while (arg[i] && ft_strchr(ALNUM, arg[i]))
	{
		ft_strappend(&var_name, arg[i], TRUE);
		i++;
	}
	if ((val = getenv(var_name)))
		ft_strojoin(buffer, val, TRUE);
	ft_strdel(&var_name);
	return (i);
}

static char	*ms_expand_dollars(char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	i = 0;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (arg[i] == '$')
		{
			if ((quoted == TRUE && quote == '\"') || (quoted == FALSE))
			{
				i++;
				i += ms_expand_dollar(&result, arg + i);
				continue ;
			}
		}
		ft_strappend(&result, arg[i], TRUE);
		i++;
	}
	return (result);
}

static char	*ms_expand_tilde(char *arg)
{
	char	*result;
	char	*value;

	result = ft_strnew(0);
	if (arg[0] == '~')
	{
		if ((value = getenv("HOME")))
			ft_strojoin(&result, value, TRUE);
		ft_strojoin(&result, arg + 1, TRUE);
		return (result);
	}
	ft_strdel(&result);
	result = ft_strdup(arg);
	return (result);
}

char		*ms_expand_arg(char *arg)
{
	char	*result;
	char	*tmp;

	result = ms_expand_tilde(arg);
	tmp = ft_strdup(result);
	ft_strdel(&result);
	result = ms_expand_dollars(tmp);
	ft_strdel(&tmp);
	tmp = ft_strdup(result);
	ft_strdel(&result);
	result = ms_expand_quotes(tmp);
	ft_strdel(&tmp);
	return (result);
}