_This project has been created as part of the 42 curriculum by boenkhja, rheidary_

## Description

The minishell project is an attempt to learn about the widely used Bourne Again Shell (bash) and reimplement ceratin features and functionality in a contained enviornment.
Being no small task the project is therefore a group project and we have chosen to split the workflow into two parts (while simultaneously helping eachother where needed) Parsing and Execution.

Parsing consists of gathering input from the user and transferring the data collected to the Executor in a preferred fashion.

Execution consists of taking the given data and executing commands given the arguments.

## Instructions

Our minishell only supports the Linux OS although a Docker container for a Linux enviornment can be installed by the user to be able to use the Shell on other OSs.

The system must contain atleast approximately 100KB to be able to run the shell, although this amount can be reduced by manually reducing the size of the ARENA memory management system by finding
the arena_create() function and setting the passed size parameter to a lower size. Although this comes with drawbacks since the shell will then have a reduced capacity in memory and therefore execute
commands with a reduced size. Alternatively if the device contains more memory the size can also be increased to support bigger commands.

To compile the program run "make" in the terminal or "make tidy" to remove unneccsary object files.

## Feature list

┏ Parsing:
┗━━━ 1: Tokenization
┗━━━ 2: Parameter Expansion
┗━━━ 3: Word Splitting
┗━━━ 4: Quote removal

Execution:
┏ Builtins
┗━━━ cd
┗━━━ echo
┗━━━ env
┗━━━ exit
┗━━━ export
┗━━━ pwd
┗━━━ unset
Heredocs
Redirections

Memory Arena:
A recently popularized memory management system, used throughout the project, meant to reduce mental overload of MMM.

Environment:
Support for building copying and building an environment. Does not live in the arena.

## Resources

For all references to how we decided to implement our functionality please refer to the GNU Bash Reference Manual.
!!! Our shell is INSPIRED and EMULATES certain functionalities of bash and is not a direct copy or support everything that bash does !!!