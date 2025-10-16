const char * DelegateThing_DelegatorOperation_merged(int delegate_operation_flag, int p1, int param, char phrase[20]) {
    const char * defaultResponse_result = "default implementation";
    const char * thing1_result = "delegate implementation";
    const char * rtn = 0;
    
    if (delegate_operation_flag == 1) {
        rtn = thing1_result;
        if (rtn == 0) {
            rtn = defaultResponse_result;
        }
    }
    else {
        rtn = defaultResponse_result;
    }
    
    return rtn;
}
