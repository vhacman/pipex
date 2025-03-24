# 🚀 Pipex

[![42 Project](https://img.shields.io/badge/42%20Project-Pipex-blue?style=for-the-badge&logo=42)](https://github.com/vhacman/pipex)  
[![C Language](https://img.shields.io/badge/Made%20with-C-00599C?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))  
[![Norminette Approved](https://img.shields.io/badge/Norminette-OK-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)  
[![Memory Leak Free](https://img.shields.io/badge/Leaks-Free-success?style=for-the-badge)](https://valgrind.org/)  

---

## 📚 Summary

This project explores the inner workings of UNIX pipelines by mimicking the shell behavior:

```bash
< infile cmd1 | cmd2 > outfile
```

The task is to replicate this logic using C system calls.

---

## 🧠 Objectives

- Master process creation using `fork()`
- Handle inter-process communication with `pipe()`
- Redirect I/O using `dup2()`
- Execute binaries with `execve()`
- Manage file descriptors and error handling like a shell would

---

## 🏗️ Mandatory Part

### 🧾 Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### ✅ Example

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

Behaves exactly like:

```bash
< input.txt grep hello | wc -l > output.txt
```

### ⚙️ Allowed Functions

```c
open, close, read, write, malloc, free, perror, strerror,
access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
```

Libft is authorized ✅  
No memory leaks tolerated 🚫  
Must follow [Norminette](https://github.com/42School/norminette) ✅  

---

## 🔧 Compilation

A Makefile is provided with the following rules:

```bash
make        # compiles the program
make clean  # removes object files
make fclean # removes executable and object files
make re     # fclean + make
```

---

## 📁 Project Structure

PIPEX
├── .github/          # Optional
├── includes/         # Header file(s)
│   └── pipex.h
├── libft/            # Your personal library
│   ├── ...
│   └── libft.a
├── main/             # Entry point
│   └── main.c
├── src/              # Core source code
│   ├── pipex.c
├── utils/ 
|   ├── errors.c  # Additional utility functions
│   ├── exec_utils.c
│   ├── path_utils.c 
|   
├── README_EN.md      # Documentation
└── Makefile          # Build script

---

## 🙌 Acknowledgments

Thanks to the 42 community and reviewers 🫡  

---