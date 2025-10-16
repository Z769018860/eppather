void verlet_stormer_velocity_verlet(int* time_ptr, int* vel_ptr, int pos, int acc, int dt) {
    int prev_pos;
    int temp_pos;
    int time;
    int vel;
    int i;
    
    time = 0;
    vel = 0;
    prev_pos = pos;
    
    for (i = 0; pos > 0; i = i + 1) {
        time = time + dt;
        temp_pos = pos;
        pos = pos * 2 - prev_pos + acc * dt * dt;
        prev_pos = temp_pos;
        vel = vel + acc * dt;
    }
    
    *time_ptr = time;
    *vel_ptr = vel;
    return;
}
