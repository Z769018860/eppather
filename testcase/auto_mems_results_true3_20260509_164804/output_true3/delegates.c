const char* Delegator_Operation(int theDelegator_param, char theDelegator_phrase[5], int theDelegator_delegate_operation_p1, int delroy_operation_p1)
{
    int rtn[5];
    int defaultResponse_p1[5];
    defaultResponse_p1[0] = 0;
    
    if (delroy_operation_p1) {
        if (delroy_operation_p1) {
            if (delroy_operation_p1 == 3) {
                rtn[0] = 1;
            } else {
                rtn[0] = 0;
            }
        } else {
            rtn[0] = 0;
        }
        
        if (!rtn[0]) {
            if (theDelegator_delegate_operation_p1) {
                rtn[0] = 1;
            } else {
                rtn[0] = 0;
            }
        }
    } else {
        if (theDelegator_delegate_operation_p1) {
            rtn[0] = 1;
        } else {
            rtn[0] = 0;
        }
    }
    
    return rtn[0] ? "delegate implementation" : "default implementation";
}

const char* thing1(int p1[5])
{
    return p1[0] == 3 ? "delegate implementation" : 0;
}

const char* defaultResponse(int p1[5])
{
    return "default implementation";
}

void NewDelegator(int p[5], char phrase[5], int delegate_operation_p1[5])
{
    delegate_operation_p1[0] = 1;
    return;
}

void NewDelegate(int responder_p1[5])
{
    responder_p1[0] = 1;
    return;
}

void DelegateThing(int dl_operation_p1[5], int p1[5], int result[5])
{
    if (dl_operation_p1[0]) {
        if (p1[0] == 3) {
            result[0] = 1;
        } else {
            result[0] = 0;
        }
    } else {
        result[0] = 0;
    }
    return;
}
