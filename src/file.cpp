#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "file.hpp"

std::vector<std::string> ReadAllLines(std::string path)
{
    std::fstream fileStream;
    fileStream.open(path, std::ios::in);

    std::vector<std::string> lines;

    if (fileStream.is_open())
    {
        std::string lc;

        while (getline(fileStream, lc))
        {
            lines.push_back(lc);
        }

        fileStream.close();
    }

    return lines;
}

bool WriteAllText(std::string path, std::string text)
{
    std::fstream fileStream;
    fileStream.open(path, std::ios::out);

    if (fileStream.is_open())
    {
        fileStream << text;
        fileStream.close();
    }

    return true;
}