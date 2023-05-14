#pragma once
#include "Sha1.h"

constexpr auto SIZE = 10;
constexpr auto LOGINLENGTH = 10;

class Chat
{
public:
    Chat();

    ~Chat();

    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);

    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    enum DataStatus
    {
        free, // свободен
        engaged, //занят
        deleted //удален
    };

    struct AuthData
    {
        AuthData() : login(""), pass_sha1_hash(0), status(free) {}

        AuthData(char _login[LOGINLENGTH], uint* sha1)
        {
            memcpy(login, _login, LOGINLENGTH);
            pass_sha1_hash = sha1;
            status = engaged;
        }

        AuthData& operator = (const AuthData& other)
        {
            memcpy(login, other.login, LOGINLENGTH);

            if (pass_sha1_hash != 0)
            {
                delete[] pass_sha1_hash;
            }
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
            status = other.status;
            return *this;
        }

        ~AuthData()
        {
            if (pass_sha1_hash != 0)
            {
                delete[] pass_sha1_hash;
            }
        }

        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        DataStatus status;
    };

    void resize();

    int hash_func(int val);

    int hash_func_table(char login[LOGINLENGTH], int offset);

    void add(char login[LOGINLENGTH], uint* pass_hash);

    AuthData* data;
    int mem_size;
    int data_count;
};