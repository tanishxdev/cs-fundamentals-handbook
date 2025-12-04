#include <iostream>
#include <vector>
using namespace std;

// Iterator Interface
template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() {}
};

// Aggregate Interface (Collection)
template <typename T>
class Aggregate {
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual ~Aggregate() {}
};

// Forward declare Playlist
class Playlist;

// Concrete Iterator
class PlaylistIterator : public Iterator<string> {
private:
    Playlist& playlist;
    int index;
public:
    PlaylistIterator(Playlist& p);

    bool hasNext() override;
    string next() override;
};

// Concrete Collection
class Playlist : public Aggregate<string> {
private:
    vector<string> songs;
public:
    void addSong(const string& song) {
        songs.push_back(song);
    }

    vector<string>& getSongs() {
        return songs;
    }

    Iterator<string>* createIterator() override {
        return new PlaylistIterator(*this);
    }
};

// Implement PlaylistIterator methods
PlaylistIterator::PlaylistIterator(Playlist& p) : playlist(p), index(0) {}

bool PlaylistIterator::hasNext() {
    return index < playlist.getSongs().size();
}

string PlaylistIterator::next() {
    return playlist.getSongs()[index++];
}

// Client Code
int main() {
    Playlist myPlaylist;
    myPlaylist.addSong("Shape of You");
    myPlaylist.addSong("Believer");
    myPlaylist.addSong("Senorita");

    Iterator<string>* it = myPlaylist.createIterator();

    cout << "🎵 Playing Playlist:" << endl;
    while (it->hasNext()) {
        cout << "Now Playing: " << it->next() << endl;
    }

    delete it; // cleanup
    return 0;
}
