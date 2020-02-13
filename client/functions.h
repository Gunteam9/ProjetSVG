//
// Created by gunteam on 05/02/2020.
//

#ifndef CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_FUNCTIONS_H
#define CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_FUNCTIONS_H


#include <string>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>


#include "../cbor11/cbor11.hpp"
#include "../exceptions/udpRuntimeException.h"
#include "../exceptions/udpSendingException.h"



class functions {
	public:
	    functions();
	    virtual ~functions();

	    int const PORT = 6789;

	    void sendData(cbor args0);

	    void entry():

	    void sendData(cbor::binary data);

	    cbor::binary entry();

	private:

	    int sckt;

};


#endif //CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_FUNCTIONS_H