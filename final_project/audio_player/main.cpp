#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <cstring>
#include <sstream>
#include <limits> // For numeric_limits

#pragma comment(lib, "winmm.lib")

using namespace std;

// ==================== UTILITY FUNCTIONS ====================
//تغيير لون الكتابة في الكونسول.
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void printHeader(string title) {
    system("cls");
    setColor(11); // Cyan
    cout << "\n";
    // Original: ╔════════════════════════════════════════════════════════════╗
    cout << "+------------------------------------------------------------+\n";
    // Original: ║                                                            ║
    cout << "|                                                            |\n";
    // Original: ║         " << setw(42) << left << title << "         ║
    cout << "|         " << setw(42) << left << title << "         |\n";
    // Original: ║                                                            ║
    cout << "|                                                            |\n";
    // Original: ╚════════════════════════════════════════════════════════════╝
    cout << "+------------------------------------------------------------+\n";
    setColor(7); // White
}

void printSuccess(string msg) {
    setColor(10); // Green
    cout << "✓ " << msg << endl;
    setColor(7);
}

void printError(string msg) {
    setColor(12); // Red
    cout << "✗ " << msg << endl;
    setColor(7);
}

void printInfo(string msg) {
    setColor(14); // Yellow
    cout << "ℹ " << msg << endl;
    setColor(7);
}

void printPlaying(string msg) {
    setColor(13); // Magenta
    cout << "♪ " << msg << endl;
    setColor(7);
}

