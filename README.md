_This project has been created as part of the 42 curriculum by boenkhja, rheidary._

## Description

Minishell is a simplified Unix shell implementation that recreates core functionality of the Bourne Again Shell (bash). This project serves as an educational exploration into shell mechanics, process management, and command-line interface design. The goal is to build a functional shell capable of parsing user input, managing environment variables, executing commands, handling redirections and pipes, and implementing essential built-in commands.

As a collaborative project, the workload was divided into two primary components: **Parsing** (tokenization, expansion, and input processing) and **Execution** (command execution, builtin management, and process control). Both team members contributed across these domains while maintaining their focus areas.

The shell emulates bash behavior for fundamental operations, providing users with an interactive command-line environment that handles complex command structures including pipelines, heredocs, and various types of redirections.

## Instructions

### System Requirements

- **Operating System**: Linux (primary support)
  - For other operating systems, a Docker container with a Linux environment can be used
- **Memory**: Approximately 100KB minimum
  - The memory requirement can be adjusted by modifying the `arena_create()` function's size parameter
  - Reducing memory size will limit command execution capacity
  - Increasing memory size (if available) supports more complex command sequences
- **Dependencies**: 
  - GNU Readline library
  - GCC or compatible C compiler
  - Make

### Compilation

To compile the project, navigate to the repository root and run:

```bash
make
```

To compile and remove unnecessary object files:

```bash
make tidy
```

### Execution

After compilation, launch the shell with:

```bash
./minishell
```

The shell will present an interactive prompt where commands can be entered.

## Features

### Parsing Pipeline

1. **Tokenization**: Breaking input into discrete tokens (words, operators, metacharacters)
2. **Parameter Expansion**: Expanding variables (e.g., `$USER`, `$HOME`) and special parameters
3. **Word Splitting**: Separating expanded results based on delimiters
4. **Quote Removal**: Processing and removing quotes while preserving quoted content

### Built-in Commands

The following built-in commands are implemented:

- `cd` - Change directory
- `echo` - Display text (with `-n` option support)
- `env` - Display environment variables
- `exit` - Exit the shell
- `export` - Set environment variables
- `pwd` - Print working directory
- `unset` - Remove environment variables

### Advanced Features

- **Heredocs**: Multi-line input with delimiter-based termination (`<<`)
- **Redirections**: Input (`<`), output (`>`), and append (`>>`) redirection
- **Pipelines**: Connecting multiple commands with pipes (`|`)
- **Environment Management**: Full environment variable support with modification capabilities
- **Signal Handling**: Proper handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-

### Memory Management

The project utilizes an **Arena Memory Management System**, a modern approach to memory allocation that:
- Reduces the cognitive overhead of manual memory management
- Provides efficient bulk allocation and deallocation
- Minimizes memory fragmentation
- Centralizes memory lifecycle management

The environment subsystem operates independently of the arena for persistence across commands.

## Technical Choices

- **C Programming Language**: For low-level system interaction and performance
- **Arena Allocator**: To simplify memory management in complex parsing operations
- **Modular Architecture**: Separation of parsing and execution concerns for maintainability
- **POSIX Compliance**: Adherence to standard Unix process and file descriptor management

## Testing

A comprehensive testing suite is included in the `tester/` directory. This third-party tester (42_minishell_tester) can be used to validate functionality across various categories:

```bash
cd tester
bash tester.sh m    # Run mandatory tests
bash tester.sh vm   # Run mandatory tests with valgrind
```

Refer to `tester/README.md` for detailed testing instructions and options.

## Resources

### Primary Reference

- **GNU Bash Reference Manual**: The authoritative source for bash behavior and implementation details
  - URL: https://www.gnu.org/software/bash/manual/bash.html
  - Used for understanding command parsing, expansion rules, builtin specifications, and shell semantics

### Additional Documentation

- POSIX Shell Command Language Specification
- "Advanced Programming in the UNIX Environment" by W. Richard Stevens
- Unix Process Management and System Calls documentation

### AI Usage Disclosure

**AI tools were utilized in the following capacities:**

1. **Research and Concept Clarification**:
   - Exploring shell parsing techniques and tokenization strategies
   - Understanding POSIX standards and bash-specific behaviors
   - Researching memory management patterns (arena allocators)
   - Clarifying system call usage (`fork`, `execve`, `pipe`, `dup2`, etc.)

2. **Documentation and README Composition**:
   - Structuring and writing this README document
   - Organizing technical information for clarity
   - Ensuring comprehensive coverage of project features and requirements

**AI was NOT used for**:
- Writing the core implementation code
- Solving project-specific algorithmic challenges
- Debugging or fixing project issues
- Making architectural decisions

All implementation work, problem-solving, and technical decisions were made by the project contributors.

---

**Important Note**: This shell is inspired by and emulates certain functionalities of bash. It is **not** a complete implementation and does not support all bash features. It is an educational project designed to understand fundamental shell mechanics.