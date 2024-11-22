#include "../minishell.h"

// UNSET AO ENVC
// Expected input args[0]=unset; args[n]="PATH"; args[n]="etc"; args[last]=NULL;
// Return 0 OK; -1 ERROR
void	ft_unset_env(envc **env, char *arg)
{
	envc	*temp;
	envc	*prev;

	temp = *env;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->var, arg) == 0)
		{
			if (prev == NULL)
				*env = temp->next;
			else
				prev->next = temp->next;
			free((temp)->var);
			if (temp->value)
				free(temp->value);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(char **args, envc **env)
{
	int	i;

	i = 1;
	if (!args || !args[1])
		return (-1);
	while (args[i])
	{
		ft_unset_env(env, args[i]);
		i++;
	}
	return (0);
}
