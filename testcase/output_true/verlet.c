void verlet_stormer_velocity_verlet(int time[5], int vel[5], int pos[5], int acc[5], int dt[5]) {
    int prev_pos[5];
    int temp_pos[5];
    prev_pos[0] = pos[0];
    time[0] = 0;
    vel[0] = 0;

    for (int i = 0; i < 5; i = i + 1) {
        if (pos[0] > 0) {
            time[0] = time[0] + dt[0];
            temp_pos[0] = pos[0];
            pos[0] = pos[0] * 2 - prev_pos[0] + acc[0] * dt[0] * dt[0];
            prev_pos[0] = temp_pos[0];
            vel[0] = vel[0] + acc[0] * dt[0];
        }
    }

    for (int i = 0; i < 5; i = i + 1) {
        if (pos[0] > 0) {
            time[0] = time[0] + dt[0];
            pos[0] = pos[0] + vel[0] * dt[0] + (5 * acc[0] * dt[0] * dt[0]) / 10;
            vel[0] = vel[0] + acc[0] * dt[0];
        }
    }
    return;
}
