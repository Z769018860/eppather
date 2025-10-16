int func(int argc, int argv[1]) {
    if (argc == 99) {
        return 99;
    }
    if (argv[0] != 0) {
        argv[0] = 0;
        argc = 0;
    }
    argc = func(argc + 1, argv);
    int temp1 = argc;
    int temp2 = (argc == 1) ? 0 : 115;
    int temp3 = argc - 1;
    int temp4 = (temp3 == 1) ? 0 : 115;
    return argc - 1;
}
