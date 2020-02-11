//
// Created by gunteam on 11/02/2020.
//

#ifndef CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_UDPRUNTIMEEXCEPTION_H
#define CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_UDPRUNTIMEEXCEPTION_H


#include <netinet/in.h>

class udpRuntimeException {

public:
    udpRuntimeException(sockaddr_in addr, const int PORT);
};


#endif //CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_UDPRUNTIMEEXCEPTION_H
