# 🚀 Pipex

[![42 Project](https://img.shields.io/badge/42%20Project-Pipex-blue?style=for-the-badge&logo=42)](https://github.com/vhacman/pipex)  
[![C Language](https://img.shields.io/badge/Made%20with-C-00599C?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))  
[![Norminette Approved](https://img.shields.io/badge/42%20Norminette-OK-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)  
[![Memory Leak Free](https://img.shields.io/badge/42%20Leaks-Free-success?style=for-the-badge)](https://valgrind.org/)  

---

## 📚 Sommario

Questo progetto esplora il funzionamento interno delle pipeline UNIX, imitando il comportamento della shell:

```bash
< infile cmd1 | cmd2 > outfile
```

L’obiettivo è replicare questa logica utilizzando le chiamate di sistema in C.

---

## 🧠 Obiettivi

- Gestire la creazione di processi con `fork()`
- Gestire la comunicazione tra processi con `pipe()`
- Reindirizzare I/O con `dup2()`
- Eseguire binari con `execve()`
- Gestire file descriptor ed errori come farebbe una shell

---

## 🏗️ Parte Obbligatoria

### 🧾 Utilizzo

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### ✅ Esempio

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

Si comporta esattamente come:

```bash
< infile.txt grep hello | wc -l > outfile.txt
```

### ⚙️ Funzioni Consentite

```c
open, close, read, write, malloc, free, perror, strerror,
access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
```

Libft è autorizzata ✅  
Nessuna perdita di memoria tollerata 🚫  
Deve seguire la [Norminette](https://github.com/42School/norminette) ✅  

---

## 🔧 Compilazione

È fornito un Makefile con le seguenti regole:

```bash
make        # compila il programma
make clean  # rimuove i file oggetto
make fclean # rimuove l'eseguibile e i file oggetto
make re     # fclean + make
```

---

## 📁 Struttura del Progetto

PIPEX  
├── .github/          # Opzionale  
├── includes/         # Header file  
│   └── pipex.h  
├── libft/            # Libreria personale  
│   ├── ...  
│   └── libft.a  
├── main/             # Punto di ingresso  
│   └── main.c  
├── src/              # Codice sorgente principale  
│   ├── pipex.c  
├── utils/  
│   ├── errors.c      # Funzioni di utilità supplementari  
│   ├── exec_utils.c  
│   ├── path_utils.c  
│  
├── README_EN.md      # Documentazione  
└── Makefile          # Script di build  
