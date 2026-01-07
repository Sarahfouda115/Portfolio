- Doubly Linked List for Songs (O(1) insertion/deletion at ends)
- Doubly Linked List for Playlists
- Efficient traversal in both directions
```

**Key Classes:**
- `Song` - Encapsulates song metadata and statistics
- `SongNode` - Node for doubly linked list
- `Playlist` - Manages collection of songs
- `PlaylistNode` - Node for playlist linked list
- `MusicPlayer` - Main controller class

**Advanced Concepts:**
- Dynamic memory management
- Object-oriented design principles
- Error handling and input validation
- Windows API integration for audio playback
- File I/O with custom serialization format
- Real-time keyboard input handling (_kbhit, _getch)

### **🎮 How It Works:**

1. **Playlist Creation:** Users create themed playlists (e.g., "Sheikh Al-Minshawi")
2. **Song Management:** Add songs with file paths to playlists
3. **Interactive Playback:** Enter playback mode with keyboard controls
4. **Auto-Navigation:** Automatically plays next song when current finishes
5. **Persistent Storage:** Save/load playlists for future sessions

### **📊 Code Statistics:**
- **Lines of Code:** 1000+
- **Classes:** 5 main classes
- **Functions:** 30+ member functions
- **File Format:** Custom text-based serialization

### **🚀 Skills Demonstrated:**
- ✅ Advanced C++ programming
- ✅ Data structures implementation (Linked Lists)
- ✅ Object-oriented design and architecture
- ✅ Windows API integration
- ✅ File handling and persistence
- ✅ Memory management (pointers, dynamic allocation)
- ✅ Real-time user interaction
- ✅ Error handling and validation
- ✅ Console UI design

### **🎨 Sample Output:**
```
+------------------------------------------------------------+
|               PROFESSIONAL QURAN PLAYER                    |
+------------------------------------------------------------+
  Songs in [Sheikh Al-Minshawi]:
  --------------------------------------------------
  > 1. Surah Yusuf - Sheikh Menshawy [Played: 5x]
    2. Surah Al-Kahf - Sheikh Menshawy [Played: 3x]
  --------------------------------------------------

♪ NOW PLAYING
  Title: Surah Yusuf
  Artist: Sheikh Menshawy
  Playlist: Sheikh Al-Minshawi