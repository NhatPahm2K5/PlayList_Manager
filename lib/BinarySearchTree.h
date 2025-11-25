#pragma once
#include <iostream>
#include <vector>
#include <string>
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

class BSTNode {
public:
    Song* song;
    BSTNode* left;
    BSTNode* right;
    int height;

    BSTNode(Song* s) : song(s), left(nullptr), right(nullptr), height(1) {}
};

class BinarySearchTree {
private:
    BSTNode* root;

    // Helper function to get height of node
    int getHeight(BSTNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Helper function to update height
    void updateHeight(BSTNode* node) {
        if (node != nullptr) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    // Helper function to get balance factor
    int getBalanceFactor(BSTNode* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    // Left rotation
    BSTNode* rotateLeft(BSTNode* node) {
        BSTNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    // Right rotation
    BSTNode* rotateRight(BSTNode* node) {
        BSTNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    // Insert with balancing (AVL Tree)
    BSTNode* insertHelper(BSTNode* node, Song* song) {
        if (node == nullptr) {
            return new BSTNode(song);
        }

        // Compare by title (primary key)
        if (song->title < node->song->title) {
            node->left = insertHelper(node->left, song);
        }
        else if (song->title > node->song->title) {
            node->right = insertHelper(node->right, song);
        }
        else {
            // Duplicate title - don't insert
            cerr << RED << "Song with title '" << song->title << "' already exists in library." << RESET << endl;
            return node;
        }

        updateHeight(node);
        int balance = getBalanceFactor(node);

        // Left-Left case
        if (balance > 1 && song->title < node->left->song->title) {
            return rotateRight(node);
        }
        // Right-Right case
        if (balance < -1 && song->title > node->right->song->title) {
            return rotateLeft(node);
        }
        // Left-Right case
        if (balance > 1 && song->title > node->left->song->title) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left case
        if (balance < -1 && song->title < node->right->song->title) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Search by title
    BSTNode* searchByTitleHelper(BSTNode* node, const string& title) {
        if (node == nullptr) {
            return nullptr;
        }

        if (title == node->song->title) {
            return node;
        }
        else if (title < node->song->title) {
            return searchByTitleHelper(node->left, title);
        }
        else {
            return searchByTitleHelper(node->right, title);
        }
    }

    // Search by artist (requires traversal)
    void searchByArtistHelper(BSTNode* node, const string& artist, vector<Song*>& results) {
        if (node == nullptr) {
            return;
        }

        searchByArtistHelper(node->left, artist, results);

        if (node->song->artist.find(artist) != string::npos) {
            results.push_back(node->song);
        }

        searchByArtistHelper(node->right, artist, results);
    }

    // In-order traversal
    void inOrderHelper(BSTNode* node, vector<Song*>& songs) {
        if (node == nullptr) {
            return;
        }

        inOrderHelper(node->left, songs);
        songs.push_back(node->song);
        inOrderHelper(node->right, songs);
    }

    // Delete node
    BSTNode* deleteHelper(BSTNode* node, const string& title) {
        if (node == nullptr) {
            return nullptr;
        }

        if (title < node->song->title) {
            node->left = deleteHelper(node->left, title);
        }
        else if (title > node->song->title) {
            node->right = deleteHelper(node->right, title);
        }
        else {
            // Node found - delete it
            // Case 1: No children
            if (node->left == nullptr && node->right == nullptr) {
                delete node->song;
                delete node;
                return nullptr;
            }
            // Case 2: One child (left)
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: One child (right)
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 4: Two children
            BSTNode* minRight = node->right;
            while (minRight->left != nullptr) {
                minRight = minRight->left;
            }
            node->song = minRight->song;
            node->right = deleteHelper(node->right, minRight->song->title);
        }

        updateHeight(node);
        int balance = getBalanceFactor(node);

        // Rebalance if needed
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Destructor helper
    void destroyTree(BSTNode* node) {
        if (node == nullptr) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Insert song into BST
    void insert(Song* song) {
        root = insertHelper(root, song);
    }

    // Search by title
    Song* searchByTitle(const string& title) {
        BSTNode* node = searchByTitleHelper(root, title);
        return (node != nullptr) ? node->song : nullptr;
    }

    // Search by artist
    vector<Song*> searchByArtist(const string& artist) {
        vector<Song*> results;
        searchByArtistHelper(root, artist, results);
        return results;
    }

    // Get all songs in order
    vector<Song*> getAllSongsInOrder() {
        vector<Song*> songs;
        inOrderHelper(root, songs);
        return songs;
    }

    // Delete song by title
    bool deleteSong(const string& title) {
        BSTNode* node = searchByTitleHelper(root, title);
        if (node == nullptr) {
            cerr << RED << "Song not found in library." << RESET << endl;
            return false;
        }

        root = deleteHelper(root, title);
        cout << GREEN << "Song '" << title << "' removed from library." << RESET << endl;
        return true;
    }

    // Check if song exists
    bool songExists(const string& title) {
        return searchByTitle(title) != nullptr;
    }

    // Get total songs
    int getTotalSongs() {
        return getAllSongsInOrder().size();
    }

    // Destructor
    ~BinarySearchTree() {
        destroyTree(root);
    }
};
