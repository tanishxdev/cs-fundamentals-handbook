#include <iostream>
#include <string>
using namespace std;

// ---------------- State Interface ----------------
class State {
public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual ~State() {}
};

// Forward declaration (for state transitions)
class MediaPlayer;

// ---------------- Concrete States ----------------

// Stopped State
class StoppedState : public State {
private:
    MediaPlayer* player;
public:
    StoppedState(MediaPlayer* p) : player(p) {}
    void play() override;
    void pause() override {
        cout << "[Stopped] Can't pause, already stopped!\n";
    }
    void stop() override {
        cout << "[Stopped] Already stopped.\n";
    }
};

// Playing State
class PlayingState : public State {
private:
    MediaPlayer* player;
public:
    PlayingState(MediaPlayer* p) : player(p) {}
    void play() override {
        cout << "[Playing] Already playing!\n";
    }
    void pause() override;
    void stop() override;
};

// Paused State
class PausedState : public State {
private:
    MediaPlayer* player;
public:
    PausedState(MediaPlayer* p) : player(p) {}
    void play() override;
    void pause() override {
        cout << "[Paused] Already paused.\n";
    }
    void stop() override;
};

// ---------------- Context: MediaPlayer ----------------
class MediaPlayer {
private:
    State* currentState;

public:
    MediaPlayer(State* initialState) : currentState(initialState) {}

    void setState(State* state) {
        currentState = state;
    }

    void play() { currentState->play(); }
    void pause() { currentState->pause(); }
    void stop() { currentState->stop(); }
};

// ---------------- State Implementations ----------------

// Forward declare states so they can transition
StoppedState* stopped = nullptr;
PlayingState* playing = nullptr;
PausedState* paused = nullptr;

// Stopped -> Playing
void StoppedState::play() {
    cout << "[Stopped] Starting playback...\n";
    player->setState(playing);
}

// Playing -> Paused
void PlayingState::pause() {
    cout << "[Playing] Pausing playback...\n";
    player->setState(paused);
}

// Playing -> Stopped
void PlayingState::stop() {
    cout << "[Playing] Stopping playback...\n";
    player->setState(stopped);
}

// Paused -> Playing
void PausedState::play() {
    cout << "[Paused] Resuming playback...\n";
    player->setState(playing);
}

// Paused -> Stopped
void PausedState::stop() {
    cout << "[Paused] Stopping playback...\n";
    player->setState(stopped);
}

// ---------------- Client ----------------
int main() {
    MediaPlayer player(nullptr);

    // Initialize states with reference to context
    stopped = new StoppedState(&player);
    playing = new PlayingState(&player);
    paused  = new PausedState(&player);

    // Set initial state
    player.setState(stopped);

    // Simulate button presses
    player.play();   // Stopped -> Playing
    player.pause();  // Playing -> Paused
    player.play();   // Paused -> Playing
    player.stop();   // Playing -> Stopped
    player.stop();   // Already stopped

    // Cleanup
    delete stopped;
    delete playing;
    delete paused;

    return 0;
}

// Real-world use:

// A music app player behaves differently depending on state:

// Play → starts music

// Pause → pauses music

// Stop → stops playback