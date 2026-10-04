# 🔍 Inverted Search Index Database

A command-line **Inverted Search** application implemented in C that builds an index of words from multiple text files and lets you search which files contain a word and how many times it occurs.

The project uses a **hash table of linked lists** to store words, with a second linked list per word to track the files and occurrence counts. The index can be saved to a database file and reloaded later for searching.

<p>
  <a href="https://github.com/JITH1"><img src="https://img.shields.io/badge/-GitHub-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub"></a>
  <a href="https://www.linkedin.com/in/jithinjith"><img src="https://img.shields.io/badge/-LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn"></a>
</p>

---

## 🚀 Features

- 📄 Indexes words from multiple `.txt` files
- 🧮 Stores the file count and per-file word count for every word
- 🗂️ Hash table with 27 buckets (`a`–`z` and others)
- 🔗 Separate chaining using linked lists
- 🔠 Case-insensitive indexing (all words stored in lowercase)
- 📊 Formatted display of the complete database
- 💾 Save the database to a file
- 🔎 Load a saved database and search for any word
- ➕ Update the database with a new file
- 🧹 Clear the database and free all memory
- ✅ Command-line argument and file name validation
- 🚫 Detects invalid, missing, and empty files
- 🎨 Colored terminal output
- ⚙️ Makefile support for compilation

---

## 🛠️ Technologies & Core Concepts

### Language
- C

### Core Concepts
- Structures
- Pointers
- Hash Tables
- Singly Linked Lists
- Separate Chaining
- Dynamic Memory Allocation
- File Handling
- Command-Line Arguments
- String Manipulation
- Modular Programming
- Memory Management
- Input Validation
- Enumerations and Macros
- Makefile

### Development Tools
- GCC
- GNU Make
- Linux

---

## 🧱 Data Structure

The project uses a **three-level data structure**: a hash table whose buckets hold linked lists of words, where each word holds its own linked list of files.

### 1. File List Node (`F_node`)

Stores the names of the input files given on the command line.

```c
typedef struct file
{
    char f_name[20];
    struct file *link;
} F_node;
```

### 2. Main Node (`M_node`)

Stores one unique word.

```c
typedef struct main
{
    char word[25];
    int file_count;
    S_node *sub_link;
    struct main *main_link;
} M_node;
```

| Field | Description |
|-------|-------------|
| `word` | The indexed word (lowercase) |
| `file_count` | Number of files containing the word |
| `sub_link` | Head of the list of files for this word |
| `main_link` | Next word in the same hash bucket |

### 3. Sub Node (`S_node`)

Stores one file entry for a word.

```c
typedef struct sub
{
    int word_count;
    char file_name[20];
    struct sub *sub_link;
} S_node;
```

| Field | Description |
|-------|-------------|
| `word_count` | Number of times the word occurs in this file |
| `file_name` | Name of the file |
| `sub_link` | Next file containing the same word |

### Hash Table

```c
M_node *HT[27];
```

| Index | Holds words starting with |
|-------|---------------------------|
| 0 – 25 | `a` – `z` |
| 26 | Any other character |

Index calculation:

```c
int get_index(char ch)
{
    if (isalpha(ch))
        return tolower(ch) - 'a';
    return 26;
}
```

### Structure Diagram

```
HT[27]
┌─────┐
│  0  │──► ┌─────────┐    ┌─────────┐    ┌──────────┐
│ (a) │    │  "and"  │───►│  "all"  │───►│"approved"│───► NULL
├─────┤    │ count=3 │    └─────────┘    └──────────┘
│  1  │    └────┬────┘
│ (b) │         │ sub_link
├─────┤         ▼
│  2  │    ┌──────────────┐   ┌──────────────┐   ┌──────────────┐
│ (c) │    │ file1.txt : 3│──►│ file2.txt : 3│──►│ file3.txt : 2│──► NULL
├─────┤    └──────────────┘   └──────────────┘   └──────────────┘
│ ... │
├─────┤
│ 26  │
│other│
└─────┘
```

- Words are stored in the bucket matching their first letter.
- Words that share a first letter are chained through `main_link`.
- Each word keeps its own list of files through `sub_link`.

### Example: Word `and`

Across `file1.txt`, `file2.txt` and `file3.txt`:

| Word | File Count | File | Word Count |
|------|-----------:|------|-----------:|
| and | 3 | file1.txt | 3 |
| | | file2.txt | 3 |
| | | file3.txt | 2 |

---

## 📂 Project Structure

```
Inverted-Search-Index-Database-in-C/
│
├── main.c
├── inverted.h
├── function.h
├── function.c
├── Database.c
├── Display.c
├── Save.c
├── Search.c
├── Update.c
├── Clear.c
├── Makefile
├── file1.txt
├── file2.txt
├── file3.txt
├── Database.txt
└── README.md
```

### File Description

| File | Description |
|------|-------------|
| `main.c` | Validates arguments and runs the menu-driven program |
| `inverted.h` | Contains the `F_node`, `M_node` and `S_node` structures |
| `function.h` | Contains function declarations, `FLAG` enum and color macros |
| `function.c` | Validates command-line files and builds the file list |
| `Database.c` | Creates the database and stores words in the hash table |
| `Display.c` | Displays the database in a formatted table |
| `Save.c` | Saves the database to a file and validates file names |
| `Search.c` | Loads a saved database and searches for a word |
| `Update.c` | Adds a new file to the existing database |
| `Clear.c` | Frees all dynamically allocated memory |
| `Makefile` | Automates project compilation |
| `file1.txt` – `file3.txt` | Sample input files |
| `Database.txt` | Sample saved database |
| `README.md` | Project documentation |

