int monty_hall_simulation() {
    int door[3];
    int choice;
    int winsbyswitch = 0;
    int i;
    int j;
    int k;
    
    for (i = 0; i < 3000000; i = i + 1) {
        if ((rand() % 2) == 0) {
            door[0] = 1;
        } else {
            door[0] = 0;
        }
        
        if (door[0] == 1) {
            door[1] = 0;
            door[2] = 0;
        } else {
            if ((rand() % 2) == 0) {
                door[1] = 1;
            } else {
                door[1] = 0;
            }
            if (door[1] == 1) {
                door[2] = 0;
            } else {
                door[2] = 1;
            }
        }
        
        choice = rand() % 3;
        
        if ((door[(choice + 1) % 3] == 0 && door[(choice + 2) % 3] == 1) || (door[(choice + 2) % 3] == 0 && door[(choice + 1) % 3] == 1)) {
            winsbyswitch = winsbyswitch + 1;
        }
    }
    
    return winsbyswitch;
}
