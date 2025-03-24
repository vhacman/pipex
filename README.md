# Pipex
[![Pipex](https://github.com/vhacman/pipex/actions/workflows/main.yml/badge.svg)](https://github.com/vhacman/pipex/actions/workflows/main.yml)
![42 Badge](https://img.shields.io/badge/42-Rome-2BA5DE)
![Project Score](https://img.shields.io/badge/Score-100%2F100-brightgreen)
![Created](https://img.shields.io/badge/Created-March_2025-blue)
![Status](https://img.shields.io/badge/Status-SUCCESS-violet)

## 📝 Description

This project is about handling **UNIX pipes** in C.  
It reproduces the behavior of the shell for a simple command like:

```bash
< file1 cmd1 | cmd2 > file2
```

You'll learn to use low-level system calls such as `pipe()`, `fork()`, `dup2()`, and `execve()` to redirect input/output between processes.

---

## 🛠️ Mandatory Features

- Reproduce the shell piping behavior with two commands.
- Correctly manage input/output redirection using file descriptors.
- Handle all errors (permissions, file access, commands not found, etc.).
- Prevent memory leaks and properly free all resources.
- Handle all possible edge cases just like a real shell.

---

## 🧪 Usage

### ✅ Compilation

```bash
make
```

Generates the `pipex` executable.

### ▶️ Run

```bash
./pipex file1 cmd1 cmd2 file2
```

This mimics the shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

### 🔁 Example

```bash
./pipex infile "grep hello" "wc -w" outfile
```

Equivalent to:

```bash
< infile grep hello | wc -w > outfile
```

---

## 📂 Project Files

| File           | Description                                       |
|----------------|---------------------------------------------------|
| `pipex.c`      | Main function, argument parsing                   |
| `exec_utils.c` | Command execution with `execve`, error handling   |
| `path_utils.c` | PATH resolution, splitting and command parsing    |
| `pipex.h`      | Header file with includes and prototypes          |
| `Makefile`     | Standard compilation rules                        |

---

## ⚙️ Compilation Rules

| Rule        | Description                                  |
|-------------|----------------------------------------------|
| `make`      | Compiles the project                         |
| `make clean`| Removes object files                         |
| `make fclean`| Removes object files and the binary         |
| `make re`   | Recompiles the project from scratch          |

---

## ⚙️ Allowed Functions

You may use **only** the following C functions:

```c
open, close, read, write,
malloc, free, perror, strerror, access,
dup, dup2, execve, exit, fork, pipe,
unlink, wait, waitpid
```

-**libft** is allowed and included locally.

---

## 🚫 Not Allowed

- `system()`, `popen()`, or any shell wrapper
- `for`, `do-while`, `switch`, `goto`, ternary operators (`?:`)
- Variable Length Arrays (VLAs)

---

## ✅ Requirements Met

- Full **Norm compliance**
- No memory leaks (`valgrind` tested)
- Correct **error messages** matching shell output (`bash:` prefix)
- All file descriptors closed properly
- Zombie processes prevented (via `waitpid`)
- Exit codes match shell behavior (126/127)

---

## 📌 Project Structure

```
pipex/
├── Makefile
├── pipex.h
├── pipex.c
├── exec_utils.c
├── path_utils.c
├── libft/ (copied if used)
│   ├── Makefile
│   └── *.c, *.h
```

---

## 👤 Author

**vhacman**  
- 42 Profile: [vhacman](https://profile.intra.42.fr/users/vhacman)

---

## 📝 License

This project is subject to the rules and academic integrity policies of 42 School.  
Any code reuse or distribution must comply with 42’s regulations.

```
