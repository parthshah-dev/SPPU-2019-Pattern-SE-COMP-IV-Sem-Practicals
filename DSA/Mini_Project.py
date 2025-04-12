import os
import pygame
import time

os.chdir("F:/DYP Engg/SEM 4/DSA/Mini Project")

class Song:
    def __init__(self, id, title, artist, file_path):
        self.id = id
        self.title = title
        self.artist = artist
        self.file_path = file_path

    def __str__(self):
        return f"{self.id}. {self.title} by {self.artist} [MP3: {self.file_path}]"

class PlaylistNode:
    def __init__(self, song: Song):
        self.song = song
        self.prev = None
        self.next = None

class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.is_empty():
            return self.items.pop()
        return None

    def is_empty(self):
        return len(self.items) == 0

    def peek(self):
        if not self.is_empty():
            return self.items[-1]
        return None

class Queue:
    def __init__(self):
        self.items = []

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        if not self.is_empty():
            return self.items.pop(0)
        return None

    def is_empty(self):
        return len(self.items) == 0

class PlaylistManager:
    def __init__(self):
        self.head = None
        self.tail = None
        self.current = None
        self.history_stack = Stack()        
        self.upcoming_queue = Queue()        

    def add_song(self, song: Song):
        new_node = PlaylistNode(song)
        if not self.head:
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
        if not self.current:
            self.current = self.head
        print(f"Song added: {song.title}")

    def enqueue_song(self, song: Song):
        self.upcoming_queue.enqueue(song)
        print(f"'{song.title}' added to autoplay queue.")

    def play_current(self):
        if self.current:
            song = self.current.song
            self.history_stack.push(song)  
            print(f"\nNow Playing: {song.title} by {song.artist}")
            try:
                pygame.mixer.init(frequency=44100, size=-16, channels=2)
                pygame.mixer.music.load(song.file_path)
                pygame.mixer.music.play()
                print("Playing... Press Ctrl+C to stop early.")
                while pygame.mixer.music.get_busy():
                    time.sleep(1)
            except KeyboardInterrupt:
                pygame.mixer.music.stop()
                print("\nPlayback stopped by user.")
            except Exception as e:
                print(f"Error playing file: {e}")
        else:
            print("No song is currently selected.")

    def play_next(self):
        if self.upcoming_queue.is_empty():
            if self.current and self.current.next:
                self.current = self.current.next
                self.play_current()
            else:
                print("No next song available.")
        else:
            next_song = self.upcoming_queue.dequeue()  
            print(f"\nPlaying from autoplay queue: {next_song.title}")
            self.history_stack.push(next_song)
            self._play_song(next_song)

    def play_previous(self):
        if not self.history_stack.is_empty():
            prev_song = self.history_stack.pop()  
            print(f"\nPlaying from history: {prev_song.title}")
            self._play_song(prev_song)
        else:
            print("No previous song in history.")

    def _play_song(self, song):
        try:
            pygame.mixer.init(frequency=44100, size=-16, channels=2)
            pygame.mixer.music.load(song.file_path)
            pygame.mixer.music.play()
            print("Playing... Press Ctrl+C to stop early.")
            while pygame.mixer.music.get_busy():
                time.sleep(1)
        except Exception as e:
            print(f"Error playing file: {e}")

    def display_playlist(self):
        if not self.head:
            print("Playlist is empty.")
            return
        print("\n--- Playlist ---")
        node = self.head
        while node:
            marker = " <-- Current" if node == self.current else ""
            print(str(node.song) + marker)
            node = node.next

# Main loop
def main():
    playlist = PlaylistManager()

    while True:
        print("\n--- Music Player Manager ---")
        print("1. Add Song Manually")
        print("2. Play Current Song")
        print("3. Play Next Song")
        print("4. Play Previous Song (From History)")
        print("5. Display Playlist")
        print("6. Enqueue Song (Add to Upcoming Queue)")
        print("7. Exit")

        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("Invalid input. Please enter a number.")
            continue

        if choice == 1:
            try:
                song_id = int(input("Enter Song ID: "))
            except ValueError:
                print("Invalid Song ID.")
                continue
            title = input("Enter Song Title: ")
            artist = input("Enter Artist: ")
            mp3_path = input("Enter MP3 file path: ")
            new_song = Song(song_id, title, artist, mp3_path)
            playlist.add_song(new_song)

        elif choice == 2:
            playlist.play_current()

        elif choice == 3:
            playlist.play_next()

        elif choice == 4:
            playlist.play_previous()

        elif choice == 5:
            playlist.display_playlist()

        elif choice == 6:
            song_id = int(input("Enter Song ID: "))
            title = input("Enter Song Title: ")
            artist = input("Enter Artist: ")
            mp3_path = input("Enter MP3 file path: ")
            new_song = Song(song_id, title, artist, mp3_path)
            playlist.enqueue_song(new_song)

        elif choice == 7:
            print("Exiting Music Player Manager.")
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
