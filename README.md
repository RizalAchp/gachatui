# Gacha Kelompok

## Prepare

1. for Windows Users

   - you can download the executeable (.exe) on [this link](https://github.com/RizalAchp/gacha_kelompok/releases/download/v1.0.0-release/gacha.exe)
   - or you can build it our self, and you can do what ever you want with the source code
     1. Dwnload the project zip on [this link](https://github.com/RizalAchp/gacha_kelompok/archive/refs/tags/v1.0.0-release.zip) and unzip or clone this project
     2. run the `install.ps1` script. the script's will ensure you have python on your host pc and creating virtual environment for this project
        and prompting you if you wanna build the project or not.
     3. enjoy

2. for Linux / \*Nix system
   - deb package: [this link](https://github.com/RizalAchp/gacha_kelompok/releases/download/v1.0.0-release/gacha-1.0-0_amd64.deb)

## How To Use it?

1. just run the program for (.exe) doubleclick or run on the terminal
2. or run with python intepreter
   ```sh
   python gacha
   ```
3. help args:

   ```sh
   ➜ python gacha --h
   usage: __init__.py [-h, --help, arguments]

   Aplikasi Gacha Golongan C TKK 2020

   positional arguments:
     start                 Menjalankan Program Gacha secara Interaktif Mode

   options:
     -h, --help            show this help message and exit
     -r file, --read file  Membuka dan Membaca isi file csv.
     -s path, --show path  Menampilkan semua file csv pada directori. Type '.' untuk current directori.
     -d file, --delete file
                           Menghapus spesifik csv file.
     -c file1 file2, --copy file1 file2
                           Copy file csv file1 dan file2 Warning: file1 akan di overwrite.
     --rename old_name new_name
                           Mengganti Nama dari file yang di berikan.

   ENJOY~!
   ```
