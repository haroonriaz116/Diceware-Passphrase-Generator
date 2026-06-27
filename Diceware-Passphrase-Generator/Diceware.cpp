#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

// Function to load a diceware file into a map
map<int, string> loadDicewareFile(const string &filename) {
  map<int, string> myData;
  ifstream myFile(filename);
  if (!myFile.is_open()) {
    cerr << "Could not open the file " << filename << endl;
    exit(EXIT_FAILURE);
  }

  int roll;
  string word;

  while (myFile >> roll >> word) {
    myData[roll] = word;
  }

  myFile.close();
  return myData;
}

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));

  bool playAgain = false;
  string response;
  string choice;
  int curIntRoll;
  int numSets;
  int totalCharacters;

  do {
    // Array of filenames for the different languages
    string filenames[] = {"EnglishDiceware.txt", "SwedishDiceware.txt",
                          "DanishDiceware.txt"};

    // Map to hold the loaded diceware data
    map<int, string> words;
    string language;

    // Display welcome message and instructions
    cout << "\033[1;36mWelcome to Diceware Passphrase Generator!\033[0m"
         << endl;
    cout << "This program will generate a random passphrase using the Diceware "
            "method."
         << endl;
    cout << "Input your language for your word list:" << endl;
    cout << "English" << endl;
    cout << "Swedish" << endl;
    cout << "Danish" << endl;
    cout << "Type \033[31mHELP\033[0m for further instructions" << endl;

    while (true) {
      // Read in the user's language choice
      cin >> choice;

      // Check the user's choice and load the appropriate diceware file from
      // array
      if (choice == "ENGLISH" || choice == "English" || choice == "english") {
        words = loadDicewareFile(filenames[0]);
        language = "English";
        break;
      } else if (choice == "SWEDISH" || choice == "Swedish" ||
                 choice == "swedish") {
        words = loadDicewareFile(filenames[1]);
        break;
      } else if (choice == "DANISH" || choice == "Danish" ||
                 choice == "danish") {
        words = loadDicewareFile(filenames[2]);
        break;
      }
      // Check if user input is help to display instructions
      else if (choice == "HELP" || choice == "Help" || choice == "help") {
        cout << "The Diceware method generates secure passphrases by rolling "
                "dice to select words from a list. Here's how to use this "
                "program:"
             << endl;
        cout << "1. Choose a language for your word list." << endl;
        cout << "2. Enter the number of sets of five rolls you would like."
             << endl;
        cout << "3. The program will generate a random number for each set of "
                "rolls and use it to look up a word from the word list."
             << endl;
        cout << "4. Your passphrase will be displayed on the screen." << endl;
        cout << "5. If you want to generate another passphrase, enter "
                "\033[32mY\033[0m. Otherwise, enter \033[31mN\033[0m to exit "
                "the program."
             << endl;
        sleep(3);
        cout << "\033[2J\033[1;1H";
        cout << "Input your language for your word list:" << endl;
        cout << "English" << endl;
        cout << "Swedish" << endl;
        cout << "Danish" << endl;
      }
      // Detect invalid input
      else {
        cout << "\033[31mInvalid input! Please enter help for "
                "instructions.\033[0m"
             << endl;
      }
    }

    do {
      cout << endl;
      // Prompt the user to enter the number of phrases they would like
      cout << "How many phrases would you like? (6 minimum): ";
      cin >> numSets;
      if (cin.fail() || numSets < 6) {
        cout << "\033[31mInvalid input! Please enter a number greater than "
                "5\033[0m"
             << endl;
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Discard invalid input
      }
    } while (numSets < 6 || cin.fail());

    // Vector to hold dice rolls
    vector<int> rolls;
    for (int i = 0; i < numSets; i++) {
      cout << "Set " << i + 1 << ":";
      curIntRoll = 0;
      for (int j = 0; j < 5; j++) {
        // Generate dice rolls for each phrase
        int roll = rand() % 6 + 1;
        curIntRoll = curIntRoll * 10 + roll;
        // Output rolls
        cout << " " << roll << " ";
      }
      rolls.push_back(curIntRoll);
      cout << endl;
    }

    totalCharacters = 0;
    cout << "Your passphrase is: ";
    vector<string> passphraseWords;
    for (auto roll : rolls) {
      string word = words[roll];
      if (!word.empty()) {
        passphraseWords.push_back(word);
        // Count the number of characters in the passphrase
        totalCharacters += word.length();
        // Output passphrase
        cout << word << " ";
      }
    }
    cout << endl;

    // Display passphrase strength depending on the number of characters
    cout << "Password Entropy: \033[31mInstant\033[0m";
    cout << endl;

    // Ask the user if they want to strengthen the passphrase
    cout << "Would you like to strengthen your passphrase? "
            "(\033[32mY\033[0m/\033[31mN\033[0m) ";
    cin >> response;

    // Check for invalid input
    while (response != "Y" && response != "y" && response != "N" &&
           response != "n") {
      cout << "\033[31mInvalid input!\033[0m" << endl;
      cout << "Would you like to strengthen your passphrase? "
              "(\033[32mY\033[0m/\033[31mN\033[0m) ";
      cin >> response;
    }

    bool strengthenPassphrase = false;
    // Set the strengthenPassphrase variable based on the user's response
    if (response == "Y" || response == "y") {
      strengthenPassphrase = true;
    }

    if (strengthenPassphrase) {
      // Modify the passphrase to include capital letters and special characters
      for (auto &word : passphraseWords) {
        int index = rand() % word.length();
        // Include capital letters in the passphrase
        word[index] = toupper(word[index]);
        int specialCharIndex = rand() % word.length();
        // Include special characters in the passphrase
        char specialChar = "!@#$%^&*"[rand() % 8];
        word.insert(specialCharIndex, 1, specialChar);
        int numIndex = rand() % word.length();
        // Include numbers in the passphrase
        int num = rand() % 10;
        word.insert(numIndex, 1, num + '0');
      }

      // Output the strengthened passphrase
      cout << "Your strengthened passphrase is: ";
      totalCharacters = 0;
      for (const auto &word : passphraseWords) {
        cout << word << " ";
        // Count the number of characters in the passphrase
        totalCharacters += word.length();
      }
      cout << endl;

      // Display passphrase strength depending on the number of characters
      if (language == "English") {
        if (totalCharacters <= 50) {
          cout << "Password Entropy: \033[31m1 Day\033[0m";
        } else if (totalCharacters <= 52) {
          cout << "Password Entropy: \033[31m1 Week\033[0m";
        } else if (totalCharacters <= 54) {
          cout << "Password Entropy: \033[1;33m1 Month\033[0m";
        } else if (totalCharacters <= 56) {
          cout << "Password Entropy: \033[1;33m1 Year\033[0m";
        } else if (totalCharacters <= 58) {
          cout << "Password Entropy: \033[32m5 Years\033[0m";
        } else {
          cout << "Password Entropy: \033[32m8 Years\033[0m";
        }
      } else {
        if (totalCharacters <= 33) {
          cout << "Password Entropy: \033[31m1 Day\033[0m";
        } else if (totalCharacters <= 36) {
          cout << "Password Entropy: \033[31m1 Week\033[0m";
        } else if (totalCharacters <= 38) {
          cout << "Password Entropy: \033[1;33m1 Month\033[0m";
        } else if (totalCharacters <= 40) {
          cout << "Password Entropy: \033[1;33m1 Year\033[0m";
        } else if (totalCharacters <= 43) {
          cout << "Password Entropy: \033[32m5 Years\033[0m";
        } else {
          cout << "Password Entropy: \033[32m8 Years\033[0m";
        }
      }
      cout << endl;
    }

    // Ask the user if they want to generate another passphrase
    cout << "Would you like to generate another passphrase? "
            "(\033[32mY\033[0m/\033[31mN\033[0m) ";
    cin >> response;

    // Check for invalid input
    while (response != "Y" && response != "y" && response != "N" &&
           response != "n") {
      cout << "\033[31mInvalid input!\033[0m" << endl;
      cout << "Would you like to generate another passphrase? "
              "(\033[32mY\033[0m/\033[31mN\033[0m) ";
      cin >> response;
    }

    // Check for response
    if (response == "Y" || response == "y") {
      playAgain = true;
    } else {
      playAgain = false;
      cout << "\033[1;33mGoodbye!\033[0m" << endl;
    }

  } while (playAgain);

  return 0;
}