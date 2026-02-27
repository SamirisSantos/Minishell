*This project has been created as part of the 42 curriculum by cpinho-c, sade-ara.*
# Minishell
## Description
Minishell is a team project to create a simplified implementation of a Unix shell, inspired by bash.

The goal of this project is to understand how a Unix shell works internally. It includes parsing user input, creating child processes, executing commands, and managing file descriptors.

Minishell implements redirections and pipes, as well as environment variable expansions. It also includes the following built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`.

Through this project, we explored process management using `fork`, `execve`, and `waitpid`, `handled signals` such as `Ctrl+C` and `Ctrl+D`, and worked with environment variables and memory management in C, following the 42 Norm (Norminette).
### Struct

## Instructions
### Compilation
- To compile the project:
```
make
```
- Other available rules:
```
make clean		# remove object files
make fclean		# remove object files and executable
make re			# recompile the project
```
### Execution
- After compilation, run:
```
./minishell
```
The program will start an interactive shell prompt.
for example:
```
minishell$ ls -l					#Simple command

minishell$ ls | grep minishell		#Using pipes

minishell$ echo Hello > file.txt	#Using redirection
minishell$ cat file.txt
Hello

minishell$ echo $HOME				#Environment variable expansion
```
## Resources
### Documentation
- GNU Bash Reference Manual

### Practical Research and Testing

During the initial phase of the project, we discussed with colleagues who had already completed Minishell in order to better understand the scope of the project and how to break the system into smaller logical parts.

We also observed the behavior of a colleague’s Minishell implementation to compare outputs and understand expected behavior:  
- Repository reference: https://github.com/danielarjordao/minishell

To better understand the project structure and common implementation strategies, we also consulted the following guides:

- https://medium.com/@laamirimarouane8/42-minishell-guide-53600f49742b  
- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

### Project Management

We used ClipUp to organize tasks and manage the project.
It helped us divide the project into smaller steps, track progress, and ensure that all parts of Minishell were implemented in a structured way.

### Use of Artificial Intelligence

AI tools were used to understand theoretical concepts, perform quick debugging, analyze memory leaks, and check the behavior of command outputs.  
All implementation decisions and code were written, tested, and fully understood by the authors.