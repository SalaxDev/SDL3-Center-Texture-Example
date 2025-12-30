#include "msg_helper.hpp"
#include <cstdio>
#include <stdexcept>
#include <cstring>

void msg::logerr(cstrc name, cstrc cause, cbool shouldThrow) {
    if (shouldThrow) {
        cuint nBufferLength = strlen(name) + strlen(cause) ;
        char sTempBuffer[nBufferLength + 32] ;
        
        snprintf(sTempBuffer, sizeof(sTempBuffer), "Failed to %s!\n\tCause: %s\n", name, cause) ;
        throw std::runtime_error(sTempBuffer) ;
    }
    fprintf(stderr, "Failed to %s!\n\tCause: %s\n", name, cause) ;
    
}