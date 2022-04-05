CS242-Assignment 2 MINISHELL
Vatsal Gupta
200101105


README
24th September 2021

● Name: Vatsal Gupta
● Roll No: 200101105
● Programming Language Used: C++
● Operating System: Linux (Ubuntu 20.04 LTS)

ZIP FILE CONTENTS
● 200101105_Assign02.cpp (Source Code)
● FLOWCHART.pdf
● assignment2.pdf

SPECIFICATIONS FOLLOWED FOR MINISHELL
● Works only on LINUX OS
● Written using C++ (POSIX based system) using g++ 9.3.0 for Ubuntu
● Flowchart as mentioned in FLOWCHART.pdf has been followed, and there are constraints
in minishell’s capability in line with this flowchart.
● MiniShell simulates bash and tries to include a reasonable subset of commands as per
instructions in sir’s mail.
KEY FEATURES INCLUDED:
● Environment variables:
*printenv: lists all environment variables.
*setenv( variable_name = variable_value): changes value of variable_name as per
requirement.
*Any particular environment variable can be seen from writing the name of that
variable or writing echo $VAR where VAR is variable name.(shown later too.)
● Path functions: Most UNIX Commands are enterable.
● Parsing
● Piping
● Input and Output redirection:
Read mode, Write mode, Append mode

CONSTRAINTS FOR MINISHELL
● Single Level Piping only (On recognising piping, the command is executed Directly
without searching for redirection according to flowchart)
● Single Level Redirection Only (On recognising piping, the command is executed Directly
without searching for redirection according to flowchart)
● No simultaneous Piping and Redirection(Redirection is checked for only if piping is not
present as per flowchart)
● Double Redirection is not allowed (in flowchart, further redirections are checked if and
only if the previous specified redirection isn’t found.)
● Most of the following commands work flawlessly (internal+external), however due to
limitations of C++ having access to the internal workings of an extended system,some
natural functions which are internal to a shell but not to a C++ program may not
work.Inspite of this, the following have been explicitly defined as internal commands to
without using execvp and work perfectly:
1. help
2. cd
3.setenv *
4.exit (or quit or x)
5.history
6.printenv
7.clear
*PLEASE NOTE: setenv works in the following format:
setenv variable_name = new_variable_value
If this is successful, you should get a VALUE CHANGED prompt and the same can be
checked by writing the variable name in the terminal which will output the value of the
environment variable.

INSTRUCTIONS TO RUN MINISHELL
● Compile with g++ 200101105_Assign02.cpp
● Run with ./a.out
OVERVIEW POINTS
● The Shell boots up with the following screen giving developer credits and information and
welcoming user to the shell.
Which clears and starts the shell after a delay of 4(max) seconds. The shell takes in input
and produces corresponding output, in tandem with the flowchart.
● The shell implements internal commands flawlessly and its details can be seen by typing
help in the terminal. Most commands of UNIX work too.
● Main commands are :
1.man (example man man) displays manual
2.which
3.chsh
4.passwd
5.date
6.cal
7.clear
8.history
9.sleep
10.apropos
11.exit
12.shutdown
13.ls
14.cat
15.more
16.touch
17.mv
18.mkdir
19.rmdir
20.script
21.nano
22.find
23.touch
24.less
25.chmod
26.grep
27.printenv
28.getenv


SPECIFICATIONS TO FOLLOW
● Blank Lines are handled quite well, they don’t get recorded in history.
● Redirection : MAKE SURE TO type both the command with no space before and after the
redirection symbol (> , <, >>)
● Wrong commands give prompt to appropriate errors.
● setenv : type command as setenv (environment variable) = (new value)
Make sure you use appropriate spacings.
● Exiting deletes history file(with exit or quit or x)

Examples of each step:
● Help
● clear:(has to be seen by user of shell)
● Environment variables output (all kinds)
● Only cd and cd with a different directory
● Input redirection,output redirection(write and append)
● History (the file is created in user’s tmp folder as per flowchart which MUST be present in
all UNIX based systems)
● exit
