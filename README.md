# Diceware Passphrase Generator

A console-based passphrase generator that follows the Diceware method, rolling simulated dice to build secure, memorable passphrases from large multilingual word lists.

## How it works

* The player first selects a word list language, choosing between English, Swedish, and Danish, each backed by its own diceware text file mapping five-digit dice roll combinations to words.
* The player then specifies how many word sets they want, with a minimum of six, and the program simulates five dice rolls per set to produce a five-digit lookup number for each word.
* Each generated number is used to retrieve a corresponding word from the loaded word list, and the resulting words are joined together into a single passphrase.
* The base passphrase entropy is reported as instant, reflecting how predictable plain dictionary words are, even when chosen randomly.
* The player can choose to strengthen the passphrase, which capitalizes a random letter in each word and inserts a random special character and digit, after which entropy is re-evaluated based on total passphrase length and reported on a scale from one day to eight years.
* Typing HELP at the language prompt reprints a summary of how the Diceware method works before returning to the language selection.
* After each passphrase is generated, the player is asked whether to generate another.

## Tech stack

The program is written in standard C++ and depends only on the C++ standard library, including fstream, map, and vector, with no external libraries, build tools, or frameworks required.

## Project structure

```
diceware/
├── Diceware.cpp
├── EnglishDiceware.txt
├── SwedishDiceware.txt
└── DanishDiceware.txt
```

## Running it locally

Clone the repository and compile the single source file with any standard C++ compiler, making sure all three word list files remain in the same directory as the executable:

```
git clone https://github.com/your-username/diceware.git
cd diceware
g++ -o diceware Diceware.cpp
./diceware
```

## Design notes

Each word list is loaded into a map keyed by its five-digit roll number, so word lookup after rolling is a constant-time operation rather than a linear search. Terminal output relies on ANSI escape codes to color-code prompts and to shade entropy results from red for weak passphrases through yellow to green for stronger ones, giving the player an immediate visual sense of passphrase strength.

## Contact

Haroon Riaz — haroonriaz116@gmail.com
