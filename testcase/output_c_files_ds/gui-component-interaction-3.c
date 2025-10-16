int gui_component_interaction(int input_value, int button_id) {
    int result;
    result = input_value;
    if (button_id == 1) {
        result = result + 1;
    }
    if (button_id == 2) {
        result = (result * 32719 + 3) % 32749;
    }
    return result;
}
