void if2(int firsttest, int secondtest, int bothtrue, int firsttrue, int secondtrue, int bothfalse) {
    int case_val;
    case_val = 0;
    if (firsttest == 0) {
        case_val = case_val + 2;
    }
    if (secondtest == 0) {
        case_val = case_val + 1;
    }
    for (; case_val == 0; ) {
        bothtrue;
        break;
    }
    for (; case_val == 1; ) {
        firsttrue;
        break;
    }
    for (; case_val == 2; ) {
        secondtrue;
        break;
    }
    for (; case_val == 3; ) {
        bothfalse;
        break;
    }
    return;
}
