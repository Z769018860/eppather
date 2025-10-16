int monty_hall(int n) {
    int door[3];
    int winsbyswitch[5] = {0};
    int choice;
    int i;
    int j;
    int k;
    
    for (i = 0; i < 5; i = i + 1) {
        door[0] = (rand() % 2 == 0) ? 1 : 0;
        if (door[0] == 1) {
            door[1] = 0;
            door[2] = 0;
        } else {
            door[1] = (rand() % 2 == 0) ? 1 : 0;
            door[2] = (door[1] == 0) ? 1 : 0;
        }
        choice = rand() % 3;
        
        if ((door[(choice + 1) % 3] == 0 && door[(choice + 2) % 3] == 1) || 
            (door[(choice + 2) % 3] == 0 && door[(choice + 1) % 3] == 1)) {
            winsbyswitch[0] = winsbyswitch[0] + 1;
        }
    }
    return;
}
