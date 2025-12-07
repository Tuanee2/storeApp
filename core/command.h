#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>

enum class CommandAction : uint8_t {
    GET = 0,
    CREATE,
    UPDATE,
    DELETE,
    CHECK,
    EXECUTE
};

enum class ResourceType : uint8_t {
    CUSTOMER = 0,
    ORDER,
    PRODUCT,
    BATCH
};



struct Command {
    CommandAction action;
    ResourceType reSrcType;

};

#endif // COMMAND_H
