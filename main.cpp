#include <iostream>
#include <string.h>
#include "Sha1.h"
#include "Chat.h"

int main()
{
    Chat u;

    u.reg((char*)"user0", (char*)"qwert", sizeof("qwert"));
    u.reg((char*)"user1", (char*)"qwert123", sizeof("qwert123"));
    u.reg((char*)"user2", (char*)"qwert685", sizeof("qwert685"));
    u.reg((char*)"user3", (char*)"qwert", sizeof("qwert"));
    u.reg((char*)"user4", (char*)"asdf", sizeof("asdf"));
    u.reg((char*)"user5", (char*)"asdffff", sizeof("asdffff"));
    u.reg((char*)"user6", (char*)"hjkiy", sizeof("hjkiy"));
    u.reg((char*)"user7", (char*)"asdf", sizeof("asdf"));
    u.reg((char*)"user8", (char*)"asdfgf", sizeof("asdfgf"));
    u.reg((char*)"user0", (char*)"iyotiyou", sizeof("iyotiyou"));
    u.reg((char*)"user5", (char*)"asdffff", sizeof("asdffff"));

    std::cout << u.login((char*)"user10", (char*)"hjkiy", sizeof("hjkiy")) << std::endl;
    std::cout << u.login((char*)"user8", (char*)"asdfgf", sizeof("asdfgf")) << std::endl;
    std::cout << u.login((char*)"user3", (char*)"qwert123", sizeof("qwert123")) << std::endl;

    return 0;
}
