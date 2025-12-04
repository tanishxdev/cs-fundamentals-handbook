# **Iterator Pattern**

* https://www.geeksforgeeks.org/system-design/iterator-pattern/

### **What is it?**

Iterator provides a way to **access elements of a collection sequentially** (one by one) **without exposing the internal structure** (like arrays, linked lists, trees).

It separates **traversal logic** from the collection itself.

---

## **Why do we need it?**

* Without iterators, each collection (array, list, tree, graph) would need custom traversal code → leads to **duplication**.
* Iterator abstracts traversal → client code doesn’t care *how* the collection is implemented.
* Major use: **STL in C++ (vector, list, map, set all provide iterators)**.

---

## **Real-world examples**

* Browsing songs in a music playlist (you don’t care if it’s stored as an array, DB, or linked list).
* Moving through pages of a PDF reader.
* Iterating over database query results.

---

## **Implementation in C++**

### 1. Define `Iterator` interface

```cpp
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
```

---

### 2. Define `Aggregate` (Collection) interface

```cpp
// Aggregate Interface (Collection)
template <typename T>
class Aggregate {
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual ~Aggregate() {}
};
```

---

### 3. Concrete Collection (e.g., Playlist)

```cpp
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

    Iterator<string>* createIterator() override;
};
```

---

### 4. Concrete Iterator

```cpp
class PlaylistIterator : public Iterator<string> {
private:
    Playlist& playlist;
    int index;
public:
    PlaylistIterator(Playlist& p) : playlist(p), index(0) {}

    bool hasNext() override {
        return index < playlist.getSongs().size();
    }

    string next() override {
        return playlist.getSongs()[index++];
    }
};
```

---

### 5. Connect Playlist to Iterator

```cpp
Iterator<string>* Playlist::createIterator() {
    return new PlaylistIterator(*this);
}
```

---

### 6. Client code

```cpp
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
```

---

## **Output**

```
🎵 Playing Playlist:
Now Playing: Shape of You
Now Playing: Believer
Now Playing: Senorita
```

---

## **Key Points**

* Iterator **decouples traversal** from collection.
* Easy to **add new traversal strategies** (e.g., reverse iterator).
* In C++, STL iterators are the real-life implementation of this pattern.
