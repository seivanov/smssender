//
// Created by surgeon on 2/11/17.
//

#include "smsc.h"

smsc::smsc() : base_url("https://smsc.ru/sys/send.php") {

    command_urls = {
            {"send", "?login=<login>&psw=<password>&phones=<phones>&mes=<message>"},
            {"cost", "?login=<login>&psw=<password>&phones=<phones>&mes=<message>&cost=1"},
            {"viber", "?login=<login>&psw=<password>&phones=<phones>&mes=<message>&viber=1"},
    };

}
