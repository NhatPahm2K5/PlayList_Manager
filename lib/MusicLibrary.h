#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "BinarySearchTree.h"
#include "Song.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

using namespace std;

class MusicLibrary {
private:
    BinarySearchTree bst;

public:
    MusicLibrary() {}

    // Add song to library (BST owns the Song*) and return the pointer
    Song* addSongToLibrary(const string& title, const string& artist, const string& genre, 
                         const string& album, int year, double duration) {
        try {
            Song* newSong = new Song(title, artist, genre, album, year, duration);
            bst.insert(newSong);
            cout << GREEN << "Song '" << title << "' added to library successfully!" << RESET << endl;
            return newSong;
        }
        catch (const invalid_argument& e) {
            cerr << RED << "Error adding song to library: " << RESET << YELLOW << e.what() << RESET << endl;
            return nullptr;
        }
    }

    // Search by title
    Song* searchSongByTitle(const string& title) {
        if (!Song::isValidString(title)) {
            cerr << RED << "Invalid song title: " << RESET << title << endl;
            return nullptr;
        }

        Song* song = bst.searchByTitle(title);
        if (song != nullptr) {
            cout << GREEN << "Found: " << song->title << " by " << song->artist << RESET << endl;
            return song;
        }
        else {
            cout << RED << "Song '" << title << "' not found in library." << RESET << endl;
            return nullptr;
        }
    }

    // Search by artist
    vector<Song*> searchSongsByArtist(const string& artist) {
        if (!Song::isValidString(artist)) {
            cerr << RED << "Invalid artist name: " << RESET << artist << endl;
            return vector<Song*>();
        }

        vector<Song*> results = bst.searchByArtist(artist);
        
        if (results.empty()) {
            cout << YELLOW << "No songs found for artist '" << artist << "'." << RESET << endl;
        }
        else {
            cout << GREEN << "Found " << results.size() << " song(s) by " << artist << ":" << RESET << endl;
        }

        return results;
    }

    // Display all songs in library
    void displayAllSongs() {
        vector<Song*> songs = bst.getAllSongsInOrder();

        if (songs.empty()) {
            cout << YELLOW << "Library is empty." << RESET << endl;
            return;
        }

        cout << BOLD << CYAN << "\n===== All Songs in Library =====" << RESET << endl;
        cout << BOLD << "+-----+------------------------+------------------------+---------+------+----------+" << RESET << endl;
        cout << BOLD << "| No. | Title                  | Artist                 | Genre   | Year | Duration |" << RESET << endl;
        cout << BOLD << "+-----+------------------------+------------------------+---------+------+----------+" << RESET << endl;

        int index = 1;
        for (Song* song : songs) {
            cout << "| " << setw(3) << index << " | "
                << setw(22) << song->title << " | "
                << setw(22) << song->artist << " | "
                << setw(7) << song->genre << " | "
                << setw(4) << song->year << " | "
                << setw(6) << fixed << setprecision(1) << song->duration << " |" << endl;
            index++;
        }

        cout << BOLD << "+-----+------------------------+------------------------+---------+------+----------+" << RESET << endl;
        cout << GREEN << "Total songs in library: " << songs.size() << RESET << endl;
    }

    // Display search results
    void displaySearchResults(const vector<Song*>& songs) {
        if (songs.empty()) {
            cout << YELLOW << "No songs found." << RESET << endl;
            return;
        }

        cout << BOLD << CYAN << "\n===== Search Results =====" << RESET << endl;
        cout << BOLD << "+-----+------------------------+------------------------+---------+------+----------+" << RESET << endl;
        cout << BOLD << "| No. | Title                  | Artist                 | Genre   | Year | Duration |" << RESET << endl;
        cout << BOLD << "+-----+------------------------+------------------------+---------+------+----------+" << RESET << endl;

        int index = 1;
        for (Song* song : songs) {
            cout << "| " << setw(3) << index << " | "
                << setw(22) << song->title << " | "
                << setw(22) << song->artist << " | "
                << setw(7) << song->genre << " | "
                << setw(4) << song->year << " | "
                << setw(6) << fixed << setprecision(1) << song->duration << " |" << endl;
            index++;
        }

        cout << BOLD << "+-----+------------------------+------------------------+---------+------+----------+" << RESET << endl;
    }

    // Remove song from library
    bool removeSongFromLibrary(const string& title) {
        if (!Song::isValidString(title)) {
            cerr << RED << "Invalid song title: " << RESET << title << endl;
            return false;
        }

        char confirm;
        cout << YELLOW << "Are you sure you want to delete '" << title << "' from library? (y/n): " << RESET;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << GREEN << "Action canceled." << RESET << endl;
            return false;
        }

        return bst.deleteSong(title);
    }

    // Get song for adding to playlist
    Song* getSongForPlaylist(const string& title) {
        return bst.searchByTitle(title);
    }

    // Check if song exists in library
    bool songExists(const string& title) {
        return bst.songExists(title);
    }

    // Get total songs in library
    int getTotalSongsInLibrary() {
        return bst.getTotalSongs();
    }

    // Get all songs in library
    vector<Song*> getAllSongs() {
        return bst.getAllSongsInOrder();
    }

    // Display song details
    void displaySongDetails(const Song* song) {
        if (song == nullptr) {
            cout << RED << "Song is null." << RESET << endl;
            return;
        }

        cout << BOLD << CYAN << "\n===== Song Details =====" << RESET << endl;
        cout << GREEN << "Title: " << RESET << song->title << endl;
        cout << GREEN << "Artist: " << RESET << song->artist << endl;
        cout << GREEN << "Genre: " << RESET << song->genre << endl;
        cout << GREEN << "Album: " << RESET << song->album << endl;
        cout << GREEN << "Year: " << RESET << song->year << endl;
        cout << GREEN << "Duration: " << RESET << fixed << setprecision(1) << song->duration << " minutes" << endl;
        cout << CYAN << "=======================" << RESET << endl;
    }

    ~MusicLibrary() {}
};
