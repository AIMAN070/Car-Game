void play_sound() {
    Beep(523, 500);  // Frequency: 523Hz, Duration: 500ms (C5)
    Beep(587, 500);  // Frequency: 587Hz, Duration: 500ms (D5)
    Beep(659, 500);  // Frequency: 659Hz, Duration: 500ms (E5)
    Beep(698, 500);  // Frequency: 698Hz, Duration: 500ms (F5)
    Beep(784, 1000); // Frequency: 784Hz, Duration: 1000ms (G5)
    Beep(880, 1000); // Frequency: 880Hz, Duration: 1000ms (A5)
    Beep(988, 1000); // Frequency: 988Hz, Duration: 1000ms (B5)
}

void add_sound() {
    // Call the play_sound function to play the sound
    play_sound();
}
void playe_sound() {
    Beep(500, 500); // Play a tone with a frequency of 500 Hz for 500 milliseconds
    Sleep(100);     // Pause for 100 milliseconds
    Beep(500, 500); // Play another tone with the same frequency and duration
}

