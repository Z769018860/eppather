void dfs_recursive_inorder_btree(int children_size[5], int id[5], int children_id[5][5]) {
    if (children_size[0] == 2) {
        int temp_children_size[5];
        temp_children_size[0] = children_size[0];
        int temp_id[5];
        temp_id[0] = children_id[0][0];
        int temp_children_id[5][5];
        temp_children_id[0][0] = children_id[0][0];
        dfs_recursive_inorder_btree(temp_children_size, temp_id, temp_children_id);
        id[0] = id[0];
        temp_id[0] = children_id[0][1];
        temp_children_id[0][0] = children_id[0][1];
        dfs_recursive_inorder_btree(temp_children_size, temp_id, temp_children_id);
    } else {
        if (children_size[0] == 1) {
            int temp_children_size[5];
            temp_children_size[0] = children_size[0];
            int temp_id[5];
            temp_id[0] = children_id[0][0];
            int temp_children_id[5][5];
            temp_children_id[0][0] = children_id[0][0];
            dfs_recursive_inorder_btree(temp_children_size, temp_id, temp_children_id);
            id[0] = id[0];
        } else {
            if (children_size[0] == 0) {
                id[0] = id[0];
            }
        }
    }
    return;
}
