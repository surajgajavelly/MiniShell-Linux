# MiniShell - Custom Linux Shell

A modular, robust Unix-like shell implemented in C. This project was developed to explore the internal workings of the Linux kernel, specifically process management and Inter-Process Communication (IPC).

## 🚀 Features

- **Command Execution:** Executes standard external commands (ls, cat, grep, etc.) using `fork` and `execvp`.
- **N-Level Piping:** Supports multiple pipes (e.g., `ls | grep .c | wc -l`) with proper file descriptor redirection.
- **Signal Handling:** Custom handlers for `SIGINT` (Ctrl+C), `SIGTSTP` (Ctrl+Z), and `SIGCHLD` to manage background/foreground processes.
- **Job Control:** Built-in linked list to track, stop, and resume processes (`jobs`, `fg`, `bg`).
- **Internal Commands:** Custom implementations of `cd`, `pwd`, `exit`, and `echo` (supporting `$$`, `$?`, and `$SHELL`).
- **Dynamic Memory Management:** Efficient parsing of 1D input strings into 2D argument arrays using heap allocation.

## 🛠️ Technical Prerequisites

- **System Calls:** `fork`, `waitpid`, `pipe`, `dup2`, `execvp`, `chdir`.
- **IPC:** Anonymous pipes for data redirection between processes.
- **Data Structures:** Singly Linked List for job tracking.

## 📂 Project Structure

- `main.c`: Entry point and global variable initialization.
- `scan_input.c`: Main shell loop and input parsing.
- `execute_external.c`: Logic for dispatching commands and memory management.
- `n_pipe.c`: Implementation of the N-pipe redirection logic.
- `signal_handler.c`: Custom signal management.

## 🔨 How to Build

1. Clone the repository:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/MiniShell-Linux.git](https://github.com/YOUR_USERNAME/MiniShell-Linux.git)

2. Build using the provided Makefile:
    ```bash
    make

3. Run the shell:
    ```bash
    ./minishell

---

## 3. Initial Push from your Terminal

Once the GitHub repo is ready, run these commands in your `MINISHELL` folder:

1.  **Initialize local git:**
    ```bash
    git init
    ```
2.  **Add your remote:**
    ```bash
    git remote add origin <PASTE_YOUR_REPO_URL_HERE>
    ```
3.  **Commit and Push:**
    ```bash
    git add .
    git commit -m "Initial commit: Completed modular shell with N-pipes and signal handling"
    git branch -M main
    git push -u origin main
    ```



**Would you like me to help you refine your `cd` and "Empty Input" logic now so your first commit is as clean as possible?**