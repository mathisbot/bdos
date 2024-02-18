# Description: Dockerfile for building the environment for the OS

# This image is an x86_64-elf-gcc toolchain
FROM randomdude/gcc-cross-x86_64-elf

# Install the necessary packages
RUN apt-get update 
RUN apt-get upgrade -y
# Compiler
RUN apt-get install -y nasm
# Bootloader
RUN apt-get install -y grub-pc-bin
RUN apt-get install -y grub-common
# ISO
RUN apt-get install -y xorriso

VOLUME /root/env
WORKDIR /root/env
