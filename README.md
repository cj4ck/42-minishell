# 42 Minishell
This project aims to recreate a simple shell (command-line interpreter) similar to the Unix shell. The shell should be able to handle basic shell commands, environmental variables, and support some shell features like pipes and redirection.

## Features
The minishell project is designed to provide a basic command-line interface for interacting with the operating system. It allows users to execute various shell commands, run programs, and manipulate the environment. The project emphasizes understanding of processes, file descriptors, signals, and basic parsing techniques.

## Installation
Clone the repository to your local machine:
```bash
git clone https://github.com/cj4ck/42-minishell.git
```
### Navigate to the project directory:
```bash
cd 42-minishell
```
### Build the minishell executable:
```go
make
```
## Usage
To start the minishell, simply run the minishell executable:
```bash
./minishell
```
> You will then be in the minishell environment, and you can enter various commands as you would in a regular shell.

## Supported Commands
#### The minishell supports a wide range of shell commands, including:
* Basic shell commands (e.g., ls, cd, echo, pwd, etc.)
* Execution of external programs
* Pipes and redirections (e.g., |, >, >>, <, etc.)
* Environment variable handling (e.g., export, unset, etc.)
* Builtin Commands
* The minishell also supports some builtin commands that are handled internally:
	- `echo` - Display a message to the terminal.
	- `cd` - Change the current working directory.
	- `pwd` - Print the current working directory.
	- `export` - Set or modify environment variables.
	- `unset` - Remove environment variables.
	- `env` - Show the list of environment variables.
	- `exit` - Exit the minishell.

## Additional Features
The minishell may also include additional features beyond the basic requirements, such as:
* Command history and navigation
* Tab completion
* Signal handling for interrupts and termination
