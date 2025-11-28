# 🎶 HarmonyHub - Playlist Manager 🎶

**HarmonyHub** is a student project that implements a music playlist manager using two core data structures:

- A **Binary Search Tree (BST)** to store and manage the main music library (fast lookup by title/artist).
- A **Circular Doubly Linked List (CDLL)** to represent the active playlist (efficient bidirectional navigation and looping).

This README focuses on the real implementation details of the repository (BST + CDLL), key features, usage and how to build/run the program.

---

## 🌟 Key Features

- **Library (BST)**: Store songs in a Binary Search Tree allowing quick search by title and artist, and efficient insertion/removal in the library.
- **Playlist (CDLL)**: The active playlist is implemented as a Circular Doubly Linked List enabling constant-time insertions/removals at current position and natural looping behavior.
- **Add / Remove / Edit Songs**: Create songs with full metadata (title, artist, genre, album, year, duration), remove by title, and edit song details.
- **Favorites**: Mark/unmark songs as favorites and display favorites separately.
- **Shuffle & Sort**: Shuffle the playlist or sort songs by attributes (title, artist, year, duration, etc.).
- **Statistics**: Show total number of songs and average duration.
- **File Operations**: Save playlists to a file and load playlists from files.

---

## 🔀 Navigation

- **Next / Previous**: Move forward or backward through the playlist using CDLL bidirectional links.
- **Current Song**: Easily display or operate on the current song node.
- **Looping**: Because the list is circular, moving next from the last song returns to the first.

---

## 📊 Analytics & Organization

- **Sort Options**: Sort playlist entries by title, artist, genre, album, year, or duration.
- **Statistics**: `totalSongs()` and `averageDuration()` functions provide quick playlist metrics.
- **Search**: Use the BST-backed library to search songs by title or list songs by artist.

---

## 💾 File Operations

- **Save**: Persist a playlist to a CSV-like text file (title,artist,genre,album,year,duration,favorite).
- **Load**: Load saved playlists; songs are inserted into the BST library first and pointers are added to the playlist.

---

## ⚙️ Implementation (Short)

- **Binary Search Tree (BST)**
  - Stores unique `Song` objects (title used as primary key for ordering/searching).
  - Responsible for memory ownership of `Song` objects; playlists keep pointers to BST-owned `Song`s.

- **Circular Doubly Linked List (CDLL)**
  - Each `Song` pointer in the playlist is wrapped in a node with `next` and `prev` pointers forming a circular list.
  - Supports `nextSong()`, `previousSong()`, `addSong()`, `removeSong()` and traversal operations efficiently.

### Why this design?

1. BST provides efficient searches and a single source of truth for song data (no duplicated mutable copies).
2. CDLL models the natural behaviour of a playlist (bi-directional navigation and looping) with low overhead for insertion/removal.

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (GCC/MinGW or MSVC). The code uses standard C++ features; compiling with `-std=c++17` is recommended.

### Build (Windows PowerShell example)

1. Open PowerShell and navigate to the project folder:
   ```powershell
   cd 'C:\Users\Pc\Documents\GitHub\PlayList_Manager'
   ```

2. Compile with g++ (requires GCC/MinGW installed):
   ```powershell
   g++ -std=c++17 -O2 -Wall main.cpp -o PlayList_Manager.exe
   ```

3. Run the executable:
   ```powershell
   .\PlayList_Manager.exe
   ```

### Build (Alternative: MSVC/Visual Studio)

If you have Visual Studio installed, use the MSVC compiler:

```powershell
cl /std:latest /O2 main.cpp /Fe:PlayList_Manager.exe
.\PlayList_Manager.exe
```

### Running the Program

Once built, the executable `PlayList_Manager.exe` will launch the HarmonyHub interactive menu where you can:

- Add songs to the library
- Create and manage playlists
- Search, sort, and shuffle songs
- Mark favorites and view statistics
- Save and load playlists from files

---

## Acknowledgments

This project uses source code from, or is heavily inspired by, the following open-source repository:

*   **Project Name:** HarmonyHub - Playlist Manager
*   **Author:** Basem Mohamed
