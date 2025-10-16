void stable_marriage(int verbose_flag, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20, int n21, int n22, int n23, int n24, int n25, int n26, int n27, int n28, int n29, int n30, int n31, int n32, int n33, int n34, int n35, int n36, int n37, int n38, int n39, int n40, int n41, int n42, int n43, int n44, int n45, int n46, int n47, int n48, int n49, int n50, int n51, int n52, int n53, int n54, int n55, int n56, int n57, int n58, int n59, int n60, int n61, int n62, int n63, int n64, int n65, int n66, int n67, int n68, int n69, int n70, int n71, int n72, int n73, int n74, int n75, int n76, int n77, int n78, int n79, int n80, int n81, int n82, int n83, int n84, int n85, int n86, int n87, int n88, int n89, int n90, int n91, int n92, int n93, int n94, int n95, int n96, int n97, int n98, int n99, int n100, int n101, int n102, int n103, int n104, int n105, int n106, int n107, int n108, int n109, int n110, int n111, int n112, int n113, int n114, int n115, int n116, int n117, int n118, int n119, int n120, int n121, int n122, int n123, int n124, int n125, int n126, int n127, int n128, int n129, int n130, int n131, int n132, int n133, int n134, int n135, int n136, int n137, int n138, int n139, int n140, int n141, int n142, int n143, int n144, int n145, int n146, int n147, int n148, int n149, int n150, int n151, int n152, int n153, int n154, int n155, int n156, int n157, int n158, int n159, int n160, int n161, int n162, int n163, int n164, int n165, int n166, int n167, int n168, int n169, int n170, int n171, int n172, int n173, int n174, int n175, int n176, int n177, int n178, int n179, int n180, int n181, int n182, int n183, int n184, int n185, int n186, int n187, int n188, int n189, int n190, int n191, int n192, int n193, int n194, int n195, int n196, int n197, int n198, int n199, int n200)
{
    int clown = -1;
    int abe = 0;
    int bob = 1;
    int col = 2;
    int dan = 3;
    int ed = 4;
    int fred = 5;
    int gav = 6;
    int hal = 7;
    int ian = 8;
    int jon = 9;
    int abi = 10;
    int bea = 11;
    int cath = 12;
    int dee = 13;
    int eve = 14;
    int fay = 15;
    int gay = 16;
    int hope = 17;
    int ivy = 18;
    int jan = 19;
    
    int pref[20][10] = {
        {10, 14, 12, 18, 19, 13, 15, 11, 17, 16},
        {12, 17, 10, 13, 14, 15, 11, 19, 18, 16},
        {17, 14, 10, 13, 11, 15, 18, 16, 12, 19},
        {18, 15, 13, 16, 17, 14, 19, 11, 12, 10},
        {19, 13, 11, 12, 15, 14, 10, 18, 17, 16},
        {11, 10, 13, 16, 14, 18, 12, 19, 17, 15},
        {16, 14, 18, 11, 12, 10, 13, 17, 19, 15},
        {10, 14, 17, 15, 18, 12, 19, 11, 16, 13},
        {17, 12, 13, 16, 11, 10, 15, 18, 19, 14},
        {10, 15, 19, 16, 14, 11, 13, 12, 18, 17},
        {1, 5, 9, 6, 8, 0, 3, 4, 2, 7},
        {1, 0, 2, 5, 6, 3, 8, 4, 9, 7},
        {5, 1, 4, 6, 7, 2, 8, 0, 3, 9},
        {5, 9, 2, 0, 8, 7, 6, 3, 1, 4},
        {9, 7, 5, 3, 0, 6, 2, 4, 8, 1},
        {1, 0, 4, 8, 9, 3, 5, 6, 2, 7},
        {9, 6, 7, 5, 1, 0, 2, 4, 3, 8},
        {6, 9, 1, 0, 8, 3, 7, 4, 2, 5},
        {8, 2, 7, 6, 5, 1, 0, 4, 9, 3},
        {4, 7, 6, 0, 1, 9, 2, 8, 5, 3}
    };
    
    int pairs[20];
    int proposed[20];
    int i;
    int j;
    int unengaged;
    int man1;
    int man2;
    int woman;
    int man;
    int fiance;
    int this;
    int that;
    int bad;
    
    for (i = 0; i < 20; i = i + 1) {
        pairs[i] = clown;
        proposed[i] = clown;
    }
    
    do {
        unengaged = 0;
        for (i = 0; i < 10; i = i + 1) {
            if (pairs[i] != clown) {
                continue;
            }
            unengaged = 1;
            proposed[i] = proposed[i] + 1;
            woman = pref[i][proposed[i]];
            fiance = pairs[woman];
            if (fiance == clown) {
                pairs[i] = woman;
                pairs[woman] = i;
            } else {
                for (j = 0; j < 10 && pref[woman][j] != i; j = j + 1);
                for (that = 0; that < 10 && pref[woman][that] != fiance; that = that + 1);
                if (j < that) {
                    pairs[fiance] = clown;
                    pairs[woman] = clown;
                    pairs[i] = woman;
                    pairs[woman] = i;
                }
            }
        }
    } while (unengaged);
    
    bad = 0;
    for (i = 0; i < 9; i = i + 1) {
        for (j = i + 1; j < 10; j = j + 1) {
            man1 = i;
            man2 = j;
            woman = pairs[man2];
            for (this = 0; this < 10 && pref[man1][this] != woman; this = this + 1);
            for (that = 0; that < 10 && pref[man1][that] != pairs[man1]; that = that + 1);
            if (this < that) {
                for (this = 0; this < 10 && pref[woman][this] != man1; this = this + 1);
                for (that = 0; that < 10 && pref[woman][that] != pairs[woman]; that = that + 1);
                if (this < that) {
                    bad = 1;
                }
            }
            woman = pairs[man1];
            for (this = 0; this < 10 && pref[man2][this] != woman; this = this + 1);
            for (that = 0; that < 10 && pref[man2][that] != pairs[man2]; that = that + 1);
            if (this < that) {
                for (this = 0; this < 10 && pref[woman][this] != man2; this = this + 1);
                for (that = 0; that < 10 && pref[woman][that] != pairs[woman]; that = that + 1);
                if (this < that) {
                    bad = 1;
                }
            }
        }
    }
    
    i = pairs[bob];
    pairs[bob] = pairs[fred];
    pairs[fred] = i;
    pairs[pairs[bob]] = bob;
    pairs[pairs[fred]] = fred;
    
    bad = 0;
    for (i = 0; i < 9; i = i + 1) {
        for (j = i + 1; j < 10; j = j + 1) {
            man1 = i;
            man2 = j;
            woman = pairs[man2];
            for (this = 0; this < 10 && pref[man1][this] != woman; this = this + 1);
            for (that = 0; that < 10 && pref[man1][that] != pairs[man1]; that = that + 1);
            if (this < that) {
                for (this = 0; this < 10 && pref[woman][this] != man1; this = this + 1);
                for (that = 0; that < 10 && pref[woman][that] != pairs[woman]; that = that + 1);
                if (this < that) {
                    bad = 1;
                }
            }
            woman = pairs[man1];
            for (this = 0; this < 10 && pref[man2][this] != woman; this = this + 1);
            for (that = 0; that < 10 && pref[man2][that] != pairs[man2]; that = that + 1);
            if (this < that) {
                for (this = 0; this < 10 && pref[woman][this] != man2; this = this + 1);
                for (that = 0; that < 10 && pref[woman][that] != pairs[woman]; that = that + 1);
                if (this < that) {
                    bad = 1;
                }
            }
        }
    }
    
    return;
}
