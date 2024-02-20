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

* [C][c-url]
* [ASM][asm-url]
* [GRUB][grub-url]

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

If you don't want to use Docker, you can still build the image on your own system. You will need to be on Linux (if you want to use Windows, you're on your own) and you will need :

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

2. Build a Docker image of the build environment:
```sh
  docker build buildenv -t build-bdos
```

### Build
<a name="build"></a>

1. Enter build environment :
* `docker run --rm -it -v "$(pwd)":/root/env build-bdos` (Linux)
* `docker run --rm -it -v "%cd%":/root/env build-bdos` (Windows CMD)
* `docker run --rm -it -v "${pwd}:/root/env" build-bdos` (Windows PS)

Don't forget to stop it later.

For Windows users, there seems to be a problem on systems having WSL installed. If you have WSL installed on your system, use WSL CLI directly with the Linux commands, otherwise there will be problems with disk sharing (`-v`). Remember that `cd /mnt` allows you to change disks (e.g. `cd /mnt/c` to enter C: from WSL).

2. Build the image
```sh
  make build-bdos
```

<p align="right">(<a href="#readme-top">Up</a>)</p>

## Usage
<a name="usage"></a>

Please note that B-DOS is made for x86-64 architecture.

Once you've successfully built the project and obtained the ISO file, you can use it like any other ISO file: create a bootable USB stick, use Qemu to make a virtual machine (`qemu-system-x86_64 -cdrom <iso>` to launch), etc.

Currently, B-DOS does not do much things. You can press keys that are recognized, the interface resembles a CLI and the command parsing is on its way.

<p align="right">(<a href="#readme-top">Up</a>)</p>

### Known Issues
<a name="known-issues"></a>

Various problems and bugs may arise during development. If no obvious solution is found, they are listed here. If you come across another bug not listed, please report it using the Issues tab.
- None

<p align="right">(<a href="#readme-top">Up</a>)</p>

[c-url]: https://fr.wikipedia.org/wiki/C_(langage)
[asm-url]: https://en.wikipedia.org/wiki/Assembly_language
[grub-url]: https://www.gnu.org/software/grub/
[docker-url]: https://www.docker.com
