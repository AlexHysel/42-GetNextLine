
*This project has been created as part of the 42 curriculum by <login1>.*

# Get Next Line (GNL)

## Description

**Get Next Line** is a core project of the 42 School curriculum.  
The objective of this project is to implement a function, `get_next_line`, that reads a file descriptor line by line, returning one line per function call.

The function must:
- Read from a file descriptor until a newline character (`\n`) or **End Of File (EOF)** is reached.
- Preserve unread data between calls.
- Allocate memory dynamically for each returned line.
- Be robust against different buffer sizes and input sources.

The **bonus part** extends this behavior to support **multiple file descriptors simultaneously**, ensuring that reading from one file descriptor does not interfere with another.

---

## Function Prototype

```c
char *get_next_line(int fd);
````

Returns a line ending with `\n` if present, or `NULL` if EOF is reached and no data remains or an error occurs.

---

## Instructions

### Compilation for testing
`get_next_line.c` and `get_next_line_bonus.c` contain COMMENTED main funtions to test them.
Uncomment them and compile the project with your own files or test files:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

For the **bonus version**:

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c
```

To test them just execute the a.out file with file name (or few file names if it is bonus) as arg to read them.

```bash
./a.out get_next_line.c
```

You may define `BUFFER_SIZE` at compile time:

```bash
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

### Usage Example

```c
int fd = open("example.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Algorithm & Design Choices

### Core Algorithm

1. **Buffered Reading**

   * Use `read()` to fetch chunks of data of size `BUFFER_SIZE`.
   * If `read()` returned negative, it immidiatly skips the reading part, frees everything and returns `NULL`.
   * Else: append each chunk (`stash_expand` function) to a persistent buffer called the **stash** and repeat it until `was_read == BUFFER_SIZE` and `buffer` doesnt contain `\n`.

2. **Line Extraction**

   * If `read()` returned integer more then 0, it uses `stach_extract_line` is used to extract one line from stash and leave other chars in it. if it returned full stash, stash will be set to `NULL`.
   * If `read()` returned 0 (EOF) and the stash contains data, return the remaining data as the final line.
   * if it returned negative, it will just remove everything and return `NULL`

4. **Memory Safety**

   * All returned lines (or `t_fd_list` in bonus) are dynamically allocated.
   * All allocated memotry is freed when no longer needed.

### Bonus

Bonus part works the same way, but it uses static `t_fd_list` with stashes and 3 additional methods instead of `stash`

```c
typedef struct s_fd_list_node
{
    int                     fd;
    char                    *stash;
    struct s_fd_list_node   *next;
} t_fd_list;
```

| Column 1 | Column 2 |
|----------|----------|
| `add_node` | Adds node with exact fd and returns it. If this node already exists, it will just return it |
| `remove_node` | Used to free the node by its fd |
| `node_by_fd` | Returns node with exact fd if it exists, otherwise `NULL`|


This approach guarantees:

* No data loss between calls
* Minimal reads from the file descriptor
* Correct handling of partial lines

---

## Resources

### Technical References

* `man read`
* `man open`
* `man close`
* 42 School subject PDF for **get_next_line**

### AI Usage Disclosure

AI tools were used **only for assistance**, including:

* Finding errors
* Writing basic README

All implementation logic, coding, testing, and final decisions were made by the project author in compliance with 42 rules.

---
