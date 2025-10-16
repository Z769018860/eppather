int getBlackNeighbours(int imageMatrix[5][5], int row, int col, int imagePixel) {
    int sum[5];
    sum[0] = 0;
    int i[5];
    int j[5];
    for (i[0] = -1; i[0] <= 1; i[0] = i[0] + 1) {
        for (j[0] = -1; j[0] <= 1; j[0] = j[0] + 1) {
            if (i[0] != 0 || j[0] != 0) {
                if (imageMatrix[row + i[0]][col + j[0]] == imagePixel) {
                    sum[0] = sum[0] + 1;
                }
            }
        }
    }
    return sum[0];
}

int getBWTransitions(int imageMatrix[5][5], int row, int col, int blankPixel, int imagePixel) {
    int transitions[5];
    transitions[0] = 0;
    if (imageMatrix[row - 1][col] == blankPixel && imageMatrix[row - 1][col + 1] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row - 1][col + 1] == blankPixel && imageMatrix[row][col + 1] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row][col + 1] == blankPixel && imageMatrix[row + 1][col + 1] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row + 1][col + 1] == blankPixel && imageMatrix[row + 1][col] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row + 1][col] == blankPixel && imageMatrix[row + 1][col - 1] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row + 1][col - 1] == blankPixel && imageMatrix[row][col - 1] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row][col - 1] == blankPixel && imageMatrix[row - 1][col - 1] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    if (imageMatrix[row - 1][col - 1] == blankPixel && imageMatrix[row - 1][col] == imagePixel) {
        transitions[0] = transitions[0] + 1;
    }
    return transitions[0];
}

int zhangSuenTest1(int imageMatrix[5][5], int row, int col, int blankPixel, int imagePixel) {
    int neighbours[5];
    neighbours[0] = getBlackNeighbours(imageMatrix, row, col, imagePixel);
    int transitions[5];
    transitions[0] = getBWTransitions(imageMatrix, row, col, blankPixel, imagePixel);
    if ((neighbours[0] >= 2 && neighbours[0] <= 6) && (transitions[0] == 1)) {
        if (imageMatrix[row - 1][col] == blankPixel || imageMatrix[row][col + 1] == blankPixel || imageMatrix[row + 1][col] == blankPixel) {
            if (imageMatrix[row][col + 1] == blankPixel || imageMatrix[row + 1][col] == blankPixel || imageMatrix[row][col - 1] == blankPixel) {
                return 1;
            }
        }
    }
    return 0;
}

int zhangSuenTest2(int imageMatrix[5][5], int row, int col, int blankPixel, int imagePixel) {
    int neighbours[5];
    neighbours[0] = getBlackNeighbours(imageMatrix, row, col, imagePixel);
    int transitions[5];
    transitions[0] = getBWTransitions(imageMatrix, row, col, blankPixel, imagePixel);
    if ((neighbours[0] >= 2 && neighbours[0] <= 6) && (transitions[0] == 1)) {
        if (imageMatrix[row - 1][col] == blankPixel || imageMatrix[row][col + 1] == blankPixel || imageMatrix[row][col - 1] == blankPixel) {
            if (imageMatrix[row - 1][col] == blankPixel || imageMatrix[row + 1][col] == blankPixel || imageMatrix[row][col + 1] == blankPixel) {
                return 1;
            }
        }
    }
    return 0;
}

void zhangSuen(int imageMatrix[5][5], int rows, int cols, int blankPixel, int imagePixel) {
    int startRow[5];
    startRow[0] = 1;
    int startCol[5];
    startCol[0] = 1;
    int endRow[5];
    endRow[0] = rows - 2;
    int endCol[5];
    endCol[0] = cols - 2;
    int i[5];
    int j[5];
    int count[5];
    int processed[5];
    int markers[5][5][5];
    do {
        count[0] = 0;
        for (i[0] = startRow[0]; i[0] <= endRow[0]; i[0] = i[0] + 1) {
            for (j[0] = startCol[0]; j[0] <= endCol[0]; j[0] = j[0] + 1) {
                if (imageMatrix[i[0]][j[0]] == imagePixel && zhangSuenTest1(imageMatrix, i[0], j[0], blankPixel, imagePixel) == 1) {
                    markers[count[0]][0][0] = i[0];
                    markers[count[0]][0][1] = j[0];
                    count[0] = count[0] + 1;
                }
            }
        }
        processed[0] = (count[0] > 0);
        for (i[0] = 0; i[0] < count[0]; i[0] = i[0] + 1) {
            imageMatrix[markers[i[0]][0][0]][markers[i[0]][0][1]] = blankPixel;
        }
        count[0] = 0;
        for (i[0] = startRow[0]; i[0] <= endRow[0]; i[0] = i[0] + 1) {
            for (j[0] = startCol[0]; j[0] <= endCol[0]; j[0] = j[0] + 1) {
                if (imageMatrix[i[0]][j[0]] == imagePixel && zhangSuenTest2(imageMatrix, i[0], j[0], blankPixel, imagePixel) == 1) {
                    markers[count[0]][0][0] = i[0];
                    markers[count[0]][0][1] = j[0];
                    count[0] = count[0] + 1;
                }
            }
        }
        if (processed[0] == 0) {
            processed[0] = (count[0] > 0);
        }
        for (i[0] = 0; i[0] < count[0]; i[0] = i[0] + 1) {
            imageMatrix[markers[i[0]][0][0]][markers[i[0]][0][1]] = blankPixel;
        }
    } while (processed[0] == 1);
    return;
}
