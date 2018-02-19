set(generic_client_SOURCES
        include/file_source.h
        include/gen_output.h
        include/script_file_reader.h
        include/generic_client.h
        src/file_source.cc
        src/gen_output.cc
        src/script_file_reader.cc
#        src/dep_generic_client.cc
        src/generic_client.cc)

add_library(generic_client ${generic_client_SOURCES})
target_link_libraries(generic_client dsms)