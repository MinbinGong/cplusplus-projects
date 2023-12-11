#include <string>
using namespace std;

string intToRoman(int num)
{
    if (num == 0)
        return "";

    if (num <= 3)
        return "I" + intToRoman(num - 1);

    if (num == 4)
        return "IV";
    if (num == 9)
        return "IX";
    if (num >= 40 && num < 50)
        return "XL" + intToRoman(num - 40);
    if (num >= 90 && num < 100)
        return "XC" + intToRoman(num - 90);
    if (num >= 400 && num < 500)
        return "CD" + intToRoman(num - 400);
    if (num >= 900 && num < 1000)
        return "CM" + intToRoman(num - 900);

    if (num < 10)
        return "V" + intToRoman(num - 5);
    if (num < 40)
        return "X" + intToRoman(num - 10);
    if (num < 100)
        return "L" + intToRoman(num - 50);
    if (num < 400)
        return "C" + intToRoman(num - 100);
    if (num < 1000)
        return "D" + intToRoman(num - 500);
    if (num >= 1000)
        return "M" + intToRoman(num - 1000);
    return "";
}