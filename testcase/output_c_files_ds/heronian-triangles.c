int gcd(int a, int b) {
    if (b != 0) {
        return gcd(b, a % b);
    }
    return a;
}

void generateTriangleList(int maxSide, int count[1], int triangles[1000][5]) {
    int a;
    int b;
    int c;
    int perimeter;
    int areaSquared;
    int s;
    int temp;
    int i;
    int j;
    int k;
    int current[5];
    
    count[0] = 0;
    
    for (a = 1; a <= maxSide; a = a + 1) {
        for (b = 1; b <= a; b = b + 1) {
            for (c = 1; c <= b; c = c + 1) {
                if (c + b > a && gcd(gcd(a, b), c) == 1) {
                    perimeter = a + b + c;
                    s = perimeter / 2;
                    temp = s * (s - a) * (s - b) * (s - c);
                    areaSquared = temp;
                    
                    for (i = 0; i * i <= temp; i = i + 1) {
                        if (i * i == temp) {
                            current[0] = a;
                            current[1] = b;
                            current[2] = c;
                            current[3] = perimeter;
                            current[4] = i;
                            
                            for (j = 0; j < count[0]; j = j + 1) {
                                if ((triangles[j][4] < current[4]) || 
                                    (triangles[j][4] == current[4] && triangles[j][3] < current[3]) || 
                                    (triangles[j][4] == current[4] && triangles[j][3] == current[3] && triangles[j][0] <= current[0])) {
                                    for (k = count[0]; k > j; k = k - 1) {
                                        triangles[k][0] = triangles[k - 1][0];
                                        triangles[k][1] = triangles[k - 1][1];
                                        triangles[k][2] = triangles[k - 1][2];
                                        triangles[k][3] = triangles[k - 1][3];
                                        triangles[k][4] = triangles[k - 1][4];
                                    }
                                    break;
                                }
                            }
                            
                            triangles[j][0] = current[0];
                            triangles[j][1] = current[1];
                            triangles[j][2] = current[2];
                            triangles[j][3] = current[3];
                            triangles[j][4] = current[4];
                            count[0] = count[0] + 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return;
}
