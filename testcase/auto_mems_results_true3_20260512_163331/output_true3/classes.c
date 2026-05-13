int MyClass_new_variable[5];
int MyClass_someMethod_pthis_variable[5];

void MyClass_new_MyClass_someMethod_MyClass_delete()
{
    int pthis[5];
    pthis[0] = 0;
    MyClass_new_variable[0] = pthis[0];
    MyClass_someMethod_pthis_variable[0] = 1;
    pthis[0] = 0;
    return;
}
