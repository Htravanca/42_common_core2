#include "so_long.h"
#include "get_next_line/get_next_line.h"

int ft_check_map_name(char *name)
{
    int fd;
    int pos;

    pos = 0;
    fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map, choose a valid .ber file!\n");
		return (1);
	}
    while (name[pos] != '.')
        pos++;
    if (!(name[pos] == '.' && name[pos + 1] == 'b' && name[pos + 2] == 'e' && name[pos + 3] == 'r' && name[pos + 4] == '\0'))
    {
        close(fd);
        return (1);
    }
    close(fd);
	return (0);
}

int ft_map_parsing(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Choose a map\n");
        return (1);
    }
    else if(argc == 2 && ft_check_map_name(argv[1]))
        return (1);
    else if (argc >= 3)
    {
        printf("Choose only a map\n");
        return (1);
    }
    return (0);
}

int ft_map_lines(char *str)
{
    int lines;
    char *getline;
    int fd;

    lines = 0;
    fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map, choose a valid .ber file!\n");
		return (1);
	}
    while (1)
	{
		getline = get_next_line(fd);
		if (getline == NULL)
			break ;
        lines++;
		free(getline);
		getline = NULL;
	}
    close (fd);
    return (lines);
}

int ft_check_map(char *str)
{
    int fd;
	char **map;
    char *temp;
    int lines;
    int i;

    lines = 0;
    i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map, choose a valid .ber file!\n");
		return (1);
	}
    lines = ft_map_lines(str);
    map = malloc((lines + 1) * sizeof(char *));
    if (map == NULL)
    {
        close(fd);
        return (1);
    }
    while (i < lines)
	{
        temp = get_next_line(fd);
	 	if (temp == NULL)
		{
			printf("[%d]:%s\n", i, temp);
			break ;
		}
        i++;
        map[i] = temp;
		printf("[%d]:%s", i, map[i]);
	}
    map[i] = NULL;
	close(fd);
	return (0);
}
