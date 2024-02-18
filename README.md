<a name="readme-top"></a>

<br />
<div align="center">
    <img src="src/images/dos.webp" alt="Logo" width="128" height="128">

  <h3 align="center">B-DOS</h3>

  <p align="center">
    This repository is a very simplified version of an MS-DOS-like OS made in C.
  </p>
</div>

<details>
  <summary>Table of contents</summary>
  <ol>
    <li>
      <a href="#about">About</a>
      <ul>
        <li><a href="#built-with">Built with</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installing</a></li>
        <li><a href="#build">Build</a></li>
      </ul>
    </li>
    <li>
      <a href="#usage">Usage</a>
      <ul>
        <li><a href="#known-issues">Known issues</a></li>
      </ul>
    </li>
  </ol>
</details>


## About
<a name="about"></a>

The motivation behind this project is to discover more about low-level computing. The aim here is to understand how a basic OS works, by creating one from scratch.

To achieve my goals, I've chosen to use the C language, which I like, to which I'll have to couple ASM for the parts that require it.

<p align="right">(<a href="#readme-top">Up</a>)</p>

#### Context

While modern operating systems have evolved to be highly complex and feature-rich, B-DOS takes a step back to focus on essential functionalities such as file management, command-line interface, and basic system operations. By stripping away unnecessary layers and features, B-DOS offers a clear and understandable platform for learning about the fundamentals of operating system design and implementation.

### Built with
<a name="built-with"></a>

* [C][c-url] (Standard C17)
* [ASM][asm-url]

## Getting started
<a name="getting-started"></a>

#### Try the OS

If you only want to try the B-DOS, you can clone the repository and build the ISO file. You can then use it as if you were manipulating any other ISO file : use it in Qemu, create a bootable USB key, ...

#### Edit code

If you want to edit/use the code, follow these steps:

<p align="right">(<a href="#readme-top">Up</a>)</p>

### Prerequisites
<a name="prerequisites"></a>

* Docker : [Docker][docker-url] is used to build and use the buildenv container.

If you don't want to use Docker, you want still build the image on your own system. However, you will need to use Linux. You will need :

* C : A C compiler. I recommend using GCC.
* ASM : An ASM compiler. I recommend using NASM.
* Other dependencies : `grub-pc-bin`, `grub-common` and `xorriso` for bootloader/iso.

### Installation
<a name="installation"></a>

1. Clone the repository
  ```sh
  git clone https://github.com/mathisbot/bdos.git
  ```

  or download code as Zip.

2. Build an image for the build environment:
```sh
  docker build buildenv -t build-bdos
```

### Build
<a name="build"></a>

For Windows users, there seems to be a problem for systems with WSL installed. If you have WSL, use WSL directly with the Linux commands. Remember that `cd /mnt` allows you to change disks (e.g. `cd /mnt/c` to enter C:).

1. Enter build environment :
* `docker run --rm -it -v "$(pwd)":/root/env build-bdos` (Linux)
* `docker run --rm -it -v "%cd%":/root/env build-bdos` (Windows CMD)
* `docker run --rm -it -v "${pwd}:/root/env" build-bdos` (Windows PS)

Don't forget to stop it later.

2. Build the image
```sh
  make build-bdos
```

<p align="right">(<a href="#readme-top">Up</a>)</p>

## Usage
<a name="usage"></a>

Please note that B-DOS is made for x86-64 architecture.

Once you have built the project and have successfully got the ISO file, you can use it as any other ISO file : make a bootable USB key, use it in Qemu (Please use `qemu-system-x86_64 -cdrom` to launch), ...

Currently, B-DOS does not do much things.

<p align="right">(<a href="#readme-top">Up</a>)</p>

### Known Issues
<a name="known-issues"></a>

Various problems and bugs may arise during development. If no obvious solution is found, they are listed here. If you come across another bug not listed, please report it using the Issues tab.
- None

<p align="right">(<a href="#readme-top">Up</a>)</p>

[c-url]: https://fr.wikipedia.org/wiki/C_(langage)
[asm-url]: https://en.wikipedia.org/wiki/Assembly_language
[docker-url]: https://www.docker.com