#include "../include/minishell.h"

char    *ms_current_folder(void)
{
    char	*path;
	char	*res;
    int		i;
	int		len;

    if(!(path = malloc(PATH_MAX * sizeof(char))))
    {
        ft_printf("[ERROR] MALLOC");
        exit(EXIT_FAILURE);
    }
    getcwd(path, PATH_MAX);
	len = ft_strlen(path);
	i = len;
	while (i > 0 && path[i] != '/')
		i--;
    if (i == 0)
        res = ft_strdup("/");
    else
	    res = ft_substr(path, i + 1, len - i);
	free(path);	
	return (res);
}

void    prompt(void)
{
    char *folder;

    folder = ms_current_folder();
    ft_printf("\033[1;34m%s\033[0m $> ", folder);
    free(folder);
}

void    signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        ft_printf("\n");
        prompt();
    }
}

int main(int argc, char **argv, char **env)
{
    // set les signaux (ctrl-c ctrl-d ctrl-/)
     int res;
    char *line;
    (void) argc;
    (void) argv;
    errno = 0;
    if(signal(SIGINT, signal_handler) == SIG_ERR) // ctrl-c ne me fait pas quitter minishell
    {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR) // ctrl-\ ne me fait pas quitter minishell
    {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        prompt();
        res = get_next_line(0, &line);
        if (res == 0 && !strcmp(line, "")) // ctrl-D
            exit(EXIT_SUCCESS);
        else if (!strcmp(line, "exit"))
            exit(EXIT_SUCCESS);
        else if (!strcmp(line, "env"))
        {
            int i = 0;
            while(env[i])
            {
                ft_printf("%s\n", env[i]);
                i++;
            }
        }
        ft_printf("commande: %s$", line);
        ft_printf("\n");
        // affiche un prompt
        // parse la commande 
        // si built-in lancer mon ficher
        // sinon fork+execve avec recherche de la commande dans les fichiers $PATH
    }
}