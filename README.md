# Printf partial rewrite: _printf

## Table of content
FIXME

## Overview

_printf is a command allowing the display of dynamically aggregated informations  
  by replacing parts of a provided string with data from other sources.

### Summary
This project aims at demonstrating how to create a simple function
  to display ("print on terminal") different kind of informations
  in various ways, which can be summarized as "isolated characters",
  "full sentences" and "integer numbers displayed in different variants".  
Please note that this is a simplified version with a limited feature set.  
Refer to the [How to use](#how-to-use) section for more details.

### Copyright
This program has been developed by...
* Erwan Barat
* Laurent Lacôte

It is distributed under terms of the GPL v3.0, confer [LICENSE](LICENSE.md) file for details.

## How to run
### Prerequisites
You must have the packages/tools related to C
  installed on your system, as well as a "compiler"
  (program used to "prepare" this tool for your machine).
In case that helps here are online resources to install
  those tools depending on your operating system
  * Windows: https://learn.microsoft.com/en-us/cpp/build/walkthrough-compile-a-c-program-on-the-command-line?view=msvc-170
     and https://nullprogram.com/blog/2016/06/13/
  * Mac: https://www.cs.auckland.ac.nz/~paul/C/Mac/
  * Linux (deb package system): https://jvns.ca/blog/2025/06/10/how-to-compile-a-c-program/

### 1. Downloading
If you have git and are comfortable with command line,
  you can simply open one and go to the directory in which you want calculator to be.
  Then run (without the quotes) "git clone https://github.com/llacote-holberton/holbertonschool-printf.git"
Otherwise you can simply download a zip containing all projects file
  by following [this url](https://github.com/llacote-holberton/holbertonschool-printf/archive/refs/heads/main.zip)
  then unfolding it where you want on your computer.

### 2. Compiling
Open the terminal, go inside the project directory then inside its "FIXME GIVE PROPER NAME" subfolder.
Then type the following command (without quotes if you're reading this as raw text).
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o custom_partial_printf_demo.out`  

**NOTE**: per express requirement from client, the "main" function which is normally required for any C program to run
  is *NOT* provided officially.  
So you will need to write your own source code implementing the "main" function and add it in the same directory.

With that said, if you just want a demonstration of its output, we provide a dedicated "test main" you can use at leisure.
Just add it to the list of files to include in compilation like so.
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c tests/test_main.c -o custom_partial_printf_demo.out`

### 3. Starting program
Open a terminal place yourself in the directory in which you have downloaded/extracted the project then compiled an executable,  
and just type ./<executable-name>  (for example for the "demo executable" it would be `./custom_partial_printf_demo.out`).

## How to use

### Usage overview
To use _printf simply call it while respecting its required syntax.
```
  _printf( format , ...);
             |        |
             |        +--> variadic list of additional data to format.
             +--> "instruction chain" (plain text and special characters triggering a replacement).
```

Format argument is mandatory (although it can technically be an empty string).
Each additional argument must be separated by a comma (',').

The "format" string can be of any desired length.
By default, the characters it contains will be outputted as is on the standard output (terminal screen).
However, each time you enter a "conversion delimiter" character ('%') paired with a supported conversion identifier,
  program will try and use the *matching* argument in the list you provide after the first.
  
For example... Let's say we print a oneline about how much money a user possesses.
```
    _printf("Hello %s, current credit: %d dollars.\n", "Alice", 30);
                   |                    |                |       |
                   |                    |                |       +--> argument 2 (int)
                   |                    |                +----------> argument 1 (string)
                   |                    |
                   |                    +--> %d = expects second variadic argument to be integer.
                   +-----------------------> %s = expects first additional argument to be string.
```
As you can see in this example, we have two replacements.
'%' (conversion delimiter) immediately followed by 's' (conversion identifier) create a "conversion command"
    replacing those two characters with the whole content of a string provided through another variable.
'%' (conversion delimiter) immediately followed by 'd' (conversion identifier) create a "conversion command"
    replacing those two characters with the integer number contained in another variable.

The output displayed will be as follows ((\n meaning "go to a new line")).
```
Hello Alice, current credit: 30 dollars.

```
For more detailed examples, confer the dedicated section [Examples of use](#examples-of-use).

### Features
This program only supports the following conversion commands.

| Conversion command | Description of what command does.                                                         | Required type for matching argument in variadic list |
|--------------------|-------------------------------------------------------------------------------------------|------------------------------------------------------|
| '%c'               | Replaces with a single character                                                          | char                                                 |
| '%s'               | Replaces with a whole string                                                              | char*                                                |
| '%d'               | Replaces with an integer "as provided"                                                    | int                                                  |
| '%i'               | Replaces with an integer "as provided"                                                    | int                                                  |
| '%u'               | Replaces with an unsigned integer (>=0) "as provided".                                    | unsigned int                                         |
| '%o'               | Replaces with an octal representation  of a provided unsigned integer.                    | unsigned int                                         |
| '%x'               | Replaces with a hexadecimal representation (in lowercase) of a provided unsigned integer. | unsigned int                                         |
| '%X'               | Replaces with a hexadecimal representation (in uppercase) of a provided unsigned integer. | unsigned int                                         |
|                    |                                                                                           |                                                      |

IMPORTANT: function has a two-branche return: if the whole writing was successful, it will return the total number of characters printed.
If at any moment writing fails for any reason, function immediately stops parsing format and will return -1.

### Accessible help
You can consult the associated help by typing the following command while at the root directory of this project.
`man 3 _printf`.

In case you would prefer adding it to your manpages database, you can type in these commands
  (you will need root privileges on your system if you plan on adding for all users by copying to /usr/share/man/man3/).
```
mkdir -p ~/.local/share/man/man3/        # OPTIONAL: in case it doesn't exist already.
cp ./_printf.3 ~/.local/share/man/man3/  # Copy to the right section.
mandb                                    # Force the reconstruction of manpages index
man 3 _printf                            # Will now work wherever you are.
```

### Important rules and limitations
1. **Only the aforementioned conversion commands are supported.** Pairing % with any other character will result in both being printed literally (ex %z).
   This is a difference with official printf which may sometimes try to interpret them and end up with undefined behaviour.
2. **When format contains valid conversion commands, arguments which follow MUST match the conversion specifiers in both order and expected type.**
   Program cannot guarantee behaviour if this requirement is not fulfilled.
3. This program only supports the aforementioned features. If you need more formatters or advanced formatting options such as padding, limiting number of decimals etc please consider using the official printf from C standard library instead.


### Examples of use

#### Valid examples
| Use case                     | Source code                               | Output                 | N° of printed chars |
|------------------------------|-------------------------------------------|------------------------|---------------------|
| %c — Single character        | _printf("Character: %c\n", 'A');          | Character: A           | 13                  |
| %s — String                  | _printf("String: %s\n", "Hello, World!"); | String: Hello, World!  | 21                  |
| %d — Signed decimal integer  | _printf("Degrees: %d\n", -42);            | Degrees: -42           | 13                  |
| %i — Signed decimal integer  | _printf("Score: %i\n", 1337);             | Score: 1337            | 12                  |
| %u — Unsigned decimal integer| _printf("Population: %u\n", 4294967295u); | Population: 4294967295 | 23                  |
| %o — Octal representation    | _printf("Permissions: %o\n", 493u);       | Permissions: 755       | 17                  |
| %x — Hexadecimal lowercase   | _printf("Color: %x\n", 255u);             | Color: ff              | 10                  |
| %X — Hexadecimal uppercase   | _printf("Color: %X\n", 255u);             | Color: FF              | 10                  |

#### Failing examples
Examples of faulty call ending in undefined behaviour.
```_printf("Hello %s, current credit: %d dollars.\n", 30, "Bob");```
  => Argument list provides variables of the right type, but the order mismatches the one of conversion commands.
```_printf("Hello %s, current credit: %d dollars.\n", "Bob");```
  => One argument is missing.
```_printf("Hello %s, current credit: %u dollars.\n", 'Z', -666);```
  => Good number of arguments, good order but second argument is signed int and %u expects an unsigned one.

## Technical information

### General architecture
FIXME describing what each file contains.
FIXME put the flowchart diagram.

### Testing
FIXME add listing of tests made with Valgrind
  and architecture on memory allocation and average use.
