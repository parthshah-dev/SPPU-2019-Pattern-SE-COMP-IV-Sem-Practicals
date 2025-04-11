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


class PlaylistManager:
    def __init__(self):
        self.head = None
        self.tail = None
        self.current = None

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

    def play_current(self):
        if self.current:
            song = self.current.song
            print(f"\nNow Playing: {song.title} by {song.artist}")
            print(f"Playing file: {song.file_path}")
            try:
                pygame.mixer.init(frequency=44100, size=-16, channels=2)
                pygame.mixer.music.load(song.file_path)
                pygame.mixer.music.play()
                print("Playing... Press Ctrl+C to stop early.")
                try:
                    while pygame.mixer.music.get_busy():
                        time.sleep(1)
                except KeyboardInterrupt:
                    pygame.mixer.music.stop()
                    print("\nPlayback stopped by user.")
            except pygame.error as e:
                print(f"Error playing file: {e}")
            except Exception as e:
                print(f"An unexpected error occurred: {e}")
        else:
            print("No song is currently selected.")

    def play_next(self):
        if self.current and self.current.next:
            self.current = self.current.next
            self.play_current()
        else:
            print("No next song available.")

    def play_previous(self):
        if self.current and self.current.prev:
            self.current = self.current.prev
            self.play_current()
        else:
            print("No previous song available.")

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


def main():
    playlist = PlaylistManager()

    while True:
        print("\n--- Music Player Manager ---")
        print("1. Add Song Manually")
        print("2. Play Current Song")
        print("3. Play Next Song")
        print("4. Play Previous Song")
        print("5. Display Playlist")
        print("6. Exit")

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
            print("Exiting Music Player Manager.")
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
