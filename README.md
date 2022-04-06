# README
24th September 2021
* [Specifications](##specifications-followed-for-minishell)
* [Key features](#key-features-included)
* [Constraints](#constraints-for-minishell)
* [Instructions](#instructions-to-run-minishell)
* [Mindmap/Overview](#overview-points)
* [Some specifications](#specifications-to-follow)

## SPECIFICATIONS FOLLOWED FOR MINISHELL
* Works on LINUX
* Written using C++ (POSIX based system) using g++ 9.3.0 for Ubuntu
* MiniShell simulates bash and tries to include a reasonable subset of commands.

## KEY FEATURES INCLUDED:
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

## CONSTRAINTS FOR MINISHELL
### Single Level Piping only 
On recognising piping, the command is executed directly
### Single Level Redirection Only 
On recognising piping, the command is executed directly,multi-level redirection is restricted.
### No simultaneous Piping and Redirection
Redirection is checked for only if piping is not present

## INSTRUCTIONS TO RUN MINISHELL
1. Compile with g++ or gnu post 9.2
2. Run with linux based OS
## OVERVIEW POINTS
1. The Shell boots up with the following screen giving developer credits and information and welcoming user to the shell, which clears and starts the shell after a delay of 4(max) seconds. The shell takes in input and produces corresponding output, in tandem with the flowchart defined for general systems.
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


## SPECIFICATIONS TO FOLLOW
* Blank Lines are handled quite well, they don’t get recorded in history.
* Redirection : MAKE SURE TO type both the command with no space before and after the
redirection symbol (> , <, >>)
* Wrong commands give prompt to appropriate errors.
* setenv : type command as setenv (environment variable) = (new value)
Make sure you use appropriate spacings.
* Exiting deletes history file(with exit or quit or x)
