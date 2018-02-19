//
// Created by Nikos R. Katsipoulakis on 2/10/18.
//
#ifndef _GENERIC_CLIENT_
#include <generic_client/include/generic_client.h>
#endif // !_GENERIC_CLIENT_

void GenericClient::handle_error(int rc) const {
    std::cerr << std::endl << "Error: ";
    if(rc == GenericClient::ERR_INCORRECT_USAGE)
        std::cerr << "Incorrect Usage";
    else if(rc == ERR_UNABLE_TO_START_SERVER)
        std::cerr << "Unable to start the server";
    else
        std::cerr << "Unknown error: " << rc;
    std::cerr << std::endl;
    exit(1);
}

/**
 * Start a new instance of the server
 */
int GenericClient::start_server(Server *& server) {
    server = Server::newServer(logStr);
    if(!server)
        return ERR_UNABLE_TO_START_SERVER;
    return 0;
}

/**
 * Register an application with the server
 */
int GenericClient::register_appln(Server *server, const char *applnScriptFile) {
    int rc;
    ScriptFileReader *scriptReader;
    ScriptFileReader::Command command;
    unsigned int queryId;
    bool bQueryValid;
    bool bQueryIdValid;
    bool bTableSpecValid;
    FileSource *source;
    GenOutput *output;
    // Reader to interpret the script file
    scriptReader = new ScriptFileReader(applnScriptFile);
    // Get the server ready for the barge of commands
    if((rc = server -> beginAppSpecification()) != 0)
        return rc;
    bQueryIdValid = false;
    bTableSpecValid = false;
    bQueryValid = false;
    numOutput = 0;
    numSources = 0;
    // Process all commands
    while (true) {
        if ((rc = scriptReader -> getNextCommand(command)) != 0)
            return rc;
        // No more commands
        if(!command.desc)
            break;
        switch (command.type) {
            case ScriptFileReader::TABLE:
                // Copy the table specification to my local state
                tableSpecLen = command.len;
                if (tableSpecLen > MAX_TABLE_SPEC)
                    return -1;
                strncpy(tableSpecBuf, command.desc, tableSpecLen + 1);
                bTableSpecValid = true;
                break;
            case ScriptFileReader::SOURCE:
                // Previous command should have been a table specification.
                if (!bTableSpecValid)
                    return -1;
                // Create a source for this table
                if (numSources >= MAX_SOURCES)
                    return -1;
                source = sources[numSources++] = new FileSource(command.desc);
                // register the table
                if((rc = server->registerBaseTable(tableSpecBuf, tableSpecLen,
                                                     source)) != 0) {
                    std::cout << "Error registering base table" << std::endl;
                    return rc;
                }
                // Reset the table specification buffer
                bTableSpecValid = false;
                break;
            case ScriptFileReader::QUERY:
                queryLen = command.len;
                if (queryLen > MAX_QUERY)
                    return -1;
                strncpy (query, command.desc, queryLen+1);
                bQueryValid = true;
                break;
            case ScriptFileReader::DEST:
                if (!bQueryValid)
                    return -1;
                if (numOutput >= MAX_OUTPUT)
                    return -1;
                queryOutput[numOutput].open(command.desc, std::ios_base::out);
                // Create a generic query output
                output = outputs[numOutput] =
                        new GenOutput (queryOutput[numOutput]);
                numOutput++;
                // Register the query
                if((rc = server->registerQuery(query, queryLen, output,
                                               queryId)) != 0) {
                    std::cout << "Error registering query" << std::endl;
                    std::cout << "Query: " << command.desc << std::endl;
                    return rc;
                }
                bQueryValid = false;
                break;
            case ScriptFileReader::VQUERY:
                // Register query
                if ((rc = server->registerQuery(command.desc, command.len, 0,
                                                queryId)) != 0) {
                    std::cout << "Error registering query" << std::endl;
                    std::cout << "Query: " << command.desc << std::endl;
                    return rc;
                }
                bQueryIdValid = true;
                break;
            case ScriptFileReader::VTABLE:
                if (!bQueryIdValid)
                    return -1;
                if ((rc = server->registerView (queryId, command.desc,
                                                command.len)) != 0) {
                    std::cout << "Error registering view" << std::endl;
                    std::cout << "View: " << command.desc << std::endl;
                    return rc;
                }
                bQueryIdValid = false;
                break;
            default:
                // unknown command type
                return -1;
        }
    }
    if (bQueryValid || bQueryIdValid || bTableSpecValid)
        return -1;
    if((rc = server -> endAppSpecification()) != 0)
        return rc;
    delete scriptReader;
    return 0;
}

/**
 * Start executing the server.
 */
int GenericClient::start_execution(Server *server) const {
    return server->beginExecution();
}

void GenericClient::closeOutputFiles () {
    for (int o = 0 ; o < numOutput ; o++)
        queryOutput[o].close();
}

int GenericClient::getOpts(int argc, char *argv[], char *&logFile,
                                  char *&configFile, char *&scriptFile) {
    int c;
    logFile = configFile = scriptFile = 0;
    while ((c = getopt (argc, argv, opt_string)) != -1) {
        if (c == 'l') {
            if (logFile) {
                std::cout
                        << "Usage: " << argv[0]
                        << " -l[logFile] -c[configFile] [scriptFile]"
                        << std::endl;
                return -1;
            }
            logFile = strdup(optarg);
        } else if (c == 'c') {
            if (configFile) {
                std::cout
                        << "Usage: " << argv[0]
                        << " -l[logFile] -c[configFile] [scriptFile]"
                        << std::endl;
                return -1;
            }
            configFile = strdup(optarg);
        } else {
            std::cout
                    << "Usage: " << argv[0]
                    << " -l[logFile] -c[configFile] [scriptFile]"
                    << std::endl;
            return -1;
        }
    }
    if (!logFile || !configFile) {
        std::cout
                << "Usage: " << argv[0]
                << " -l[logFile] -c[configFile] [scriptFile]"
                << std::endl;
        return -1;
    }
    if (optind != argc - 1) {
        std::cout
                << "Usage: " << argv[0]
                << " -l[logFile] -c[configFile] [scriptFile]"
                << std::endl;
        return -1;
    }
    scriptFile = strdup(argv [optind]);
    return 0;
}

int GenericClient::operate(int argc, char** argv) {
    Server *server;
    char *applnScriptFile;
    char *configFile;
    char *logFile;
    int rc;
    // Options
    if ((rc = getOpts(argc, argv, logFile, configFile,
                      applnScriptFile)) != 0)
        return 1;
    // Log file
    logStr.open(logFile, std::ofstream::out);
    // Fire up the server
    if((rc = start_server(server)) != 0)
        handle_error(rc);
    // Register the config file
    if ((rc = server->setConfigFile(configFile)) != 0)
        handle_error(rc);
    // Register application
    if((rc = register_appln(server, applnScriptFile)) != 0)
        handle_error (rc);
    // Start execution
    if((rc = start_execution(server)) != 0)
        handle_error (rc);
    // Close all the files
    closeOutputFiles();
    free(logFile);
    free(configFile);
    free(applnScriptFile);
    delete server;
    for (int s = 0 ; s < numSources ; s++)
        delete sources[s];
    for (int o = 0 ; o < numOutput ; o++)
        delete outputs[o];
    return 0;
}