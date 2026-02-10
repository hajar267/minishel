# Minishell

*This project has been created as part of the 42 curriculum by hfiqar. and istili.*

## Description

Minishell is a simplified bash-like shell implementation in C. This project provides a deep understanding of process creation, 
file descriptors, signal handling, and command execution. The goal is to recreate core shell functionalities including command parsing, 
environment variable expansion, redirections, pipes, and built-in commands.

## Team Responsibilities

**hfiqar - Parsing & Tokenization:**
- Lexical analysis and tokenization of command input
- Environment variable expansion (`$VAR`, `$?`)
- Heredoc implementation (`<<`)
- File descriptor management for redirections (`<`, `>`, `>>`)
- Pipe setup and fd handling (`|`)
- Syntax validation and error handling

**istili - Execution:**
- Command execution and process management
- Built-in commands implementation (cd, echo, pwd, export, unset, env, exit)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- PATH resolution and executable search
- Process forking and waiting
- Exit status management

## Features

- **Command Parsing**: Tokenizes and parses complex command lines
- **Environment Variables**: Expands `$VARIABLE` and `$?` (exit status)
- **Redirections**: Input (`<`), output (`>`), append (`>>`)
- **Heredoc**: Multi-line input with delimiter (`<<`)
- **Pipes**: Chain multiple commands (`cmd1 | cmd2 | cmd3`)
- **Quotes**: Single (`'`) and double (`"`) quote handling
- **Built-ins**: cd, echo, pwd, export, unset, env, exit
- **Signal Handling**: Proper behavior with Ctrl-C, Ctrl-D, Ctrl-\

## Instructions

**Compilation:**
```bash
make
```

**Execution:**
```bash
./minishell
```

**Usage Examples:**
```bash
# Environment variables
echo $HOME $USER
echo $?

# Redirections
cat < infile > outfile
ls -la >> output.txt

# Heredoc
cat << EOF
Hello World
EOF

# Pipes
ls -l | grep .c | wc -l

# Combined
< input.txt grep "pattern" | sort | uniq > output.txt
```

**Cleaning:**
```bash
make clean    # Remove object files
make fclean   # Remove objects and executable
make re       # Rebuild
```

## Technical Implementation

**Parsing Pipeline:**
1. **Tokenization**: Split input into tokens (words, operators, redirections)
2. **Expansion**: Replace environment variables with their values
3. **Syntax Check**: Validate command structure
4. **AST Building**: Create command table with redirections and pipes
5. **FD Management**: Open files and setup pipe file descriptors

**Execution Flow:**
1. Process built-in commands directly in parent
2. Fork child processes for external commands
3. Setup redirections and pipes in child processes
4. Execute commands with proper environment
5. Wait for children and collect exit status

## Resources

**Documentation:**
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- man pages: `bash`, `fork`, `execve`, `pipe`, `dup2`, `waitpid`

**Key Concepts:**
- Process creation and management
- File descriptor manipulation
- Signal handling in interactive programs
- Lexical analysis and parsing
- Environment variable management

**AI Usage:**
AI tools were used for:
- Understanding complex parsing edge cases
- Clarifying file descriptor duplication behavior
- Debugging tokenization logic
- Exploring different approaches to heredoc implementation
- Understanding signal handling in child processes

## Notes

- Built following the C norm and coding standards
- No memory leaks (verified with valgrind)
- Handles edge cases and error conditions gracefully
- Follows bash behavior for command parsing and execution

---

*A journey into the depths of shell implementation and process management.*
