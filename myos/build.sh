#!/bin/bash
# Автосборка Notepad OS
set -e

echo "=== Установка зависимостей ==="
sudo apt update -y
sudo apt install -y nasm gcc ld grub-pc-bin grub-common xorriso qemu-system-x86 make gcc-multilib

echo "=== Сборка ядра ==="
make clean
make

echo "=== Сборка ISO ==="
make iso

echo "=== Готово! Запуск в QEMU ==="
make run
