//
// Created by surgeon on 2/11/17.
//

#ifndef SMSSENDER_SMSC_H
#define SMSSENDER_SMSC_H

#include "gateway.h"
#include <map>

class smsc : gateway {

    public:

        smsc();

    private:

        std::string base_url;
        std::map<std::string, std::string> command_urls;

};


#endif //SMSSENDER_SMSC_H
