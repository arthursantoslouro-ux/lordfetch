# Lordfetch

**Lordfetch** is a system information tool for the terminal, written in C and inspired by tools such as Fastfetch and Neofetch.

This project was created as a way to learn C through practical development while working with Linux system information, ANSI colors, ASCII art, CMake, shell scripting, and terminal rendering.

## Features

Lordfetch can display:

- Operating system
- Kernel
- Architecture
- Hostname
- Uptime
- Linux distribution
- Shell
- CPU
- Environment
- RAM
- Username
- IP address
- Installed package count

It also supports:

- ASCII logos
- ANSI colors
- Linux distribution detection
- Android detection
- Termux detection
- Package manager detection
- Custom ASCII logos
- CMake builds

## Supported Environments

Lordfetch currently supports:

- Linux
- Android
- Termux

Package detection currently supports:

- `dpkg`
- `pacman`
- `rpm`
- `apk`

## Requirements

To build Lordfetch, you need:

- A C compiler
- CMake
- `xxd`
- Git

## Installation

Clone the repository:

```bash
git clone https://github.com/arthursantoslouro-ux/lordfetch.git && cd lordfetch
``` 

# compile and run 

```bash
cmake -S . -B cmake-build && cmake --build cmake-build && clear && ./cmake-build/lordfetch
```
The executable will be located in cmake-build


<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-blue" alt="License: MIT">
</p>

