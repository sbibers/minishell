## Example of Minishell in Action 🖥️

42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

![Minishell Screenshot](screenshot.png)

---

## How to use it

Using `make` will create the `minishell` executable.

Simply run it with:

./minishell

---

## Available options

- **Executables**: `Minishell` runs executables from an absolute, relative, or environment path (`/bin/ls` or `ls`), including arguments or options. 
- **Environment Variables**: Environment variables such as `$HOME` are handled, and the return code `$?` is supported. 
- **Redirections**: You can use redirections such as `>`, `>>`, `<`, and pipes `|`.
- **Quotation Marks**: Both single quotes (`'`) and double quotes (`"`) work the same as in Bash, except for multiline commands.
- **Control Keys**: 
  - `Ctrl-C` interrupts the current command.
  - `Ctrl-\` quits a program.
  - `Ctrl-D` sends an EOF, just like in Bash.

---

## Built-in Functions

Some functions are "built-in", meaning they are re-coded directly in `minishell` instead of calling the executable. These built-in commands include:

- `echo`
- `pwd`
- `cd`
- `env`
- `export`
- `unset`
- `exit`

---

## Project Overview

The goal of this project is to recreate a minimalist shell environment that can interpret commands, handle input and output redirections, process environment variables, and support built-in commands. As part of the 42 School curriculum, this project emphasizes understanding the core functionality of a shell, including process management, file handling, and user input parsing.

---

## Features

- **Command Parsing**: `Minishell` can parse and execute commands, with the ability to handle arguments, options, and environment variables.
- **Redirection and Pipes**: Support for input/output redirections (`>`, `>>`, `<`) and piping (`|`), allowing complex command chaining.
- **Signal Handling**: Implements handling of signals such as `Ctrl-C`, `Ctrl-\`, and `Ctrl-D` to control the shell's behavior.
- **Exit Status**: The return status of the last executed command is stored and can be accessed via `$?`.

---

## Built with

- **C programming language**: The core of `minishell` is written in C, using basic system calls to handle user input and execute commands.
- **Makefile**: For compiling and managing the build process.

---

## How to Contribute

Feel free to fork the repository and submit pull requests if you'd like to contribute improvements or report bugs. This is an ongoing project, and contributions are welcome.