---


<img width="4592" height="6624" alt="diagram (2)" src="https://github.com/user-attachments/assets/f47da890-574a-4583-a20f-a0fc55ccfc96" />


---

## 📋 Supported Operations

| Option | Operation | Description |
|:------:|-----------|-------------|
| 1 | Create Database | Builds the index from the input files |
| 2 | Display Database | Prints all words with file and word counts |
| 3 | Save Database | Writes the index to a `.txt` file |
| 4 | Search | Loads a saved database and searches a word |
| 5 | Update Database | Adds a new file to the index |
| 6 | Clear Database | Frees the index and the file list |
| 7 | Exit | Quits the program |

---

## 💻 Usage

The program accepts one or more `.txt` files through command-line arguments.

### Syntax

```bash
./inverted.o <file1.txt> <file2.txt> ... <fileN.txt>
```

### Example

```bash
./inverted.o file1.txt file2.txt file3.txt
```

### Menu

```
Select your choice among following operations:
1. Create Database
2. Display Database
3. Save Database
4. Search
5. Update Database
6. Clear Database
7. Exit
```

### Typical Flow

1. Choose `1` to create the database
2. Choose `2` to display it
3. Choose `3` and enter a file name (for example `Database.txt`) to save it
4. Choose `4`, enter the database file name, then the word to search
5. Choose `5` to add another `.txt` file
6. Choose `6` to clear the database
7. Choose `7` to exit

---

## 📋 Example

### Display Database

```
INDEX    WORD                      FILE_COUNT   FILENAME             WORD_COUNT
--------------------------------------------------------------------------------
0        and                       3            file1.txt            3
                                                file2.txt            3
                                                file3.txt            2
--------------------------------------------------------------------------------
```

### Search Database

```
The Database.txt database loaded successfully...!

Enter the word to search :
and

The word found...!

Word : and        ->  File Count : 3
--------------------------------------------------------
File : file1.txt  | Word Count : 3
File : file2.txt  | Word Count : 3
File : file3.txt  | Word Count : 2
--------------------------------------------------------
```

---

## 💾 Database File Format

Each word is saved as one line:

```
# <index> ; <word> ; <file_count> ; <file_1> ; <count_1> ; <file_2> ; <count_2> ; #
```

Example:

```
# 0 ; and ; 3 ; file1.txt ; 3 ; file2.txt ; 3 ; file3.txt ; 2 ; #
```

---

## ✅ Input Validation

The program validates that every file name:

- Ends with `.txt`
- Does not start with `.`
- Does not start with a digit
- Does not contain spaces
- Exists and can be opened
- Is not empty (input files and database files)

Invalid inputs are handled with appropriate error messages.

---

## 🔨 Compilation

### Using Makefile

Build the project using:

```bash
make
```

Clean the generated build files using:

```bash
make clean
```

### Manual Compilation

```bash
gcc main.c function.c Database.c Display.c Save.c Search.c Update.c Clear.c -o inverted.o
```

For compilation with warnings enabled:

```bash
gcc -Wall -Wextra main.c function.c Database.c Display.c Save.c Search.c Update.c Clear.c -o inverted.o
```

---

## ▶️ Running the Program

After compilation, run:

```bash
./inverted.o <file1.txt> <file2.txt> ...
```

Example:

```bash
./inverted.o file1.txt file2.txt file3.txt
```

---

## 🧠 Learning Outcomes

This project helped strengthen practical understanding of:

- C Programming
- Hash Tables and Separate Chaining
- Linked Lists
- Structures and Pointers
- Dynamic Memory Allocation
- File Handling and Parsing
- Command-Line Arguments
- String Manipulation
- Modular Programming
- Memory Management
- Input Validation
- Makefile and Build Automation

---

## 🎯 Project Objective

The primary objective of this project is to understand how a search engine style **inverted index** works, mapping each word to the documents that contain it so that lookups do not require scanning every file.

The project combines C programming, hash tables, linked lists, file handling and dynamic memory allocation to build a practical command-line search index.

---

## ⚠️ Known Limitations

- Only alphabetic characters form words; digits and symbols act as separators
- File names are limited to 19 characters and words to 24 characters
- Search compares the word exactly as typed, so enter it in lowercase
- Updating with an already indexed file adds its counts again

---

## 🚧 Future Improvements

- [ ] Case-insensitive search
- [ ] Duplicate-file detection during update
- [ ] Stronger hash function and larger table
- [ ] Phrase and multi-word search
- [ ] Dynamic buffers for file and word names
- [ ] Remove a file from the database
- [ ] Add automated test cases

---

## 👨‍💻 About Me

**Jithin P**
Electronics and Communication Engineering Graduate | Embedded Systems & Firmware

I am an Electronics and Communication Engineering graduate with skills in Embedded Systems, Firmware Development, C/C++, Data Structures & Algorithms, and Linux Internals.

I focus on building strong foundations in programming and system-level development, with an emphasis on writing efficient and reliable software.

---

## 💻 Technical Skills

- C Programming
- C++
- Data Structures & Algorithms (DSA)
- Embedded Systems
- Firmware Development
- Linux Internals

---

## 🔗 Connect With Me

<p>
  <a href="https://www.linkedin.com/in/jithinjith"><img src="https://img.shields.io/badge/-LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn"></a>
  <a href="https://github.com/JITH1"><img src="https://img.shields.io/badge/-GitHub-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub"></a>
</p>