string getCurrentTime() {
    time_t now = time(0);
    tm timeInfo;
    //نسخة آمنة في ويندوز من localtime().
    localtime_s(&timeInfo, &now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return string(buffer);
}





// ==================== SONG CLASS ====================
class Song {
public:
    string title;
    string artist;
    string filePath;
    string duration;
    int playCount;
    string lastPlayed;

    Song(string t, string a, string path) {
        title = t;
        artist = a;
        filePath = path;
        duration = "Unknown";
        playCount = 0;
        lastPlayed = "Never";
    }

    void incrementPlayCount() {
        playCount++;
        lastPlayed = getCurrentTime();
    }

    void display(int num, bool isPlaying = false) {
        if (isPlaying) {
            setColor(13);
            cout << "  > "; // Changed from '►'
        }
        else {
            cout << "    ";
        }

        setColor(11);
        cout << num << ". ";
        setColor(15);
        cout << title;
        setColor(8);
        cout << " - " << artist;

        if (playCount > 0) {
            setColor(10);
            cout << " [Played: " << playCount << "x]";
        }

        setColor(7);
        cout << endl;
    }
};
    



// ==================== SONG NODE ====================
class SongNode {
public:
    Song* data;
    SongNode* next;
    SongNode* prev;

    SongNode(Song* s) {
        data = s;
        next = nullptr;
        prev = nullptr;
    }

    ~SongNode() {
        delete data;
    }
};

// ==================== PLAYLIST CLASS ====================
class Playlist {
public:
    string name;
    string description;
    SongNode* head;
    SongNode* tail;
    SongNode* current;
    int songCount;
    string createdDate;
    int totalPlays;

    Playlist(string n, string desc = "") {
        name = n;
        description = desc;
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        songCount = 0;
        createdDate = getCurrentTime();
        totalPlays = 0;
    }

    ~Playlist() {
        SongNode* temp = head;
        while (temp) {
            SongNode* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    bool addSong(string title, string artist, string path) {
        Song* newSong = new Song(title, artist, path);
        SongNode* newNode = new SongNode(newSong);

        if (!head) {
            head = tail = current = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        songCount++;
        printSuccess("Added: " + title + " by " + artist);
        return true;
    }

    bool removeSong(string title) {
        SongNode* temp = head;

        while (temp) {
            if (temp->data->title == title) {
                if (temp->prev) {
                    temp->prev->next = temp->next;
                }
                else {
                    head = temp->next;
                }

                if (temp->next) {
                    temp->next->prev = temp->prev;
                }
                else {
                    tail = temp->prev;
                }

                if (current == temp) {
                    current = temp->next ? temp->next : head;
                }

                delete temp;
                songCount--;
                printSuccess("Removed: " + title);
                return true;
            }
            temp = temp->next;
        }

        printError("Song not found: " + title);
        return false;
    }

    SongNode* findSong(string title) {
        SongNode* temp = head;
        while (temp) {
            if (temp->data->title == title) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void displaySongs() {
        if (!head) {
            printInfo("Playlist is empty");
            return;
        }

        cout << "\n";
        setColor(14);
        cout << "  Songs in [" << name << "]:\n";
        setColor(7);
        // Original: cout << "  " << string(50, '─') << "\n";
        cout << "  " << string(50, '-') << "\n";

        SongNode* temp = head;
        int num = 1;
        while (temp) {
            temp->data->display(num, temp == current);
            temp = temp->next;
            num++;
        }
        // Original: cout << "  " << string(50, '─') << "\n";
        cout << "  " << string(50, '-') << "\n";
    }

    bool reorder(int from, int to) {
        if (from < 1 || from > songCount || to < 1 || to > songCount || from == to) {
            printError("Invalid positions!");
            return false;
        }

        // Find song to move
        SongNode* songToMove = head;
        for (int i = 1; i < from; i++) {
            songToMove = songToMove->next;
        }

        // Remove from current position
        if (songToMove->prev) {
            songToMove->prev->next = songToMove->next;
        }
        else {
            head = songToMove->next;
        }

        if (songToMove->next) {
            songToMove->next->prev = songToMove->prev;
        }
        else {
            tail = songToMove->prev;
        }

        // Insert at new position
        if (to == 1) {
            songToMove->next = head;
            songToMove->prev = nullptr;
            if (head) head->prev = songToMove;
            head = songToMove;
            if (!tail) tail = songToMove;
        }
        else {
            SongNode* temp = head;
            for (int i = 1; i < to - 1; i++) {
                temp = temp->next;
            }

            songToMove->next = temp->next;
            songToMove->prev = temp;

            if (temp->next) {
                temp->next->prev = songToMove;
            }
            else {
                tail = songToMove;
            }
            temp->next = songToMove;
        }

        printSuccess("Song moved from position " + to_string(from) + " to " + to_string(to));
        return true;
    }

    void getStats() {
        cout << "\n";
        setColor(11);
        // Original: cout << "  ╔═══════════════════════════════════════════╗\n";
        cout << "  +------------------------------------------+\n";
        // Original: cout << "  ║         PLAYLIST STATISTICS               ║\n";
        cout << "  |         PLAYLIST STATISTICS              |\n";
        // Original: cout << "  ╠═══════════════════════════════════════════╣\n";
        cout << "  +------------------------------------------+\n";
        setColor(7);
        // Original: cout << "  ║ Name: " << setw(36) << left << name << "║\n";
        cout << "  | Name: " << setw(36) << left << name << "|\n";
        // Original: cout << "  ║ Songs: " << setw(35) << left << songCount << "║\n";
        cout << "  | Songs: " << setw(35) << left << songCount << "|\n";
        // Original: cout << "  ║ Total Plays: " << setw(29) << left << totalPlays << "║\n";
        cout << "  | Total Plays: " << setw(29) << left << totalPlays << "|\n";
        // Original: cout << "  ║ Created: " << setw(33) << left << createdDate.substr(0, 19) << "║\n";
        cout << "  | Created: " << setw(33) << left << createdDate.substr(0, 19) << "|\n";
        setColor(11);
        // Original: cout << "  ╚═══════════════════════════════════════════╝\n";
        cout << "  +------------------------------------------+\n";
        setColor(7);
    }
};

// ==================== PLAYLIST NODE ====================
class PlaylistNode {
public:
    Playlist* data;
    PlaylistNode* next;
    PlaylistNode* prev;

    PlaylistNode(Playlist* p) {
        data = p;
        next = nullptr;
        prev = nullptr;
    }

    ~PlaylistNode() {
        delete data;
    }
};
 


// ==================== MUSIC PLAYER ====================
class MusicPlayer {

private:

    PlaylistNode* playlistHead;
    PlaylistNode* playlistTail;
    //البلاي الي شغاله ويشتغل منها 
    PlaylistNode* activePlaylist;

    bool isPlaying;
    bool isPaused;
    int totalPlaylists;

    void stopAudio() {
        mciSendStringA("stop SONG", NULL, 0, NULL);
        mciSendStringA("close SONG", NULL, 0, NULL);
        isPlaying = false;
        isPaused = false;
    }

    void togglePause() {
        if (!isPlaying) {
            printError("Nothing is playing!");
            return;
        }

        if (isPaused) {
            mciSendStringA("resume SONG", NULL, 0, NULL);
            isPaused = false;
            printPlaying("Resumed: " + activePlaylist->data->current->data->title);
        }
        else {
            mciSendStringA("pause SONG", NULL, 0, NULL);
            isPaused = true;
            printInfo("Paused: " + activePlaylist->data->current->data->title);
        }
    }

    bool playAudioFile(Song* song) {
        if (!song || song->filePath.empty()) {
            printError("Invalid file path!");
            return false;
        }

        stopAudio();

        string openCmd = "open \"" + song->filePath + "\" type mpegvideo alias SONG";
        if (mciSendStringA(openCmd.c_str(), NULL, 0, NULL) != 0) {
            printError("Could not open file! Check file path and format.");
            return false;
        }

        if (mciSendStringA("play SONG", NULL, 0, NULL) != 0) {
            printError("Could not play file!");
            return false;
        }

        isPlaying = true;
        isPaused = false;
        song->incrementPlayCount();
        activePlaylist->data->totalPlays++;

        cout << "\n";
        printPlaying("NOW PLAYING"); //megenta 
        setColor(15); //wh
        cout << "  Title: " << song->title << "\n";
        setColor(8); //g
        cout << "  Artist: " << song->artist << "\n";
        cout << "  Playlist: " << activePlaylist->data->name << "\n";
        setColor(7);
        return true;
    }

public:
    MusicPlayer() {
        playlistHead = nullptr;
        playlistTail = nullptr;
        activePlaylist = nullptr;
        isPlaying = false;
        isPaused = false;
        totalPlaylists = 0;
    }

    ~MusicPlayer() {
        stopAudio();
        PlaylistNode* temp = playlistHead;
        while (temp) {
            PlaylistNode* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    PlaylistNode* findPlaylist(string name) {
        PlaylistNode* temp = playlistHead;
        while (temp) {
            if (temp->data->name == name) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    bool createPlaylist(string name, string description = "") {
        if (findPlaylist(name)) {
            printError("Playlist already exists!");
            return false;
        }

        Playlist* newPlaylist = new Playlist(name, description);
        PlaylistNode* newNode = new PlaylistNode(newPlaylist);

        if (!playlistHead) {
            playlistHead = playlistTail = activePlaylist = newNode;
        }
        else {
            playlistTail->next = newNode;
            newNode->prev = playlistTail;
            playlistTail = newNode;
        }

        totalPlaylists++;
        printSuccess("Created new playlist: " + name);
        return true;
    }

    bool setActivePlaylist(string name) {
        PlaylistNode* playlist = findPlaylist(name);
        if (!playlist) {
            printError("Playlist not found!");
            return false;
        }

        activePlaylist = playlist;
        printSuccess("Active playlist set to: " + name);
        return true;
    }

    bool deletePlaylist(string name) {
        PlaylistNode* toDelete = findPlaylist(name);
        if (!toDelete) {
            printError("Playlist not found!");
            return false;
        }

        if (toDelete == activePlaylist) {
            stopAudio();
            activePlaylist = nullptr;
        }

        if (toDelete->prev) {
            toDelete->prev->next = toDelete->next;
        }
        else {
            playlistHead = toDelete->next;
        }

        if (toDelete->next) {
            toDelete->next->prev = toDelete->prev;
        }
        else {
            playlistTail = toDelete->prev;
        }

        delete toDelete;
        totalPlaylists--;
        printSuccess("Deleted playlist: " + name);
        return true;
    }

    void displayAllPlaylists() {
        if (!playlistHead) {
            printInfo("No playlists available!");
            return;
        }

        cout << "\n";
        setColor(11);
        // Original: cout << "  ╔═══════════════════════════════════════════════════════╗\n";
        cout << "  +-------------------------------------------------------+\n";
        // Original: cout << "  ║                   ALL PLAYLISTS                       ║\n";
        cout << "  |                   ALL PLAYLISTS                       |\n";
        // Original: cout << "  ╚═══════════════════════════════════════════════════════╝\n";
        cout << "  +-------------------------------------------------------+\n";
        setColor(7);

        PlaylistNode* temp = playlistHead;
        int num = 1;

        while (temp) {
            cout << "\n";
            if (temp == activePlaylist) {
                setColor(10);
                cout << "  > "; // Changed from '►'
            }
            else {
                cout << "    ";
            }

            setColor(15);
            cout << num << ". " << temp->data->name;
            setColor(8);
            cout << " (" << temp->data->songCount << " songs, "
                << temp->data->totalPlays << " plays)\n";
            setColor(7);

            if (!temp->data->description.empty()) {
                setColor(8);
                cout << "     " << temp->data->description << "\n";
                setColor(7);
            }

            temp = temp->next;
            num++;
        }
        cout << "\n";
    }

    bool addSongToPlaylist(string playlistName, string title, string artist, string path) {
        PlaylistNode* playlist = findPlaylist(playlistName);
        if (!playlist) {
            printError("Playlist not found!");
            return false;
        }

        return playlist->data->addSong(title, artist, path);
    }

    bool playSong(string title) {
        if (!activePlaylist) {
            printError("No playlist selected! Please select an active playlist first.");
            return false;
        }

        SongNode* song = activePlaylist->data->findSong(title);
        if (!song) {
            printError("Song not found in the active playlist!");
            return false;
        }

        activePlaylist->data->current = song;
        return playAudioFile(song->data);
    }

    bool playFirst() {
        //head==null
        if (!activePlaylist || !activePlaylist->data->head) {
            printError("No songs available in the active playlist!");
            return false;
        }

        activePlaylist->data->current = activePlaylist->data->head;
        return playAudioFile(activePlaylist->data->current->data);
    }

    bool playNext() {
        if (!activePlaylist || !activePlaylist->data->current) {
            printError("No song is playing! Starting from the first song.");
            return playFirst();
        }

        //check about found next
        if (activePlaylist->data->current->next) {
            activePlaylist->data->current = activePlaylist->data->current->next;
        }
        else {
            printInfo("End of playlist - starting from beginning");
            activePlaylist->data->current = activePlaylist->data->head;
        }

        return playAudioFile(activePlaylist->data->current->data);
    }

    bool playPrevious() {
        if (!activePlaylist || !activePlaylist->data->current) {
            printError("No song is playing!");
            return false;
        }

        if (activePlaylist->data->current->prev) {
            activePlaylist->data->current = activePlaylist->data->current->prev;
            return playAudioFile(activePlaylist->data->current->data);
        }
        else {
            printError("This is the first song!");
            return false;
        }
    }

    //مسؤله عن تشغيل الاغاني 
    void startPlaybackLoop() {
        if (!activePlaylist) {
            printError("No playlist selected!");
            return;
        }

        if (!activePlaylist->data->head) {
            printError("Playlist is empty!");
            return;
        }

        playFirst();

        setColor(14);
        // Original: cout << "  ╔════════════════════════════════════════╗\n";
        cout << "  +----------------------------------------+\n";
        // Original: cout << "  ║       PLAYBACK CONTROLS                ║\n";
        cout << "  |       PLAYBACK CONTROLS                |\n";
        // Original: cout << "  ╠════════════════════════════════════════╣\n";
        cout << "  +----------------------------------------+\n";
        setColor(7);
        // Original: cout << "  ║  ◄  Previous Song (Left Arrow)         ║\n";
        cout << "  |  <  Previous Song (Left Arrow)         |\n";
        // Original: cout << "  ║  ►  Next Song (Right Arrow)            ║\n";
        cout << "  |  >  Next Song (Right Arrow)            |\n";
        // Original: cout << "  ║  ⏸  Pause/Resume (SPACE)               ║\n";
        cout << "  |  || Pause/Resume (SPACE)               |\n"; // Changed from '⏸'
        // Original: cout << "  ║  ■  Stop & Exit (ESC)                  ║\n";
        cout << "  |  #  Stop & Exit (ESC)                  |\n"; // Changed from '■'
        setColor(14);
        // Original: cout << "  ╚════════════════════════════════════════╝\n";
        cout << "  +----------------------------------------+\n";
        setColor(7);
        cout << "\n";

        bool exitRequested = false;

        while (!exitRequested) {                                                                                                                        
            if (isPlaying && !isPaused) {
                char status[128];
                mciSendStringA("status SONG mode", status, sizeof(status), NULL);

                if (strcmp(status, "stopped") == 0) {
                    if (activePlaylist->data->current->next) {
                        printInfo("Auto-playing next song...");
                        Sleep(500);
                        playNext();
                    }
                    else {
                        printInfo("Playlist finished!");
                        stopAudio();
                        break;
                    }
                }
            }

            if (_kbhit()) {
                int key = _getch();

                if (key == 0 || key == 224) {
                    key = _getch();
                    if (key == 75) {  // Left Arrow
                        playPrevious();
                    }
                    else if (key == 77) {  // Right Arrow
                        playNext();
                    }
                }
                else if (key == ' ') {
                    togglePause();
                }
                else if (key == 27) {  // ESC
                    stopAudio();
                    printInfo("Exiting playback mode...");
                    exitRequested = true;
                }
            }
            Sleep(100);
        }
    }

    bool savePlaylist(string playlistName, string filename) {
        PlaylistNode* playlist = findPlaylist(playlistName);
        if (!playlist) {
            printError("Playlist not found!");
            return false;
        }

        ofstream file(filename);
        if (!file.is_open()) {
            printError("Could not open file for writing!");
            return false;
        }

        // Header: Name, Description, CreatedDate
        file << playlist->data->name << "\n";
        file << playlist->data->description << "\n";
        file << playlist->data->createdDate << "\n";

        // Songs: Title|Artist|FilePath|PlayCount
        SongNode* song = playlist->data->head;
        while (song) {
            file << song->data->title << "|"
                << song->data->artist << "|"
                << song->data->filePath << "|"
                << song->data->playCount << "\n";
            song = song->next;
        }

        file.close();
        printSuccess("Playlist saved to: " + filename);
        return true;
    }

    bool loadPlaylist(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            printError("Could not open file!");
            return false;
        }

        string name, desc, created, line;

        // Read Header
        if (!getline(file, name) || !getline(file, desc) || !getline(file, created)) {
            printError("Invalid file format or empty file!");
            file.close();
            return false;
        }

        if (findPlaylist(name)) {
            printError("A playlist with this name already exists. Please delete it first.");
            file.close();
            return false;
        }
 

        // Create the new playlist
        createPlaylist(name, desc);
        PlaylistNode* newPlaylistNode = findPlaylist(name);
        if (!newPlaylistNode) {
            printError("Failed to create playlist during load.");
            file.close();
            return false;
        }

        // Read Songs
        while (getline(file, line)) {
            stringstream ss(line);
            string segment;
            string title, artist, path, playCountStr;
            int count = 0;

            // Simple tokenization by '|'
            if (getline(ss, title, '|') &&
                getline(ss, artist, '|') &&
                getline(ss, path, '|') &&
                getline(ss, playCountStr, '|'))
            {
                int playCount = stoi(playCountStr);
                //new object
                Song* newSong = new Song(title, artist, path);
                newSong->playCount = playCount;

                SongNode* newNode = new SongNode(newSong);

                // Add to the new playlist's linked list
                if (!newPlaylistNode->data->head) {
                    newPlaylistNode->data->head = newPlaylistNode->data->tail = newPlaylistNode->data->current = newNode;
                }
                else {
                    newPlaylistNode->data->tail->next = newNode;
                    newNode->prev = newPlaylistNode->data->tail;
                    newPlaylistNode->data->tail = newNode;
                }
                newPlaylistNode->data->songCount++;
            }
        }

        file.close();
        printSuccess("Playlist loaded from: " + filename);
        return true;
    }

    //الدالة تُعيد كائن قائمة التشغيل النشطة إذا كانت موجودة، وإلا ترجع nullptr لتدل على عدم وجود قائمة نشطة.
    Playlist* getActivePlaylist() {
        return activePlaylist ? activePlaylist->data : nullptr;
    }

    void displayStatistics() {
        if (!playlistHead) {
            printInfo("No statistics available!");
            return;
        }

        int totalSongs = 0;
        int totalPlays = 0;

        PlaylistNode* temp = playlistHead;
        while (temp) {
            totalSongs += temp->data->songCount;
            totalPlays += temp->data->totalPlays;
            temp = temp->next;
        }

        cout << "\n";
        setColor(11);
        // Original: cout << "  ╔═══════════════════════════════════════════╗\n";
        cout << "  +------------------------------------------+\n";
        // Original: cout << "  ║         GLOBAL STATISTICS                 ║\n";
        cout << "  |         GLOBAL STATISTICS                |\n";
        // Original: cout << "  ╠═══════════════════════════════════════════╣\n";
        cout << "  +------------------------------------------+\n";
        setColor(7);
        // Original: cout << "  ║ Total Playlists: " << setw(25) << left << totalPlaylists << "║\n";
        cout << "  | Total Playlists: " << setw(25) << left << totalPlaylists << "|\n";
        // Original: cout << "  ║ Total Songs: " << setw(29) << left << totalSongs << "║\n";
        cout << "  | Total Songs: " << setw(29) << left << totalSongs << "|\n";
        // Original: cout << "  ║ Total Plays: " << setw(29) << left << totalPlays << "║\n";
        cout << "  | Total Plays: " << setw(29) << left << totalPlays << "|\n";
        setColor(11);
        // Original: cout << "  ╚═══════════════════════════════════════════╝\n";
        cout << "  +------------------------------------------+\n";
        setColor(7);
        cout << "\n";
    }
};

// ==================== MENU FUNCTIONS ====================
void printMainMenu() {
    setColor(11);
    // Original: cout << "\n  ╔════════════════════════════════════════════════════════════╗\n";
    cout << "\n  +------------------------------------------------------------+\n";
    // Original: cout << "  ║               PROFESSIONAL QURAN PLAYER                    ║\n";
    cout << "  |               PROFESSIONAL QURAN PLAYER                    |\n";
    // Original: cout << "  ╠════════════════════════════════════════════════════════════╣\n";
    cout << "  +------------------------------------------------------------+\n";
    setColor(14);
    // Original: cout << "  ║  PLAYLIST MANAGEMENT                                       ║\n";
    cout << "  |  PLAYLIST MANAGEMENT                                       |\n";
    setColor(7);
    // Original: cout << "  ║  1.  Create New Playlist                                   ║\n";
    cout << "  |  1.  Create New Playlist                                   |\n";
    // Original: cout << "  ║  2.  Delete Playlist                                       ║\n";
    cout << "  |  2.  Delete Playlist                                       |\n";
    // Original: cout << "  ║  3.  Display All Playlists                                 ║\n";
    cout << "  |  3.  Display All Playlists                                 |\n";
    // Original: cout << "  ║  11. View Playlist Details                                 ║\n";
    cout << "  |  11. View Playlist Details                                 |\n";
    setColor(14);
    // Original: cout << "  ║  SONG MANAGEMENT                                           ║\n";
    cout << "  |  SONG MANAGEMENT                                           |\n";
    setColor(7);
    // Original: cout << "  ║  4.  Add Song to Playlist                                  ║\n";
    cout << "  |  4.  Add Song to Playlist                                  |\n";
    // Original: cout << "  ║  5.  Remove Song from Playlist                             ║\n";
    cout << "  |  5.  Remove Song from Playlist                             |\n";
    // Original: cout << "  ║  6.  Reorder Songs in Playlist                             ║\n";
    cout << "  |  6.  Reorder Songs in Playlist                             |\n";
    setColor(14);
    // Original: cout << "  ║  PLAYBACK                                                  ║\n";
    cout << "  |  PLAYBACK                                                  |\n";
    setColor(7);
    // Original: cout << "  ║  7.  Play Playlist (Interactive Mode)                      ║\n";
    cout << "  |  7.  Play Playlist (Interactive Mode)                      |\n";
    // Original: cout << "  ║  8.  Play Specific Song                                    ║\n";
    cout << "  |  8.  Play Specific Song                                    |\n";
    // Original: cout << "  ║  12. View Global Statistics                                ║\n";
    cout << "  |  12. View Global Statistics                                |\n";
    setColor(14);
    // Original: cout << "  ║  FILE OPERATIONS                                           ║\n";
    cout << "  |  FILE OPERATIONS                                           |\n";
    setColor(7);
    // Original: cout << "  ║  9.  Save Playlist                                         ║\n";
    cout << "  |  9.  Save Playlist                                         |\n";
    // Original: cout << "  ║  10. Load Playlist                                         ║\n";
    cout << "  |  10. Load Playlist                                         |\n";
    setColor(14);
    // Original: cout << "  ║  SYSTEM                                                    ║\n";
    cout << "  |  SYSTEM                                                    |\n";
    setColor(7);
    // Original: cout << "  ║  0.  Exit Application                                      ║\n";
    cout << "  |  0.  Exit Application                                      |\n";
    setColor(11);
    // Original: cout << "  ╚════════════════════════════════════════════════════════════╝\n";
    cout << "  +------------------------------------------------------------+\n";
    setColor(7);
    cout << "\n  Your choice: ";
}

//رساله انتظار المشتخدم
void waitForKey() {
    setColor(8);
    cout << "\n  Press any key to continue...";

    setColor(7);
   //stop of progeam without wait enter
    _getch();
}



// ==================== MAIN ====================
int main() {
    // This is a Windows-specific application using <windows.h> and <conio.h>
    // It will not compile or run correctly on a standard Linux environment.
    // The code is provided as requested, but the user should be aware of this limitation.
    system("color 0F");

//object include all songs,playlists

    MusicPlayer player;
    int choice;
    string playlistName, songTitle, artist, path, filename, description;
    int fromPos, toPos;

    printHeader("PROFESSIONAL QURAN PLAYLIST MANAGER");

    setColor(14);
    cout << "\n  Initializing application...\n\n";
    setColor(7);

    printInfo("Loading sample playlists...");
    Sleep(500);

    // Sample data
    player.createPlaylist("Sheikh Al-Minshawi", "Beautiful recitations by Sheikh Minshawi");
    player.addSongToPlaylist("Sheikh Al-Minshawi", "Surah Yusuf", "Sheikh Menshawy",
       
   "C:\\Users\\king\\Downloads\\012.mp3" );
    player.addSongToPlaylist("Sheikh Al-Minshawi", "Surah Al-Kahf", "Sheikh Menshawy",
        "C:\\Users\\king\\Downloads\\018 (1).mp3");

    
    Sleep(500);
    printSuccess("Sample playlists loaded successfully!");
    printInfo("Ready to use!");

    Sleep(1500);

    do {
        printHeader("MAIN MENU");
        printMainMenu();

        // Input handling for choice
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // Invalid choice
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        printHeader("PROCESSING REQUEST");

        switch (choice) {
        case 1: // Create New Playlist
            cout << "\n  Playlist name: ";
            getline(cin, playlistName);
            cout << "  Description (optional): ";
            getline(cin, description);
            player.createPlaylist(playlistName, description);
            break;

        case 2: // Delete Playlist
            cout << "\n  Playlist name to delete: ";
            getline(cin, playlistName);
            player.deletePlaylist(playlistName);
            break;

        case 3: // Display All Playlists
            player.displayAllPlaylists();
            break;

        case 4: // Add Song to Playlist
            cout << "\n  Playlist name: ";
            getline(cin, playlistName);
            cout << "  Song title: ";
            getline(cin, songTitle);
            cout << "  Artist/Reciter: ";
            getline(cin, artist);
            cout << "  File path: ";
            getline(cin, path);
            player.addSongToPlaylist(playlistName, songTitle, artist, path);
            break;

        case 5: // Remove Song from Playlist
            cout << "\n  Playlist name: ";
            getline(cin, playlistName);
            {
                PlaylistNode* pNode = player.findPlaylist(playlistName);
                if (pNode) {
                    pNode->data->displaySongs();
                    cout << "  Song title to remove: ";
                    getline(cin, songTitle);
                    pNode->data->removeSong(songTitle);
                }
                else {
                    printError("Playlist not found!");
                }
            }
            break;

        case 6: // Reorder Songs in Playlist
            cout << "\n  Playlist name: ";
            getline(cin, playlistName);
            {
                PlaylistNode* pNode = player.findPlaylist(playlistName);
                if (pNode) {
                    pNode->data->displaySongs();
                    cout << "  Move song from position (number): ";
                    if (!(cin >> fromPos)) {
                        printError("Invalid input for 'from' position.");
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    cout << "  To position (number): ";
                    if (!(cin >> toPos)) {
                        printError("Invalid input for 'to' position.");
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline
                    pNode->data->reorder(fromPos, toPos);
                }
                else {
                    printError("Playlist not found!");
                }
            }
            break;

        case 7: // Play Playlist (Interactive Mode)
            cout << "\n  Playlist name to set as active and play: ";
            getline(cin, playlistName);
            if (player.setActivePlaylist(playlistName)) {
                player.startPlaybackLoop();
            }
            break;

        case 8: // Play Specific Song
            cout << "\n  Set active playlist first (Y/N)? ";
            char set_active;
            cin >> set_active;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (toupper(set_active) == 'Y') {
                cout << "  Playlist name: ";
                getline(cin, playlistName);
                player.setActivePlaylist(playlistName);
            }

            if (player.getActivePlaylist()) {
                player.getActivePlaylist()->displaySongs();
                cout << "  Song title to play: ";
                getline(cin, songTitle);
                player.playSong(songTitle);
            }
            else {
                printError("No active playlist set. Cannot play song.");
            }
            break;

        case 9: // Save Playlist
            cout << "\n  Playlist name to save: ";
            getline(cin, playlistName);
            cout << "  Filename (e.g., mylist.txt): ";
            getline(cin, filename);
            player.savePlaylist(playlistName, filename);
            break;

        case 10: // Load Playlist
            cout << "\n  Filename to load (e.g., mylist.txt): ";
            getline(cin, filename);
            player.loadPlaylist(filename);
            break;

        case 11: // View Playlist Details
            cout << "\n  Playlist name: ";
            getline(cin, playlistName);
            {
                PlaylistNode* pNode = player.findPlaylist(playlistName);
                if (pNode) {
                    pNode->data->getStats();
                    pNode->data->displaySongs();
                }
                else {
                    printError("Playlist not found!");
                }
            }
            break;

        case 12: // View Global Statistics
            player.displayStatistics();
            break;

        case 0: // Exit Application
            printInfo("Exiting application. Goodbye!");
            break;

        default:
            printError("Invalid choice. Please try again.");
            break;
        }

        if (choice != 0 && choice != 7) {
            waitForKey();
        }

    } while (choice != 0);

    return 0;}