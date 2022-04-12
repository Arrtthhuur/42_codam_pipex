# 42_codam_pipex
This project is the discovery in detail and by programming of a UNIX mechanism that you already know: pipes.

## Usage

The pipex program will be executed as follows:

```bash
./pipex file1 cmd1 cmd2 file2
```

It must take 4 arguments:

• file1 and file2 are **file names**.

• cmd1 and cmd2 are **shell commands** with their parameters.


It must behave exactly the same as the shell command below:
```bash
$> < file1 cmd1 | cmd2 > file2
```

### Constraints
Functions allowed: open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid.


### Return value
The return value of pipex should be the exit code of the second command.

## Flowchart
### Overview
<img width="597" alt="Screen Shot 2022-04-12 at 11 03 35 AM" src="https://user-images.githubusercontent.com/43698378/162923607-07f658cc-20fc-4c89-bc1d-2154e56833ae.png">

### Input parsing
<img width="759" alt="Screen Shot 2022-04-12 at 11 04 20 AM" src="https://user-images.githubusercontent.com/43698378/162923691-8898dda5-c6c8-4f9f-ba9a-e526bd2eff3b.png">

### Child process 1 & 2
<img width="633" alt="Screen Shot 2022-04-12 at 11 05 03 AM" src="https://user-images.githubusercontent.com/43698378/162923779-eb8bf33b-9598-4fcf-9bda-f4fe19e7a3ca.png">
<img width="633" alt="Screen Shot 2022-04-12 at 11 05 24 AM" src="https://user-images.githubusercontent.com/43698378/162923827-26ccb7a9-c9a3-4484-8dd4-74980e971225.png">

### Command execution
<img width="565" alt="Screen Shot 2022-04-12 at 11 05 43 AM" src="https://user-images.githubusercontent.com/43698378/162923977-86da3121-fbf7-4afc-b0ab-af28b1bbc0b4.png">

### Parent process
<img width="506" alt="Screen Shot 2022-04-12 at 11 05 59 AM" src="https://user-images.githubusercontent.com/43698378/162924003-295878a1-bb87-4d05-8964-25c0fa5fb0ad.png">


## Examples
### a.
```bash
./pipex infile "ls -l" "wc -l" outfile
```

Should behave like: 
```bash
< infile ls -l | wc -l > outfile
```

### b.
```bash
./pipex infile "grep a1" "wc -w" outfile
```

Should behave like: 
```bash
< infile grep a1 | wc -w > outfile
```
