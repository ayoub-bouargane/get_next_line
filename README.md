*This project has been created as part of the 42 curriculum by aybouarg.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor and returns **one line per call**, including the trailing `\n` when there is one. Repeated calls return the whole content of the file line by line, and `NULL` is returned at the end of the file or on error.

```c
char *get_next_line(int fd);
```

The goal of the project is to learn about:

- file descriptors and the `read` system call,
- `static` variables and how they keep state between calls,
- dynamic memory management (`malloc` / `free`) without leaks, double frees or use-after-free,
- handling any `BUFFER_SIZE` (from `1` to very large values) and any line length.

Allowed functions: `read`, `malloc`, `free`. No `libft`, no `lseek`, no global variables.

### Files

| Part | Files |
|---|---|
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` |
| Bonus | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` |

The bonus part uses **a single `static` variable** and manages **several file descriptors at the same time** (reading fd 3, then 4, then 5, then 3 again, without mixing or losing the state of any of them).

## Instructions

### Compilation

`BUFFER_SIZE` is defined at compile time with `-D`. If it is not given, a default value from the header is used.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*s;

	fd = open("file.txt", O_RDONLY);
	while ((s = get_next_line(fd)) != NULL)
	{
		printf("%s", s);
		free(s);
	}
	close(fd);
	return (0);
}
```

The caller owns every returned line and must `free` it. `get_next_line` also works on `stdin` (`fd = 0`) and on pipes.

### Testing

```bash
# memory errors and leaks
cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 get_next_line.c get_next_line_utils.c main.c && valgrind ./a.out

# norm
norminette *.c *.h
```

Tested with `BUFFER_SIZE` = `1`, `2`, `5`, `42`, `10000000`, and with: empty file, one line without `\n`, only `\n`, consecutive empty lines, last line without `\n`, very long lines (100000 chars), invalid / closed fd, a directory, `stdin`, and a pipe.

## Algorithm

### Core problem

`read(fd, buf, BUFFER_SIZE)` returns a fixed amount of bytes that has nothing to do with line boundaries: one call can return half a line, exactly one line, or several lines. The kernel keeps the reading offset of the file descriptor and **never goes back**, so whatever has been read but not yet returned must be kept by the program between two calls.

### Chosen approach: a `static` remainder string

A `static char *remainder` keeps the bytes that were read but not returned yet. Each call does three steps:

1. **Fill**: while `remainder` contains no `\n`, `read` `BUFFER_SIZE` bytes into a temporary buffer, add a `'\0'`, and append it to `remainder` with `ft_strjoin`. Stop when a `\n` appears, when `read` returns `0` (end of file) or `-1` (error).
2. **Extract**: copy from the start of `remainder` up to and including the first `\n` (or everything if there is no `\n`) into a new string. This is the returned line.
3. **Update**: build a new `remainder` containing only what comes after the `\n`, and free the old one. If nothing remains, `remainder` becomes `NULL`.

Example with `BUFFER_SIZE = 4` and the file `hello\n world\n1337`:

| Call | Reads | `remainder` after fill | Returned | `remainder` after update |
|---|---|---|---|---|
| 1 | `hell`, `o\n w` | `hello\n w` | `hello\n` | ` w` |
| 2 | `orld`, `\n133` | ` world\n133` | ` world\n` | `133` |
| 3 | `7`, then `0` (EOF) | `1337` | `1337` | `NULL` |
| 4 | `0` (EOF) | `NULL` | `NULL` | `NULL` |

### Why this approach

- **Correct for any `BUFFER_SIZE`**: the loop condition depends on the presence of `\n`, never on the buffer size.
- **No lost data**: bytes read after the `\n` stay in `remainder` for the next call.
- **Works with any kind of fd** (files, `stdin`, pipes) because it only uses `read` sequentially and never needs `lseek`.
- **Simple memory model**: one dynamic string and one temporary buffer, so every exit path can be checked for leaks (read error, `malloc` failure, end of file, success).
- **Allowed by the subject**: a single `static` variable and no global variable.

### Error handling and memory

- Invalid input (`fd < 0` or `BUFFER_SIZE <= 0`) returns `NULL` immediately.
- On a `read` error or a failed `malloc`, the remainder and the temporary buffer are freed and `NULL` is returned.
- `ft_strjoin` and `update_remainder` free the old string themselves, so the caller just reassigns the pointer.
- The temporary buffer is allocated with `(size_t)BUFFER_SIZE + 1` to avoid an `int` overflow for very large values and to leave room for the `'\0'`.


### Bonus: several file descriptors

The single `static char *remainder` becomes a single `static char *remainder[FD_MAX]`, indexed by the file descriptor. Each fd has its own remainder, just as the kernel keeps an independent offset for each open file, so reading alternately from several fds never mixes their content. `FD_MAX` is `1024`, the default soft limit of open files per process (`ulimit -n`). A descriptor `>= FD_MAX` returns `NULL` instead of writing out of bounds. The helper functions are unchanged because they only receive one string.

## Resources

### References

- `man read`, `man open`, `man close`, `man malloc`, `man free`
- Valgrind manual: <https://valgrind.org/docs/manual/>
- 42 Norm and the project subject (PDF)

### Use of AI

- **Theory for the defense**: file descriptors, `open` / `read` internals, user mode vs kernel mode, `ulimit -n`, memory errors.