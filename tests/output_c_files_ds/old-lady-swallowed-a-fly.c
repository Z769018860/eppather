void func() {
    char animals[8][16] = {"fly", "spider", "bird", "cat", "dog", "goat", "cow", "horse"};
    char verses[8][64] = {
        "I don't know why she swallowed that fly.\nPerhaps she'll die\n",
        "That wiggled and jiggled and tickled inside her",
        "How absurd, to swallow a bird",
        "Imagine that. She swallowed a cat",
        "What a hog to swallow a dog",
        "She just opened her throat and swallowed that goat",
        "I don't know how she swallowed that cow",
        "She's dead of course"
    };
    
    for (int i = 0; i < 8; i = i + 1) {
        for (int j = i; j > 0; j = j - 1) {
            if (i < 7) {
                if (j == 1) {
                }
            }
        }
    }
    return;
}
