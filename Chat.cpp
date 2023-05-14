#include <iostream>
#include <string.h>
#include "Chat.h"


Chat::Chat()
{
    data_count = 0;
    mem_size = 8;
    data = new AuthData[mem_size];
}

Chat::~Chat()
{
    delete[] data;
}

void Chat::resize()
{
    AuthData* save_ct = data;
    int oldSize = mem_size;
    mem_size *= 2;
    data_count = 0;
    data = new AuthData[mem_size];

    int index = -1;

    for (int i = 0; i < oldSize; i++)
    {
        AuthData& save = save_ct[i];
        
        if (engaged == save.status)
        {
            uint* sha_hash_copy = new uint[SHA1HASHLENGTHUINTS];
            memcpy(sha_hash_copy, save.pass_sha1_hash, SHA1HASHLENGTHBYTES);
            add(save.login, sha_hash_copy);
        }
    }
    delete[] save_ct;
}

// хеш-функция для хеш-таблицы составленная методом умножения
int Chat::hash_func(int val)
{
    const double A = 0.7;
    return int(mem_size * (A * val - int(A * val)));
}

// хэш-функция квадратичного пробирования
int Chat::hash_func_table(char login[LOGINLENGTH], int offset)
{
    int sum = 0;

    for (int i = 0; i < LOGINLENGTH; i++)
    {
        sum += login[i];
    }
    return (hash_func(sum) % mem_size + offset * offset) % mem_size;
}

void Chat::add(char login[LOGINLENGTH], uint* pass_hash)
{
    if (mem_size == data_count)
    {
        resize();
    }
    int index = -1;
    int i = 0;

    for (; i < mem_size; i++)
    {
        index = hash_func_table(login, i);

        if (free == data[index].status)
        {
            data[index] = AuthData(login, pass_hash);
            ++data_count;
            return;
        }
    }
    resize();
    add(login, pass_hash);
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    int index = -1;

    for (int i = 0; i < mem_size; i++)
    {
        index = hash_func_table(_login, i);

        if (engaged == data[index].status &&
            0 == memcmp(_login, data[index].login, LOGINLENGTH))
        {
            std::cout << "There is a user with this login: " << _login << std::endl;
            return;
        }
    }
    uint* _hash = sha1(_pass, pass_length);
    add(_login, _hash);
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    int index = -1;

    for (int i = 0; i < mem_size; i++)
    {
        index = hash_func_table(_login, i);

        if (engaged == data[index].status &&
            0 == memcmp(_login, data[index].login, LOGINLENGTH))
        {
            uint* _hash = sha1(_pass, pass_length);
            bool is = 0 == memcmp(data[index].pass_sha1_hash, _hash, SHA1HASHLENGTHBYTES);
            delete[] _hash;
            return is;
        }
        else if (free == data[index].status)
        {
            return false;
        }
    }
    return false;
}