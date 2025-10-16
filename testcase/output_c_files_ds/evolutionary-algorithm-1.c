int irand(int n) {
    int r;
    int rand_max = 32767 - (32767 % n);
    while (1) {
        r = rand();
        if (r < rand_max) {
            break;
        }
    }
    return r / (rand_max / n);
}

int unfitness(const char *a, const char *b) {
    int i;
    int sum = 0;
    for (i = 0; a[i] != 0; i = i + 1) {
        if (a[i] != b[i]) {
            sum = sum + 1;
        }
    }
    return sum;
}

void mutate(const char *a, char *b) {
    int i;
    for (i = 0; a[i] != 0; i = i + 1) {
        if (irand(15) != 0) {
            b[i] = a[i];
        } else {
            b[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "[irand(27)];
        }
    }
    b[i] = 0;
}

void evolve() {
    int i;
    int best_i;
    int unfit;
    int best;
    int iters = 0;
    char specimen[30][29];
    char target[29] = "METHINKS IT IS LIKE A WEASEL";

    for (i = 0; target[i] != 0; i = i + 1) {
        specimen[0][i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "[irand(27)];
    }
    specimen[0][i] = 0;

    do {
        for (i = 1; i < 30; i = i + 1) {
            mutate(specimen[0], specimen[i]);
        }

        best_i = 0;
        for (i = 0; i < 30; i = i + 1) {
            unfit = unfitness(target, specimen[i]);
            if (i == 0 || unfit < best) {
                best = unfit;
                best_i = i;
            }
        }

        if (best_i != 0) {
            for (i = 0; specimen[best_i][i] != 0; i = i + 1) {
                specimen[0][i] = specimen[best_i][i];
            }
            specimen[0][i] = 0;
        }
        iters = iters + 1;
    } while (best != 0);

    return;
}
