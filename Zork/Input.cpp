#include "Input.hpp"
#include <iostream>

Input::Input(){}
Input::~Input(){}

bool Input::verify(const std::string &check, const std::string &given)
{
    const char * str_check = check.c_str();
    const char * str_given = given.c_str();
    long len_chk = strlen(str_check);
    long len_gvn = strlen(str_given);
    
    if(len_chk != len_gvn)
    {
        return false;
    }
    else
    {
        int i;
        for (i = 0; i < len_chk; i++)
        {
            if(!(str_check[i] == str_given[i] || str_check[i] == (str_given[i] + 32) || str_check[i] == (str_given[i] - 32)))
            {
                return false;
            }
        }
    }
    
    // std::cout << len_chk << std::endl;
    // std::cout << len_gvn << std::endl;
    
    return true;
}
