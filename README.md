
# 🎮 Quick Wordle Game (C++)

A simple **console-based Wordle clone** built in C++ as a quick side project. The game selects a random 5-letter word from a word list and lets the player guess it within a limited number of tries.

---

## 📝 About

This project was created to experiment with:

* Basic C++ features
* File I/O
* Random number generation
* Console cursor manipulation
* Simple game loop logic

It also features a basic colored keyboard and board rendered in the Windows console.

---

## ⚙️ How It Works

* Loads valid Wordle words from `valid-wordle-words.txt`.
* Selects one word at random using a **Mersenne Twister** RNG.
* You get **7 attempts** to guess the word.
* After each guess, feedback is provided using colored letters:

  * 🟩 **Green**: Correct letter in the correct spot
  * 🟨 **Yellow**: Correct letter in the wrong spot
  * 🟥 **Red**: Letter not in the word
* Invalid or repeated words are rejected with feedback.

The game also includes a simple on-screen keyboard that updates colors as you play.

---

## ▶️ Running the Game

This project is a Windows console application. Use **Visual Studio** or **Visual Studio Code** (with a working C++ build setup).

### Setup

1. Download or clone this repository.
   * I use the list from these repos and combined them for easier and matching words: [gist](https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93) / [gist](https://github.com/first20hours/google-10000-english).
2. If using your own word list, rename these 2 files or update the filename in the code:

   ```cpp
   inallwords.open("valid-wordle-words.txt");
   ineasy.open("finishedlist.txt");
   ```

### Build and Run

* Open the project in your IDE.
* Build and run.
* The game will launch in the console.

---

## 🗂 Project Structure

```
Wordle.h				 # Contains all game classes, function names and logic
Wordle.cpp               # Contains all game logic
valid-wordle-words.txt   # List of valid 5-letter words
finishedlist.txt         # A second list used in the game logic
```

---

## 🧠 Notes

* Word validation uses a basic lookup from a preloaded list.
* The on-screen keyboard and word grid use **Windows console colors** (no external libraries).
* Mouse input was considered but not implemented – interaction is via standard keyboard input.
* This is a **learning/demo project**, not a full production game.

---

## ✅ Features

* Fully functional Wordle-style gameplay
* Console color feedback (Green, Yellow, Red)
* Reusable game logic and clean structure
* Keyboard rendering with per-letter color updates
