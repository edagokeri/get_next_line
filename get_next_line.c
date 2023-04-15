#include "get_next_line.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;
	int		new_line;

	i = 0;
	new_line = ft_strchr(str, '\n');
	if (!str[i])
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 1 + new_line);
	if (!line)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (0);
	}
	new_line = malloc(sizeof(char) * (j - i) + 1);
	if (!new_line)
		return (0);
	j = 0;
	i++;
	while (str[i] != '\0')
		new_line[j++] = str[i++];
	new_line[j] = '\0';
	free(str);
	return (new_line);
}

char	*ft_get_read(int fd, char *str)
{
	int		count;
	char	*now_str;

	now_str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!now_str)
		return (0);
	count = 1;
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, now_str, BUFFER_SIZE);
		if (count == -1)
		{
			free(now_str);
			return (0);
		}
		now_str[count] = '\0';
		str = ft_strjoin(str, now_str);
	}
	free(now_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
	{
		return (0);
	}
	str = ft_get_read(fd, str);
	if (!str)
		return (0);
	line = ft_get_line(str);
	str = ft_get_new_str(str);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
//This main function will print the first line of file.

int	main(void)
{
	int	fd = open("a.txt", O_RDONLY);
	char	*a = get_next_line(fd);
	printf("%s", a);
	system("leaks a.out"); //This line will show you the leaks.

} 
*/

/*
//This main function will print out the all lines in file.

int	main(void)
{
	int	fd = open("a.txt", O_RDONLY);
	char	*a = get_next_line(fd);
	free(a);
	while (a)
	{
		printf("%s", a);
		a = get_next_line(fd);
		free(a);
	}
	//system("leaks a.out");
}*/

/*
//This main function will print out the first five line from file.

int	main(void)
{
	int	fd;
	fd = open ("a.txt", O_RDONLY);
	char	*a = get_next_line(fd);
	char	*b = get_next_line(fd);
	char	*c = get_next_line(fd);
	char	*d = get_next_line(fd);
	char	*e = get_next_line(fd);
	printf("%s", a);
	printf("%s", b);
	printf("%s", c);
	printf("%s", d);
	printf("%s", e);
	system("leaks a.out");
}*/

/*
//This main function will print out only third line of file.
int	main()
{
	int	fd = open("a.txt", O_RDONLY);
	char	*a = get_next_line(fd);
	free(a);
	int	count = 1;
	while (a)
	{
		if (count == 3)
			printf("%s", a);
	count++;
	a = get_next_line(fd);
	free(a);
	}
	system("leaks a.out");
}
*/
