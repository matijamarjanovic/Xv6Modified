# Xv6Modified
(1)The xv6 operating system was modified to support advanced file system functionalities, including:
  
  Handling Large Files: Implemented the creation, reading, writing, editing, and deletion of large files using double indirect pointers within the inode structure.
  File Encryption: Added the capability to encrypt the content of specific files on disk.
  In addition to these file system enhancements, the following system calls and user programs were implemented:
  
  System Calls:
  
  int setkey(int key); - Sets the encryption key.
  int setecho(int echo); - Configures whether encryption status messages are displayed.
  int encr(int fd); - Encrypts the file associated with the file descriptor.
  int decr(int fd); - Decrypts the file associated with the file descriptor.
  User Programs:
  
  setkey - A program to set the encryption key.
  encr - A program to encrypt files.
  decr - A program to decrypt files.
  blockwriter - A utility to write data blocks.
  The code used as the starting point for this project was obtained using the specified command.
  
(2)The xv6 operating system was modified to enable shared memory between parent and child processes. The parent process can declare shared memory, which its direct children can access.
  
  System Calls Implemented:
  
  int share_data(char *name, void *addr, int size); - Allows a parent process to declare a shared memory structure.
  int get_data(char *name, void **addr); - Enables a child process to access the declared shared memory.
  System Modifications:
  
  fork(): Ensures child processes inherit shared memory structures from the parent.
  exec(): Maps shared memory starting from 1GB in the virtual address space of the new process.
  Process Termination: Properly handles memory release to avoid leaks.
  User Programs Implemented:
  
  dalle: A parent process that starts two child processes, coMMa and liSa, sharing text processing data.
  coMMa: Handles user commands to interact with shared memory data.
  liSa: Processes the text file, updating shared memory with the shortest and longest words per sentence.
  
