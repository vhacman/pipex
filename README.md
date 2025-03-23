# Pipex

`pipex` è un progetto della Scuola 42 che replica parte del funzionamento della shell UNIX, in particolare il comportamento delle pipe (`|`) tra comandi. L'obiettivo è comprendere e gestire processi, redirezioni e file descriptor in ambiente UNIX.

## 📚 Descrizione

Il programma simula il comportamento di un'espressione shell come:

```bash
< file1 cmd1 | cmd2 > file2
```

`pipex` prende in input:
- un file di input (`file1`)
- due comandi (`cmd1` e `cmd2`)
- un file di output (`file2`)

Esegue `cmd1` prendendo l'input da `file1`, poi passa l'output di `cmd1` come input a `cmd2`, infine scrive l'output finale in `file2`.

## 🧪 Esempio di utilizzo

```bash
./pipex infile "grep a" "wc -l" outfile
```

Equivale a:

```bash
< infile grep a | wc -l > outfile
```

## 🔧 Compilazione

Per compilare il progetto:

```bash
make
```

Per pulire i file oggetto:

```bash
make clean
```

Per rimuovere anche l’eseguibile:

```bash
make fclean
```

Per ricompilare tutto da zero:

```bash
make re
```

## ✅ Requisiti

- Solo funzioni C standard POSIX (`open`, `close`, `read`, `write`, `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `access`, ecc.)
- Non è permesso usare `system()` o funzioni di parsing avanzato

## 📁 Struttura del progetto

```
pipex/
├── libft/             # Libreria Libft (libft)
│   └── ...
├── src/               # File sorgente principali
│   ├── pipex.c
│   ├── path_utils.c
│   └── ...
├── includes/          # Header file (file .h)
│   ├── pipex.h
│   
├── Makefile
└── README.md
```

## 🧠 Cosa ho imparato con questo progetto

- Come funzionano le pipe tra processi
- Gestione della memoria e dei file descriptor
- Uso delle syscall UNIX
- Parsing dei comandi e delle variabili d’ambiente

## 👩‍💻 Autore

Hacman Viorica Gabriela – studentessa di 42 Roma

---

> “This project is not just about piping commands — it's about understanding the flow of data, one byte at a time.”
