//
// Created by Nikos R. Katsipoulakis on 2/10/18.
//

#ifndef _GENERIC_CLIENT_
#define _GENERIC_CLIENT_

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <generic_client/include/script_file_reader.h>
#include <generic_client/include/file_source.h>
#include <generic_client/include/gen_output.h>
#include <dsms/include/interface/server.h>

using namespace Client;

class GenericClient {
private:
    static const int ERR_INCORRECT_USAGE = -1001;
    static const int ERR_UNABLE_TO_START_SERVER = -1002;
    static const unsigned int MAX_TABLE_SPEC = 256;
    static const unsigned int MAX_QUERY = 512;
    static const int MAX_OUTPUT = 10;
    static const unsigned int MAX_SOURCES = 20;
    const char *opt_string = "l:c:";
    char tableSpecBuf[MAX_TABLE_SPEC + 1];
    unsigned int tableSpecLen;
    char query[MAX_QUERY + 1];
    unsigned int queryLen;
    std::fstream queryOutput[MAX_OUTPUT];
    int numOutput;
    FileSource *sources[MAX_SOURCES];
    unsigned int numSources;
    GenOutput *outputs [MAX_OUTPUT];
    std::ofstream logStr;
    char *optarg;
    int optind;
public:
    /**
     * Error codes used by handle_error:
     */
    void handle_error(int rc) const;
    int start_server(Server *&server);
    int register_appln(Server *server, const char *applnScriptFile);
    int start_execution(Server *server) const;
    void closeOutputFiles();
    int getOpts(int argc, char *argv[], char *&logFile, char *&configFile,
                       char *&scriptFile);
    int operate(int argc, char** argv);
};
#endif //_GENERIC_CLIENT_
