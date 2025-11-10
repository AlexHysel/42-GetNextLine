Get Next Line (GNL)

💡 Project Overview

The get_next_line project is a core exercise from the 42 School curriculum. Its main objective is to implement a robust and efficient function that reads text from a file descriptor, returning one line at a time. The function is designed to handle calls sequentially, ensuring that it preserves any remaining data (the "stash") from previous reads until the subsequent call.

The implementation is split into two parts: the required function and the bonus part, which handles multiple file descriptors simultaneously without corrupting the read position of any individual file.

⚙️ Function Prototype

```char *get_next_line(int fd);```


The function reads from the file descriptor fd until a newline character (\n) or the End-Of-File (EOF) is encountered.

Return Value:

The read line, including the final newline character (if present). The returned string is allocated using malloc and must be freed by the caller.

NULL if EOF is reached and no bytes were read, or if an error occurred.

🚀 Bonus Implementation: Static Linked List

For the bonus challenge—handling simultaneous reads from multiple file descriptors—a persistent data structure is required to store the read remainder (stash) for each file.

Instead of a fixed-size array (which wastes memory or fails if FDs are too large), this implementation utilizes a Static Linked List to map the file descriptor (FD) to its corresponding data buffer.

Structure (t_fd_list)

The core structure is a node defined as follows:

```
typedef struct s_fd_list_node
{
    int                     fd;         // The File Descriptor (Key)
    char                    *stash;     // Dynamically allocated buffer holding the remaining data
    struct s_fd_list_node   *next;      // Pointer to the next node in the list
} t_fd_list;
```

Mechanism

Persistence: The head of the list (static t_fd_list *list;) is declared static within get_next_line.c. This ensures the list survives between function calls, preserving the state for every open file across the entire program execution.

Lookup (Key Conversion): When get_next_line(fd) is called, the function traverses the linked list linearly (the O(N) operation) using the fd as the key to find the correct node.

Dynamic Stash: Once the node is found, the function works directly with the char ** pointer inside the node (&current_node->stash). This allows the stash to be dynamically expanded (via realloc or equivalent) or trimmed, ensuring the persistent node always holds the correct, up-to-date memory address.

Cleanup: When a file is fully exhausted (EOF and no data left), the corresponding node is freed (free(stash) then free(node)) and removed from the list, preventing memory leaks and keeping the list efficient.

It opens all files provided as command-line arguments.

It cycles through the list of open FDs, calling get_next_line once for each FD in turn.

This cycling continues until all file descriptors have returned NULL, confirming that the function can correctly maintain the read position and data integrity for all files simultaneously.
