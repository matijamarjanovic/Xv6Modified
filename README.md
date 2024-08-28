# XV6 Implemented Encryption and Increased Max File Size

## Overview

This project enhances the XV6 operating system by implementing file encryption and supporting larger maximum file sizes. These enhancements improve the security and scalability of the file system, making it more robust and capable of handling modern requirements.

## Table of Contents
- [Project Features](#project-features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Encrypting Files](#encrypting-files)
  - [Handling Larger Files](#handling-larger-files)
- [Technical Implementation](#technical-implementation)
  - [Double Indirect Inode](#double-indirect-inode)
  - [File Encryption](#file-encryption)
  - [System Calls](#system-calls)
  - [User Programs](#user-programs)
  - [Testing and Validation](#testing-and-validation)
- [Directory Structure](#directory-structure)

## Project Features

- **Increased Maximum File Size**: Implemented using a double indirect pointer in the inode structure, allowing the file system to manage much larger files than the original XV6.
- **File Encryption**: Adds functionality to encrypt and decrypt files, ensuring data security and privacy.

## Getting Started

### Prerequisites

To work with this project, you need the following tools installed on your system:

- GCC (GNU Compiler Collection)
- QEMU (for emulating the XV6 OS)
- Make

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/stefann-01/xv6-implemented-encription-and-incresed-max-file-size.git
   cd xv6-implemented-encription-and-incresed-max-file-size
   ```

2. **Build the project**:
   ```bash
   make
   ```

3. **Run the operating system**:
   ```bash
   make qemu
   ```

## Usage

### Encrypting Files

The project provides commands to encrypt and decrypt files. Use the following commands to interact with encrypted files:

- **Encrypt a file**:
  ```bash
  encr <filename>
  ```

- **Decrypt a file**:
  ```bash
  decr <filename>
  ```

### Handling Larger Files

With the new double indirect inode implementation, the system supports larger files. Create and manipulate large files as follows:

- **Create a large file**:
  ```bash
  dd if=/dev/zero of=largefile bs=1M count=1024
  ```

## Technical Implementation

### Double Indirect Inode

The double indirect inode mechanism allows the file system to reference more data blocks than the original single indirect method. Here’s a breakdown of the changes made:

- **Inode Structure**: Modified to include an additional pointer for double indirect blocks. A file can consist of 11 direct blocks, 128 single indirect blocks, and 128*128 double indirect blocks.
- **Block Allocation**: Updated the block allocation logic to handle double indirect references.
- **File Operations**: Adjusted read and write operations to correctly navigate the new inode structure.

### File Encryption

File encryption is integrated into the file system’s read and write processes. Here’s an overview of the encryption implementation:

- **Encryption Algorithm**: Implements a Caesar cipher for file encryption. The key is a global integer set through a system call.
- **File Read/Write**: Modified the `read` and `write` system calls to include encryption and decryption steps.
- **Key Management**: Added functionality to manage encryption keys securely within the file system.

### System Calls

Several new system calls were implemented to support the encryption functionality:

- **setkey(int key)**: Sets the global encryption/decryption key.
- **setecho(int echo)**: Controls the echo functionality on the console.
- **encr(int fd)**: Encrypts a file using the current global key.
- **decr(int fd)**: Decrypts a file using the current global key.

### User Programs

New user programs were added to facilitate the use of the new system calls:

- **setkey**: Sets the encryption/decryption key.
  ```bash
  setkey <key>
  ```

- **encr**: Encrypts a file.
  ```bash
  encr <filename>
  ```

- **decr**: Decrypts a file.
  ```bash
  decr <filename>
  ```

- **blockwriter**: Creates a file of a specified size with predictable content.
  ```bash
  blockwriter -o <filename> -b <block_count>
  ```

### Testing and Validation

Extensive testing was conducted to ensure the stability and correctness of the new features:

- **Unit Tests**: Added unit tests for new and modified functions.
- **Integration Tests**: Conducted integration tests to validate overall system functionality.
- **Performance Testing**: Evaluated the performance impact of the new features, particularly the encryption and double indirect inode management.

## Directory Structure

The repository is organized as follows:

- `bootloader/`: Contains the bootloader code.
- `kernel/`: Contains the kernel code, including the modifications for encryption and double indirect inodes.
- `user/`: Contains user-level programs and utilities, including encryption tools and test programs.
- `tools/`: Contains tools and utilities for building and running the OS.
- `Makefile`: Build configuration for the project.
- `specification.pdf`: Detailed project specification document.
