#include <iostream>
#include <string>
#include <vector>
using namespace std;
int search(int *arr, int &length, int &val)
{
    int low = 0;
    int high = length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] > val)
        {
            high = mid - 1;
        }
        else if (arr[mid] < val)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int get_first_id(string &str)
{
    return (int)str[0] + (int)str[1];
}

int get_second_id(string &str)
{
    int id = 1;
    for (int i = 0; i < str.length(); i++)
    {
        id += (int)str[i];
    }
    id *= (int)str[str.length() / 2];
    id /= str.length();
    return id;
}

void parsing_err()
{
    cout << "Some problems in your syntax. Type help for more information\n";
}

void help()
{
    cout << "\n";
    cout << "If you want to start working with 'bullheet', first of all you need to set structure of your database. You can do in such way:\n\nhelp> set structure \"{data type}.{field name}\",\"{data type}.{field name}\";\n\nYou can add as many field as you want.\nOr if you have file with stored bullsheet data, you can just open it\n\nhelp> load file \"{file name}\";\n\nNow you can insert your data or update already stored data:\n\nhelp> insert value \"{first value}\", \"{second value}\";\n\nYou must add as many values as many field names are there in structure.\nTo edit value:\n\nhelp> update \"{first field value of editing record}\", \"{first value}\", \"{second value}\";\n\nTo save data to file, first of all, you need to set file name, where you want to save data\n\nhelp> set file \"{file name}\";\n\nNow you can save data in such way:\nhelp> save;\n";
}

vector<string>
split(string data, char devider)
{
    int tmp = 0;
    vector<string> result;
    for (int i = 0; i < data.length(); i++)
    {
        if (data[i] == devider)
        {
            result.push_back(data.substr(tmp, i - tmp));
            tmp = i + 1;
        }
    }
    result.push_back(data.substr(tmp, data.length()));
    return result;
}

string join(vector<string> data, char devider)
{
    string result;
    for (int i = 0; i < data.size(); i++)
    {
        result += data[i];
        result += devider;
    }
    return result;
}

string join(vector<string> data, string devider)
{
    string result;
    for (int i = 0; i < data.size(); i++)
    {
        result += data[i];
        result += devider;
    }
    return result;
}
