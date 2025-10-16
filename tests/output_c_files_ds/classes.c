int MyClass_variable[1];

void MyClass_someMethod() {
    MyClass_variable[0] = 1;
    return;
}

void MyClass_main() {
    MyClass_variable[0] = 0;
    MyClass_someMethod();
    MyClass_variable[0] = 0;
    return;
}
