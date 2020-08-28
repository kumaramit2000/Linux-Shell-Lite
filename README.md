# Linux-Shell-Lite
Linux Shell Lite is a simple implementation of a shell in C. It demonstrates the basics of how a shell works. That is: read, parse, fork, exec, and wait. Since its purpose is demonstration (not feature completeness or even fitness for casual use), it has many limitations, including:
- Commands must be on a single line.
- Arguments must be separated by whitespace.
- No quoting arguments or escaping whitespace.
- No piping or redirection.
- Only builtins are: echo, pwd, cd, jobs, quit, kjob, killallbg, fg, pinfo. 

# Running
Use gcc -o lsh src/main.c to compile, and then ./lsh to run. If you would like to use the standard-library based implementation of lsh_read_line(), then you can do: gcc -DLSH_USE_STD_GETLINE -o lsh src/main.c.

