int pick(int at, int remain, int accu, int treat) {
    int data[19] = {85, 88, 75, 66, 25, 29, 83, 39, 97, 68, 41, 10, 49, 16, 65, 32, 92, 28, 98};
    int result;
    if (remain == 0) {
        if (accu > treat) {
            result = 1;
        } else {
            result = 0;
        }
        return result;
    }
    result = pick(at - 1, remain - 1, accu + data[at - 1], treat);
    if (at > remain) {
        result = result + pick(at - 1, remain, accu, treat);
    }
    return result;
}
