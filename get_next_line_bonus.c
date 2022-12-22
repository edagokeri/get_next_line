/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:01:34 by egokeri           #+#    #+#             */
/*   Updated: 2022/12/20 17:14:43 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	line = (char *)malloc(sizeof(char) * i + 1 + new_line);
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
	new_line = (char *)malloc(sizeof(char) * (j - i) + 1);
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

	now_str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!now_str)
		return (0);
	count = 1;
	while (! ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, now_str, BUFFER_SIZE);
		if (count == -1)
		{
			free (now_str);
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
	static char	*str[256];
	char		*line;

	if (fd == -1 && BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_get_read(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_get_line(str[fd]);
	str[fd] = ft_get_new_str(str[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd1 = open("a.txt", O_RDONLY);
	int	fd2 = open("b.txt", O_RDONLY);
	char *a = get_next_line(fd1);
	char *b = get_next_line(fd2);
	free(a);
	while (a)
	{
		printf("%s", a);
		a = get_next_line(fd1);
		free(a);
	}
	printf("%c", '\n');
	free(b);
	while (b)
	{
		printf("%s", b);
		b = get_next_line(fd2);
		free(b);
	}
	system("leaks a.out");
}*/

/*
int main()
{
	int fd;

	fd = open("t1.txt", O_RDONLY);
	fd = open("t2.txt", O_RDONLY);
	fd = open("t3.txt", O_RDONLY);

	printf("%d", fd);
	return 0;
}
*/

/*
int main()
{
	int fd1 = open("t1.txt", O_CREAT|O_RDWR, 0777);
	int fd2 = open("t2.txt", O_CREAT|O_RDWR, 0777);
	int fd3 = open("t3.txt", O_CREAT|O_RDWR, 0777);

	write(fd1, "11111\naaaaaaaaa\n444444", 30);
	write(fd2, "22222\nbbbbbbb\n5555555", 30);
	write(fd3, "333333\ncccccccc\n66666", 30);

	close(fd1);
	close(fd2);	
	close(fd3);

	fd1 = open("t1.txt", O_CREAT|O_RDWR, 0777);
	fd2 = open("t2.txt", O_CREAT|O_RDWR, 0777);
	fd3 = open("t3.txt", O_CREAT|O_RDWR, 0777);

	printf("a : %d\n", fd1);
	printf("b : %d\n", fd2);
	printf("c : %d\n", fd3);

	
	printf("d : %s\n", get_next_line(fd1));
	printf("e : %s\n", get_next_line(fd2));
	printf("f : %s\n", get_next_line(fd3));

	printf("g : %s\n", get_next_line(fd1));
	printf("h : %s\n", get_next_line(fd2));
	printf("j : %s\n", get_next_line(fd3));
	
	close(fd1);
	close(fd2);
	close(fd2);

	return 0;
}
*/
