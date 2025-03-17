Ti spiego in maniera colloquiale e dettagliata tutto quello che c'è da sapere su Pipex, il progetto che replica il comportamento della pipe della shell in C.

---

### Cos'è Pipex?

Pipex è un progetto in C che simula il funzionamento della pipe (`|`) che usi in shell per collegare l'output di un comando all’input di un altro. In pratica, invece di scrivere qualcosa tipo:

```bash
cat file.txt | grep "ciao"
```

il programma Pipex esegue due comandi collegandoli tramite una pipe.

---

### Come si usa il programma

Il comando per eseguire Pipex è:

```bash
./pipex infile cmd1 cmd2 outfile
```

- **infile**: è il file da cui si legge.
- **cmd1**: è il primo comando da eseguire.
- **cmd2**: è il secondo comando.
- **outfile**: è il file in cui viene scritto l’output finale.

In sostanza, l’output di **cmd1** (che legge da *infile*) viene passato come input a **cmd2**, e il risultato di quest’ultimo viene scritto su *outfile*.

---

### Meccanismo base: pipe(), fork() e dup2()

#### 1. Creare la pipe

La funzione `pipe()` crea un canale di comunicazione tra processi. Essa accetta un array di due interi, ad esempio `int end[2];`, dove:

- `end[0]` è il lato di lettura.
- `end[1]` è il lato di scrittura.

Quindi, ciò che viene scritto in `end[1]` può essere letto da `end[0]`.

#### 2. Creare i processi con fork()

Per eseguire due comandi contemporaneamente, il programma utilizza `fork()`, che crea due processi:

- **Processo figlio (child)**: esegue il **cmd1**.
- **Processo padre (parent)**: esegue il **cmd2**.

Quando `fork()` viene chiamato:
- Se ritorna 0, siamo nel processo figlio.
- Se ritorna un numero positivo, siamo nel processo padre.
- Se ritorna -1, c'è stato un errore.

#### 3. Redirigere gli input e gli output con dup2()

Il trucco per collegare i due comandi è usare `dup2()`, che permette di "scambiare" i file descriptor (FD). In pratica:

- **Nel processo figlio (cmd1)**:
  - Si ridirige l’input standard (`stdin`) per leggere da *infile*.
  - Si ridirige l’output standard (`stdout`) per scrivere sull’estremità di scrittura della pipe (`end[1]`).
  
  Il codice sarà simile a:
  ```c
  dup2(f1, STDIN_FILENO);    // f1 è l'FD di infile
  dup2(end[1], STDOUT_FILENO); // end[1] diventa stdout
  close(end[0]);             // chiudiamo il lato di lettura, non serve qui
  ```

- **Nel processo padre (cmd2)**:
  - Si attende che il figlio finisca (con `waitpid()`).
  - Si ridirige l’input standard per leggere dalla pipe (`end[0]`).
  - Si ridirige l’output standard per scrivere su *outfile*.
  
  E il codice diventa:
  ```c
  waitpid(-1, &status, 0);
  dup2(end[0], STDIN_FILENO);  // end[0] diventa stdin
  dup2(f2, STDOUT_FILENO);     // f2 è l'FD di outfile
  close(end[1]);              // chiudiamo il lato di scrittura, non serve qui
  ```

L’idea è che **cmd1** legga da *infile* e scriva sulla pipe, mentre **cmd2** legge dalla pipe e scrive su *outfile*.

---

### Esecuzione dei comandi: execve()

Dopo aver impostato correttamente i file descriptor con `dup2()`, il programma esegue i comandi usando `execve()`. Questa funzione sostituisce il processo corrente con quello del comando specificato.  
  
I punti chiave di `execve()` sono:
- **path**: il percorso del comando, che puoi trovare usando `which` (es. `which ls`).
- **argv**: l’array degli argomenti (es. `{ "ls", "-la", NULL }`).
- **envp**: l’array delle variabili d’ambiente, utile per recuperare la variabile `PATH` e cercare il comando nelle directory giuste.

Se `execve()` non trova il comando, ritorna -1, per cui è importante gestire gli errori.

---

### Gestione degli errori e debugging

Ci sono alcuni accorgimenti importanti:
- **Controllo degli errori con perror()**: Dopo chiamate come `fork()` o `execve()`, usare `perror()` aiuta a capire eventuali errori.
- **Chiusura corretta dei file descriptor**: È fondamentale chiudere i lati della pipe che non servono. Se non lo fai, un'estremità aperta può far bloccare l'altro processo in attesa di input o output.
- **Uso di waitpid()**: Nel processo padre, è bene usare `waitpid()` per attendere il completamento del processo figlio, evitando così processi zombie.
- **Controllo dei permessi dei file**: Quando apri *infile* e *outfile*, verifica che esistano e che abbiano i permessi corretti. Se non puoi aprirli, il programma deve gestire l’errore in modo adeguato.

---

### Ricerca del comando: variabile PATH e access()

Prima di eseguire un comando, è utile verificare che esista. Si estrae la variabile d’ambiente `PATH` e si divide in più percorsi, così da poter cercare il comando in ciascuna directory. Se il comando non viene trovato, si deve mostrare un messaggio di errore tipo:

```
pipex: cmd_non_esistente: cmd_non_esistente not found
```

Per verificare l’esistenza del comando, si può usare la funzione `access()`.

---

### Riepilogo del flusso di esecuzione

1. **Apertura dei file**: Apri *infile* per leggere e *outfile* per scrivere.
2. **Creazione della pipe**: Usa `pipe(end)` per creare il canale di comunicazione.
3. **Fork dei processi**:
   - Il **figlio**:
     - Ridireziona `stdin` a *infile*.
     - Ridireziona `stdout` alla pipe.
     - Esegue **cmd1** con `execve()`.
   - Il **padre**:
     - Attende il completamento del figlio con `waitpid()`.
     - Ridireziona `stdin` dalla pipe.
     - Ridireziona `stdout` a *outfile*.
     - Esegue **cmd2** con `execve()`.
4. **Gestione e chiusura**: Chiudi i file descriptor non usati per evitare blocchi e gestire correttamente la terminazione dei processi.

---

### Conclusioni

Il progetto Pipex è un ottimo esercizio per imparare a gestire la comunicazione tra processi, a lavorare con file descriptor e a utilizzare funzioni fondamentali del C come `fork()`, `pipe()`, `dup2()` ed `execve()`. Comprendere questi concetti ti permette di capire meglio come funziona internamente una shell e come vengono gestiti i comandi e la redirezione degli input/output.

Spero che questa spiegazione ti abbia chiarito tutti i punti essenziali di Pipex! Se hai altre domande o dubbi, chiedi pure.
