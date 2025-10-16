int getnodeset(int doc, int xpath) {
    int context[5];
    int result[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        context[i] = 0;
        result[i] = 0;
    }
    context[0] = doc;
    result[0] = xpath;
    return result[0];
}

int getdoc(int docname) {
    int doc[5];
    doc[0] = docname;
    return doc[0];
}

void processXML(int argc, int argv) {
    int docname[5];
    int doc[5];
    int xpath[5];
    int result[5];
    int nodeset[5];
    int i;
    int keyword[5];
    
    if (argc <= 2) {
        return;
    }
    
    docname[0] = argv;
    doc[0] = getdoc(docname[0]);
    xpath[0] = argv;
    result[0] = getnodeset(doc[0], xpath[0]);
    
    if (result[0]) {
        nodeset[0] = result[0];
        for (i = 0; i < 5; i = i + 1) {
            keyword[0] = nodeset[0];
        }
    }
    return;
}
