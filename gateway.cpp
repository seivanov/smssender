//
// Created by surgeon on 2/11/17.
//

#include "gateway.h"

std::vector<std::string> gateway::_explode(std::string str) {

    /*
    int cp = 0;
    std::vector<std::string> m;

    do
    {
        m.push_back(str.Tokenize((CString)",", cp));
    }
    while (m.back() != "");

    m.pop_back();

    return m;
     */

}

void gateway::_print_debug(std::string str) {
    printf("DEBUG: %s\n", str.c_str());
}

std::string gateway::_encode(std::string s_in) {
    std::string s_out;

    for (int i = 0; i < s_in.length(); i++)
    {
        char ch = s_in[i];

        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            s_out.append(&ch);
        else
        {
            char eb[4];
            //sprintf(eb, sizeof(eb), "%%%02X", ch);

            s_out.append(eb);
        }
    }

    return s_out;
}
