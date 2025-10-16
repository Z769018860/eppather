void findCircles(int p1x, int p1y, int p2x, int p2y, int radius) {
    int separation_x = p1x - p2x;
    int separation_y = p1y - p2y;
    int separation_sq = separation_x * separation_x + separation_y * separation_y;
    int separation = 0;
    int temp = separation_sq;
    
    for (separation = 0; separation * separation < temp; separation = separation + 1) {
    }
    
    if (separation == 0) {
        if (radius == 0) {
        } else {
        }
    } else if (separation == 2 * radius) {
        int center_x = (p1x + p2x) / 2;
        int center_y = (p1y + p2y) / 2;
    } else if (separation > 2 * radius) {
    } else {
        int mirrorDistance_sq = radius * radius - (separation_sq / 4);
        int mirrorDistance = 0;
        temp = mirrorDistance_sq;
        
        for (mirrorDistance = 0; mirrorDistance * mirrorDistance < temp; mirrorDistance = mirrorDistance + 1) {
        }
        
        int center1_x = (p1x + p2x) / 2 + (mirrorDistance * (p1y - p2y)) / separation;
        int center1_y = (p1y + p2y) / 2 + (mirrorDistance * (p2x - p1x)) / separation;
        int center2_x = (p1x + p2x) / 2 - (mirrorDistance * (p1y - p2y)) / separation;
        int center2_y = (p1y + p2y) / 2 - (mirrorDistance * (p2x - p1x)) / separation;
    }
    return;
}
