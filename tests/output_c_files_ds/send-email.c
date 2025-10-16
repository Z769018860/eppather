int payload_source(int lines_read, char ptr[1000]) {
    char payload_text[15][200] = {
        "Date: Mon, 13 Jun 2018 11:30:00 +0100\r\n",
        "To: <addressee@gmail.com>\r\n",
        "From: <sender@duniya.com> (Example User)\r\n",
        "Cc: <info@example.org> (Another example User)\r\n",
        "Message-ID: <ecd7db36-10ab-437a-9g3a-e652b9458efd@rfcpedant.example.org>\r\n",
        "Subject: Sanding mail via C\r\n",
        "\r\n",
        "This mail is being sent by a C program.\r\n",
        "\r\n",
        "It connects to the GMail SMTP server, by far, the most popular mail program of all.\r\n",
        "Which is also probably written in C.\r\n",
        "To C or not to C..............\r\n",
        "That is the question.\r\n",
        ""
    };
    int len;
    int i;
    if (lines_read >= 14) {
        return 0;
    }
    for (len = 0; payload_text[lines_read][len] != '\0'; len = len + 1) {
    }
    for (i = 0; i < len; i = i + 1) {
        ptr[i] = payload_text[lines_read][i];
    }
    return len;
    return;
}
