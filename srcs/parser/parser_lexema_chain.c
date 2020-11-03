# include "../minishell.h"
#include "../t_lexema/t_lexema.h"
t_list_lexema *get_next_lexema_chain(t_list_lexema **lexema_list, t_lexema_type delimeter)
{
    t_lexema *lexema;
    int is_not_delimeter_prev;
    t_list_lexema *chain;
    t_list_lexema *prev_node;
    t_list_lexema *lexema_list_tmp;

    prev_node = NULL;
    chain = *lexema_list;
    is_not_delimeter_prev = 1;
    while (*lexema_list && is_not_delimeter_prev)
    {
        lexema = (*lexema_list)->lexema;
        if(lexema->lexemaType != delimeter)
        {
            prev_node = *lexema_list;
            *lexema_list = (*lexema_list)->next;
        }
        else
        {
            lexema_list_tmp = (*lexema_list)->next;
            prev_node->next = NULL;
            *lexema_list = lexema_list_tmp;
            is_not_delimeter_prev = 0;
        }
    }
    return chain;
}



static void str_join_str(char **str1, char *str2)
{
    char *str_tmp;

    str_tmp = ft_strjoin(*str1, str2);
    free(*str1);
    *str1 = str_tmp;
}

static void str_join_char(char **str1, char ch)
{
    char *str_tmp;

    str_tmp = (char *)(malloc(sizeof(char )*2));
    str_tmp[0] = ch;
    str_tmp[1] = '\0';

    str_join_str(str1, str_tmp);
    free(str_tmp);
}

static void unescape$(char **str_eval, char **str_original)
{
    str_join_str(str_eval, "$");
    (*str_original)+=2;
}


static int is_var_name_symbol(char symbol)
{
    if(((symbol >='a') && (symbol <= 'z')) ||
            ((symbol >='A') && (symbol <= 'Z')) ||
               symbol == '_')
        return 1;
    else
        return 0;
}

static int is_var_name_symbol_with_num(char symbol)
{
    if((symbol >='0' && symbol <= '9') ||
            is_var_name_symbol(symbol)
    )
        return 1;
    else
        return 0;
}

static char *get_var_name(char *str)
{
    int i;
    char *varName;

    i = 1;
    while (str[i] && is_var_name_symbol_with_num(str[i]))
        i++;
    varName = ft_strndup((str+1), i-1);
    return varName;
}
static void eval_var(char **str_eval, char **str_original, t_list_env	*envs)
{
    char *varName;

    varName = get_var_name(*str_original);
    str_join_str(str_eval, get_env_value(varName, (t_list *)envs));
    (*str_original)+=(ft_strlen(varName)+1);
    free(varName);
}

static void eval_param(char **str_eval, char **str_original, int argc, char **argv)
{
    int paramIndex;

    paramIndex = (*((*str_original)+1)) - '0';
    if(paramIndex < argc)
    {
        str_join_str(str_eval, argv[paramIndex]);
    }
    (*str_original)+=2;
}

static void simple_join_symbol(char **str_eval, char **str_original)
{
    str_join_char(str_eval, **str_original);
    (*str_original)++;
}

static void eval_last_exit_value(char **str_eval, char **str_original) //$? substitution
{
	char *exit_value;

	exit_value = ft_itoa(g_exit_value);
	str_join_str(str_eval, exit_value);
	(*str_original)+=(ft_strlen(exit_value)+1);
	free(exit_value);
}

static void eval_vars_and_params(char **str_eval, char **str_original, int argc, char **argv, t_list_env	*envs)
{
	if (*((*str_original) + 1) == '?')
		eval_last_exit_value(str_eval, str_original); //$? substitution
    else if(is_var_name_symbol(*((*str_original)+1)))
    {
        eval_var(str_eval, str_original, envs);
    } else if(is_var_name_symbol_with_num(*((*str_original)+1)))
    {
        eval_param(str_eval, str_original, argc, argv);
    } else
        simple_join_symbol(str_eval, str_original);
}

static void eval_tilda(char **str_eval, char **str_original, t_list_env	*envs) //~ substitution
{
	char *home_dir;

	home_dir = get_env_value("HOME", (t_list *)envs);
	str_join_str(str_eval, home_dir);
	(*str_original)+=2;
//	free(home_dir);
}

static void eval_vars_and_unescape_$(t_lexema *lexema, int argc, char **argv, t_list_env	*envs)
{
    char *str_original;
    char *str_eval;

    str_eval = ft_strdup("");
    str_original = lexema->string;
	if (*str_original == '~' && *(str_original+1) == '\0')
	{
		eval_tilda(&str_eval, &str_original, envs);
	}
	else
		while (*str_original)
		{
			if(*str_original == '\\' && *(str_original+1) == '$')
				unescape$(&str_eval, &str_original);
			else if (*str_original == '$')
				eval_vars_and_params(&str_eval, &str_original, argc, argv, envs);
			else
				simple_join_symbol(&str_eval, &str_original);
		}
    free(lexema->string);
    lexema->string = str_eval;
}

void eval_vars_and_unescape_$_in_lexema_chain(t_list_lexema *lexema_chain, int argc, char **argv, t_list_env *envs)
{
    t_lexema *lexema;

    while (lexema_chain)
    {
        lexema = lexema_chain->lexema;
        if(lexema->lexemaType == lexema_type_simple_word || lexema->lexemaType == lexema_type_double_q)
        {
            eval_vars_and_unescape_$(lexema, argc, argv, envs);
        }
        lexema_chain = lexema_chain->next;
    }
}

void remove_empty_elements(t_list_lexema **lexema_chain)
{
	t_list_lexema *prev;
	t_list_lexema *current;
	t_list_lexema *tmp;
	t_list_lexema *tmp2;
	char *tmp_string;

	prev = NULL;
	current = *lexema_chain;
	while (current)
	{
		if(current->lexema->string[0] == '\0')
		{
			if(current->lexema->lexemaType==lexema_type_simple_word)
			{
				if(prev == NULL)
				{
					*lexema_chain = current->next;
				}
			}
			else {
				if (current->next) {
					if (current->next->lexema->has_space_before) {
						if((current->next->lexema->string[0] != '\0')) {
							tmp_string = current->next->lexema->string;
							current->next->lexema->string = ft_strjoin(" ", current->next->lexema->string);
							free(tmp_string);
						}
					}
					else
					{
						if(!(current->lexema->has_space_before) && prev)
						{
							tmp_string = prev->lexema->string;
							prev->lexema->string = ft_strjoin(prev->lexema->string, current->next->lexema->string);
							free(tmp_string);

							tmp = current->next;
							current->next = current->next->next;
							free(tmp->lexema->string);
							free(tmp->lexema);
							free(tmp);
						}
					}
				}
			}
			tmp = current;
			current = current->next;
			if (prev)
			{
				prev->next = current;
				current = prev;
			}
			free(tmp->lexema->string);
			free(tmp->lexema);
			free(tmp);
			continue;
		}
		prev = current;
		current = current->next;
	}
}