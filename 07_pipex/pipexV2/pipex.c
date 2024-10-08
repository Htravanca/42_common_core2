/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepereir <hepereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:43:40 by hepereir          #+#    #+#             */
/*   Updated: 2024/10/06 13:19:36 by hepereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *argv, char **envp)
{
	char	**cmdsarr;
	char	*path;

	cmdsarr = ft_split_adapt(argv, ' ');
	ft_split_result(cmdsarr);
	path = ft_path(cmdsarr, envp);
	if (!path)
	{
		perror("Command not found");
		ft_free_arr(cmdsarr);
		exit(127);
	}
	execve(path, cmdsarr, envp);
	perror("Error executing the cmd");
	ft_free_arr(cmdsarr);
	free(path);
	exit(1);
}

int	ft_execute_child(char *argv, char **envp, int *fd, int prev_fd)
{
	int	pid;

	pid = ft_handle_error(fork(), "Fork error");
	if (pid == 0)
	{
		if (prev_fd != -1) // If it's not the first command, redirect input
		{
			dup2(prev_fd, STDIN_FILENO); // Redirect input from previous pipe
			close(prev_fd);
		}
		close(fd[0]); // Close the read end of the current pipe
		dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the write end of the current pipe
		close(fd[1]); // Close write end after duping
		ft_execute(argv, envp); // Execute command
	}
	// Close the unnecessary FDs in the parent process immediately after fork
	close(fd[1]); // Parent doesn't need to write to the current pipe
	if (prev_fd != -1) // If there is a previous pipe, close its read end
		close(prev_fd);
	return (pid);
}

/* static void	ft_wait(int i)
{
	int	status;
	int	statusf;

	statusf = 0;
	while ((i - 2) >= 0)
	{
		waitpid(-1, &status, 0);
		//fprintf(stderr, "path2:%d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) != 0)
			statusf = WEXITSTATUS(status);
		i--;
	}
	exit(statusf);
} */ 

static void ft_wait(int i)
{
    int status;
    int statusf = 0;

    while ((i - 2) >= 0)
    {
        waitpid(-1, &status, 0);
        // Check if the process exited normally
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            // Only record an error if the exit status is not 0 or 1 (allowing grep to indicate no match)
            if (exit_status != 0 && exit_status != 1)
            {
                statusf = exit_status; // Capture the actual error status
            }
        }
        i--;
    }

    exit(statusf); // Exit with the recorded status
}


static void	ft_loop_process(int argc, char **argv, char **envp)
{
	int	pid[10000];
	int i;
	int prev_fd = -1; // Initially, no previous pipe
	int fd[2];

	i = 2;
	while (i < (argc - 2)) // Loop through all commands except the last one
	{
		ft_handle_error(pipe(fd), "Pipe Error"); // Create a new pipe for each command
		pid[i - 2] = ft_execute_child(argv[i], envp, fd, prev_fd);
		//close(fd[1]); // Close the write end of the current pipe in the parent process
		//if (prev_fd != -1) // Close the previous read end if it's not the first command
		//	close(prev_fd);
		prev_fd = fd[0]; // Save the read end of the current pipe to use in the next iteration
		i++;
	}

	// Last command: Redirect output to file instead of another pipe
	int wfd = ft_handle_error(open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644), "Error opening file2");
	pid[i - 2] = ft_handle_error(fork(), "Fork error");
	if (pid[i - 2] == 0) // Child process for the last command
	{
		dup2(prev_fd, STDIN_FILENO); // Redirect input from the last pipe
		close(prev_fd); // Close the read end after duping
		dup2(wfd, STDOUT_FILENO); // Redirect output to the file
		close(wfd); // Close the file descriptor after duping
		ft_execute(argv[argc - 2], envp); // Execute last command
	}
	close(prev_fd); // Close the last read end in the parent
	close(wfd); // Close the file descriptor in the parent
	ft_wait(i); // Wait for all child processes to finish
}

int	main(int argc, char **argv, char **envp)
{
	int	rfd;
	int	wfd;

	if (argc >= 5)
	{
		rfd = ft_handle_error(open(argv[1], O_RDONLY, 0777),
				"Error opening infile");
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		wfd = ft_handle_error(open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
					0644), "Error opening outfile");
		close(wfd);
		ft_loop_process(argc, argv, envp);
	}
	else
		perror("Error ARGS,correct usage: ./pipex file1 cmd1 cmdn... file2");
	return (0);
}
