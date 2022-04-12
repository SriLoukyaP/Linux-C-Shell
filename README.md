#  Linux Shell in C

## Introduction

This is an implementation of a Linux shell written in C language.


## Run the shell
1. Run the command `make`.
2. Run `./shell` to get a prompt of the form `username@system_name:path`.
3. Run any command in the shell. It can entail as many number of tabs and spaces, the shell accounts for those.
4. In order to exit, run `quit`.

### Description of the files
1. `main.c`  
This contains the main function of the program. The main function includes the primary shell-loop of the program and is responsible for executing other commands.
2. `input.c`  
Reads the input line
3. `display.c`  
Printing and Implementing the prompt of the shell 
4. `token.c `  
It also extracts the input and parse into commands broken by a semi-colon and tabs,spaces,new line.    
5. `implement.c`   
Based on whether the input contains repeat command,arguments are passed accordingly to execute the actual command  

6. `part.c`  
Checks the input,and appropriately calls the required function  

7. `display.c`  
Printing and Implementing the prompt of the shell 

### Commands
1. `cd [file]`
- Changes directory to the directory specified, throws an error if the directory does not exist.
- Implemented in `cd.c`
2. `echo [arguments]`
 - Displays whatever is specified in [arguments]. 
 - Accounts for double quotes as well.
 - Implemented in `echo.c`
3. `pwd`
- Displays the name of the working directory.
- Implemented in `pwd.c`
4. `ls [-l -a] [directory]`
 - Lists all the files and directories in the specified directory in alphabetical order.
- Variations such as `ls, ls . , ls ..` also work.
- Also handles multiple directories as arguments. eg. `ls -l dir1 dir2 dir3`.
- Throws error if you try to `ls` on anything except a directory. 
- Implemented in `ls.c`
5. `pinfo [PID]`
- Prints  details about the process status, memory, and executable path.
- Just `pinfo` with no arguments gives details of the shell.
- Implemented in `pinfo.c`
6. `repeat <no. of times to be run> command`
- The command is responsible for executing the given instruction multiple times.
- Checked for repreat command in `implement.c`  
7. `jobs`
- prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number (a sequential number assigned by your shell), process ID and their state, which can either be running or stopped
- There may be flags specified as well. 
   - If the flag specified is -r , then prints only the running processes 
   - If the flag is -s then print the stopped processes onl
- Implemented in `jobs.c`


8. `sig <job_num> <signal_number> `
- Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to s ​ ignal number​ to that process.
- Throws an error if no job with the given number exists.
- Implemented in `sig_comm.c`


9. `fg <jobNumber>`
    
- Brings a running or a stopped background job with given job number to foreground.
- Implemented in `fg.c`

10. `bg <jobNumber>`

- Changes a stopped background job to a running background job.
- Implemented in `bg.c`

11. `quit`
- Exits the shell with return status as success 
### Foreground and Background Processes

- All other commands are treated as system commands like emacs, vim etc.
- To run a process in the background, follow the command with a '&' symbol. Eg. `emacs &`.
- Upon termination of a background process, the shell prints its PID and exit status.
- Handles `&` . eg. `emacs& , emacs         &, ls -l&`.
- Implemented in `fbbg.c`
## Additional Features

1. `Input-Output Redirection & Piping`

- Handles `<`, `>`, `>>`, and `|` operators appropriately, wherever they are in the command
- Throws error if syntax is incorrect
- Implemented in `redirect.c` and `pipe.c`
2. `CTRL-Z`
- Sends SIGTSTP signal to the current foreground job of the shell​.
- Changes the status of currently running job to stop, and pushes it to the background.
- Implemented in `signal.c`

3. `CTRL-C`

- Sends SIGINT signal to the current foreground job of the shell​.
- If there is no foreground job, then the signal does not have any effect.
- Implemented in `signal.c` 
4. `CTRL-D`
- Logs you out of the shell, without having any effect on the actual terminal.
- If get line returns -1,it logs out.
