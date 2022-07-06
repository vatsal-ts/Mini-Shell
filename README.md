# README
24th September 2021
* [Specifications](##specifications-followed-for-minishell)
* [Key features](#key-features-included)
* [Constraints](#constraints-for-minishell)
* [Instructions](#instructions-to-run-minishell)
* [Mindmap/Overview](#overview-points)
* [Some specifications](#specifications-to-follow)
* [Examples of some functions](#examples)

## Specifications followed for minishell
* Works on LINUX
* Written using C++ (POSIX based system) using g++ 9.3.0 for Ubuntu
* MiniShell simulates bash and tries to include a reasonable subset of commands.

## Key features included
### Environment variables:
* <b>printenv</b> lists all environment variables.
* <b>setenv</b><br/><code>(variable_name = variable_value)</code><br/>changes value of variable_name as per
requirement.
* Any particular environment variable can be seen from writing the name of that
variable or writing echo $VAR where VAR is variable name.(shown later too.)
### Path functions: Most UNIX Commands are enterable.
#### Parsing
#### Piping
#### Input and Output redirection:
* Read mode, Write mode, Append mode
### The following commands work flawlessly (internal+external) 
however due to limitations of posix based compiler having access to the internal workings of an extended system,some natural functions which are internal to a shell but not to a C++ program may not
work.Inspite of this, the following have been explicitly defined as internal commands to
without using *execvp* and work perfectly:
1. help
2. cd
3. setenv *
4. exit (or quit or x)
5. history
6. printenv
7. clear<br/>
**PLEASE NOTE* : setenv works in the following format:<br/><code>
*setenv variable_name=new_variable_value*</code><br/>
If this is successful, you should get a "VALUE CHANGED" prompt and the same can be checked by writing the variable name in the terminal which will output the value of the environment variable.

## Constraints for minishell
### Single Level Piping only 
On recognising piping, the command is executed directly
### Single Level Redirection Only 
On recognising piping, the command is executed directly,multi-level redirection is restricted.
### No simultaneous Piping and Redirection
Redirection is checked for only if piping is not present

## Instructions to run minishell
1. Compile with g++ or gnu post 9.2
2. Run with linux based OS
## Overview points
1. The Shell boots up with the following screen giving developer credits and information and welcoming user to the shell. 
<!-- ![1](https://user-images.githubusercontent.com/84033475/177593242-57c6fd02-846a-46d2-8a40-1056518f8bfc.JPG) -->
<img src="https://user-images.githubusercontent.com/84033475/177593948-1f4f0036-d2e5-4426-ba42-15344bbde8b0.JPG" alt="drawing" width="75%">
Which clears and starts the shell after a delay of 4(max) seconds. The shell takes in input and produces corresponding output, in tandem with the flowchart defined for general systems.
2. The shell implements internal commands flawlessly and its details can be seen by typing
help in the terminal. Most commands of UNIX work too.
#### Main commands are :
1. man (example man man) displays manual
2. which
3. chsh
4. passwd
5. date
6. cal
7. clear
8. history
9. sleep
10. apropos
11. exit
12. shutdown
13. ls
14. cat
15. more
16. touch
17. mv
18. mkdir
19. rmdir
20. script
21. nano
22. find
23. touch
24. less
25. chmod
26. grep
27. printenv
28. getenv


## Specifications to follow
* Blank Lines are handled quite well, they don’t get recorded in history.
* Redirection : MAKE SURE TO type both the command with no space before and after the
redirection symbol (> , <, >>)
* Wrong commands give prompt to appropriate errors.
* setenv : type command as setenv (environment variable) = (new value)
Make sure you use appropriate spacings.
* Exiting deletes history file(with exit or quit or x)

## Examples
* help
<img src="https://user-images.githubusercontent.com/84033475/177595783-5efc456c-6067-4a8a-ab0b-b0e05a813b5b.JPG" alt="drawing" width="55%"/>
* Environment variables output (all kinds)
<img src="https://user-images.githubusercontent.com/84033475/177593242-57c6fd02-846a-46d2-8a40-1056518f8bfc.JPG" alt="drawing" width="60%"/>
* cd
<img src="https://user-images.githubusercontent.com/84033475/177596158-6dd311d3-c89e-4ebc-8675-eb9b7dd111fb.JPG" alt="drawing" width="50%"/>
* Input redirection,output redirection(write and append)
<img src="https://user-images.githubusercontent.com/84033475/177596551-1c463728-ca17-4f36-8339-206bc3084d26.JPG" alt="drawing" width="60%"/>
* History (the file is created in user’s tmp folder which MUST be present in all UNIX based systems)
<img src="https://user-images.githubusercontent.com/84033475/177597137-93e323c7-eaef-431b-8a68-23a8f461e324.JPG" alt="drawing" height="300px" />
* Exit
<img src="https://user-images.githubusercontent.com/84033475/177597423-5762ea52-939e-4a48-97a5-4c4db8c8755a.JPG" alt="drawing" width="60%" />
<!-- ![9](https://user-images.githubusercontent.com/84033475/177597423-5762ea52-939e-4a48-97a5-4c4db8c8755a.JPG) -->
* Piping example
<img src="https://user-images.githubusercontent.com/84033475/177597881-0ef99562-a36e-4a0f-8102-1bb61f65a639.JPG" alt="drawing" width="70%" />

