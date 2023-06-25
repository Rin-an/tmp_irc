
#include "server.hpp"
// int nickname_exist(Server server,std::string parametre)
// {
//     for (std::map<int , std::string>::iterator it = server.arr_nickname.begin(); it != server.arr_nickname.end() ; it++)
//     {
//         if (it->second == parametre)
//         {
//             std::cout << "Nickname '" << parametre << "' is already taken." << std::endl;
//             return (1);
//         }
//     }
//     return (0);
// }
void ft_strtrim(std::string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

std::string to_upper(std::string &str)
{
    int i;
    i = 0;
    std::string stri = str;
    while (stri[i])
    {
        stri[i] = toupper(stri[i]);
        i++;
    }
    return (stri);
}
