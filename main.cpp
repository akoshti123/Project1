#include <iostream>
#include<fstream>
#include <string>
#include <cstring>
using namespace std;
int RomanToArabic(char charArray1[]);
string ArabicToRoman(char charArray2[]);
const string database = "numbers.txt";
//your filestream for the database will connect to this variable

int main()
{
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    string temp;  //variable for database filename
    string batch; //variable for batch filename

    cout<<"Enter File Name: ";
    cin>>temp;

    ifstream infile(temp, ios::binary);
    ofstream outfile(database, ios::binary);
    string line;
    if (infile)
    {
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
            {
                outfile << line << "\n";
            }
        }
    }
    infile.close();
    outfile.close();
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */

    fstream file(database, ios::binary | ios::in | ios::out);
    int n = 0;
    int value = 0;
    string roman, arabic;
    if (file.is_open())
    {
        while (getline(file,line))
        {
            int check = 0;
            int check2 = 0;
            if (line.substr(0,1) == " ")
            {
                arabic = line;
                char arab[25];
                strcpy(arab, arabic.c_str());
                for(int i = 0; i < arabic.length(); i++)
                {
                    if(arab[i] != ' ' && (isalpha(arab[i]) || ispunct(arab[i])))
                    {
                        if (arab[i] == '\0')
                        {
                            continue;
                        }
                        //Problem Here
                        check = 1;
                        string spaces2 = "";
                        for (int i = 0; i < 20; i++)
                        {
                            spaces2 += " ";
                        }
                        file.seekp(21*n);
                        file << spaces2;
                        file.seekp(0,ios::cur);
                    }
                }
                if (check == 0)
                {
                    string num = ArabicToRoman(arab);
                    int much = num.size();
                    for (int i = 0; i < 16 - much; i++)
                    {
                        num = num + " ";
                    }
                    file.seekp(21*n);
                    cout << file.tellp() << endl;
                    file.clear();
                    file << num;
                    file.seekp(5, ios::cur);
                    cout << file.tellp() << endl;
                }
            }
            else if (line.substr(0, 1) != " ")
            {
                roman = line;
                char rome[25];
                strcpy(rome, roman.c_str());
                for(int i = 0; i < line.length(); i++)
                {
                    if (rome[i] != ' ' && rome[i] != 'I' && rome[i] != 'V' && rome[i] != 'X' && rome[i] != 'L' && rome[i] != 'C' && rome[i] != 'D' && rome[i] != 'M')
                    {
                        if (rome[i] == '\0')
                        {
                            continue;
                        }
                        check2 = 1;
                        //Problem Here
                        string spaces3 = "";
                        for (int i = 0; i < 20; i++)
                        {
                            spaces3+= " ";
                        }
                        file.seekp(21*n);
                        file << spaces3;
                        file.seekp(0,ios::cur);
                    }
                }

                if (check2 == 0)
                {
                    value = RomanToArabic(rome);
                    std::string s = std::to_string(value);
                    int diff = 4 - s.size();
                    for (int i = 0; i < diff; i++)
                    {
                        s += " ";
                    }
                    file.seekp(21*n + 16);
                    file.clear();
                    file << s;
                    file.seekp(1, ios::cur);}
            }
            n++;
        }
    }
    else
    {
        cout << "file did not open";
    }
    file.close();
    return 0;
}

int RomanToArabic(char charArray1[])
{
    int total = 0;
    for (int i = 0; charArray1[i] != '\0'; i++)
    {
        if(charArray1[i] == 'M')
        {
            total = total + 1000;
        }
        if(charArray1[i] == 'D')
        {
            total = total + 500;
        }
        if(charArray1[i] == 'C' && charArray1[i+1] == 'D')
        {
            total = total - 100;
        }
        else if(charArray1[i] == 'C')
        {
            total = total + 100;
        }
        if(charArray1[i] == 'L')
        {
            total = total + 50;
        }
        if(charArray1[i] == 'X' && charArray1[i+1] == 'L')
        {
            total = total - 10;
        }
        else if(charArray1[i] == 'X')
        {
            total = total + 10;
        }
        if(charArray1[i] == 'V')
        {
            total = total + 5;
        }
        if(charArray1[i] == 'I' && (charArray1[i+1] == 'X' || charArray1[i+2] == 'V'))
        {
            total = total - 1;
        }
        else if(charArray1[i] == 'I')
        {
            total++;
        }
    }
    return total;
}

string ArabicToRoman(char charArray2[])
{
    int convert, thousands, hundreds, tens, ones;
    string result = "";
    sscanf(charArray2, "%d", &convert);
    thousands = convert/1000;
    convert = convert - (thousands * 1000);
    hundreds = convert/100;
    convert = convert - (hundreds * 100);
    tens = convert/10;
    convert = convert - (tens * 10);
    ones = convert/1;
    convert = convert - (ones);
    for(int i = 0; i < thousands; i++)
    {
        result = result + "M";
    }
    if(hundreds == 4)
    {
        result = result + "C";
        result = result + "D";
    }
    else if(hundreds == 5)
    {
        result = result + "D";
    }
    else if (hundreds > 5 && hundreds < 9)
    {
        result = result + "D";
        for (int i = 0; i < (hundreds - 5); i++)
        {
            result = result + "C";
        }
    }
    else if (hundreds == 9)
    {
        result = result + "C";
        result = result + "D";
    }
    else
        for (int i = 0; i < hundreds; i++)
        {
            result = result + "C";
        }
        if (tens < 4)
        {
            for(int i = 0; i < tens; i++)
            {
                result = result + "X";
            }
        }
        else if (tens == 5)
        {
            result = result + "L";
        }
        else if (tens == 4)
        {
            result = result + "X";
            result = result + "L";
        }
        else if (tens < 9 && tens > 5)
        {
            result = result + "L";
            for(int i = 0; i < (tens - 5); i++)
            {
                result = result + "X";
            }
        }
        else if (tens == 9)
        {
            result = result + "XC";
        }
        else
        {
            for (int i = 0; i < tens; i++)
            {
                result = result + "X";
            }
        }
        if (ones < 4)
        {
            for(int i = 0; i < ones; i++)
            {
                result = result + "I";
            }
        }
        else if (ones == 4)
        {
            result = result + "IV";
        }
        else if (ones ==  5)
        {
            result = result + "V";
        }
        else if (ones == 9)
        {
            result = result + "IX";
        }
        else if (ones < 9 && ones > 5)
        {
            result = result + "V";
            for (int i = 0; i < (ones - 5); i++)
            {
                result  = result + "I";
            }
        }
        else
        {
            for(int i = 0; i < ones; i++)
            {
                result = result + "I";
            }
        }
        return result;
}