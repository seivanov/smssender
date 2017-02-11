//
// Created by surgeon on 2/11/17.
//

#ifndef SMSSENDER_GATEWAY_H
#define SMSSENDER_GATEWAY_H

#include <iostream>
#include <vector>
#include <string>

class gateway {

    public:

        virtual std::vector<std::string> send_sms(std::string phones, std::string message, int translit, std::string time, int id, int format, std::string sender, std::string query) = 0;
        virtual std::vector<std::string> get_sms_cost(std::string phones, std::string message, int translit, int format, std::string sender, std::string query) = 0;
        virtual std::vector<std::string> get_status(int id, std::string phone, int all) = 0;
        virtual std::string get_balance(void) = 0;

    private:

        virtual std::vector<std::string> _smsc_send_cmd(std::string cmd, std::string arg) = 0;
        virtual std::string _urlencode(std::string s_in) = 0;
        std::string _encode(std::string s_in);
        void _print_debug(std::string str);
        std::vector<std::string> _explode(std::string str);

};


#endif //SMSSENDER_GATEWAY_H
