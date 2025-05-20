# 📚 Advanced‑C Mini Project

A tiny, menu‑driven console program that demonstrates several classic C concepts in one place: dynamic string handling, file I/O, character statistics, and a progressive Caesar‑style decoder.

---

## ✨ Features

| ID    | Exercise                            | What it Shows                                                                                                                                                                      |
| ----- | ----------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **1** | **Word Splitter**                   | Reads a sentence, then prints every word that begins with a user‑chosen letter (case insensitive). Demonstrates dynamic allocation & string scanning without `strtok()`.           |
| **2** | **File Creator + Letter Frequency** | Captures arbitrary keyboard input into `input.txt`, then reports the most common letter inside that file. Highlights low‑level file I/O (`fgetc`, `fputc`) and frequency analysis. |
| **3** | **Progressive Decoder**             | Decodes an encrypted message by subtracting an increasing shift from each character, resetting after every space. Shows in‑place string manipulation & simple ciphers.             |

---

## 🚀 Build & Run (Visual Studio 2022)

1. **Clone / copy** the source files into a new VS 2022 *Console Application* project.
2. Make sure the compile flag **`/D _CRT_SECURE_NO_WARNINGS`** is set (already handled via `#define`).
3. *Build → Run* (`Ctrl + F5`). You’ll be prompted to choose which exercise to execute.

> **Tip:** To loop through the menu automatically, enter any non‑zero number when asked *"Run menu once or cyclically?"*.

---

## 🏗️ File Structure

```
│  main.c          ← single‑file source (contains everything)
│  README.md       ← this file
└─ input.txt       ← created on‑the‑fly by Exercise 2 (if it doesn’t exist)
```

---

## 🔍 Key Functions

| Function            | Purpose                                                                       |
| ------------------- | ----------------------------------------------------------------------------- |
| `split()`           | Two‑pass algorithm that counts & extracts words starting with a given letter. |
| `createFile()`      | Saves raw stdin characters into a file until `EOF` (Ctrl+Z/Ctrl+D).           |
| `commonestLetter()` | Scans a file and returns the most frequent alphabetic character.              |
| `decode()`          | Progressive Caesar shift decryption in‑place.                                 |

---

## 📝 License

Feel free to use or modify this mini project for study or teaching. Attribution is appreciated but not required. Have fun hacking C! ✌️
