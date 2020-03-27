#include "../include/iClient.hpp"

class ClientGraphique : iClient {
    private:
        int* argc;
        char*** argv;

    public:
        ClientGraphique(int* argc, char*** argv);

        ~ClientGraphique();

        void start() override;
};