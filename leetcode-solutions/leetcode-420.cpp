#include <priority_queue>
#include <vector>
using namespace std;

int strongPasswordChecker(string s)
{
    bool lower = false;
    bool upper = false;
    bool digit = false;

    int repeating = 0;

    int n = s.size();

    //We actually dont need a priority queue here because
    //The numbers are going to be < 3
    priority_queue<int> toRemove;

    for (int i = 0; i < n;)
    {
        //Check if character is lowercase, uppercase, or digit and set those to true
        char c = s[i];
        if (48 <= c && c <= 57)
        {
            digit = true;
        }
        else if (65 <= c && c <= 90)
        {
            upper = true;
        }
        else if (97 <= c && c <= 122)
        {
            lower = true;
        }

        //count how many repeating numbers we have
        int counter = 1;
        while (i + counter < n && s[i + counter] == s[i])
        {
            counter++;
        }

        //number of repeat errors goes up by 1 for every 3 repeating
        repeating += (counter) / 3;

        //if we have a repeat error than push to a heap the number of deletions we need to
        //remove a repeat error
        if (counter > 2 && counter % 3 != 2)
        {
            toRemove.push(-((counter % 3) + 1));
        }

        i += counter;
    }

    //count missing cases
    int toAdd = !lower + !upper + !digit;

    //get size error. 0 if there are no errors
    int toSize = 0;
    if (n > 20)
    {
        toSize = 20 - n;
    }
    else if (n < 6)
    {
        toSize = 6 - n;
    }

    if (toSize < 0)
    {
        //case n > 20
        //remove easy repeat errors with < 3 deletions required
        int tmpSize = toSize;
        while (toRemove.size())
        {
            if (tmpSize <= toRemove.top())
            {
                tmpSize -= toRemove.top();
                toRemove.pop();
                repeating--;
            }
            else
            {
                break;
            }
        }

        //remove repeat errors that require 3 deletions
        while (repeating && tmpSize <= -3)
        {
            tmpSize += 3;
            repeating--;
        }

        //if we have any case errors we can merge them with
        //repeat errors
        return max(toAdd, repeating) - toSize;
    }
    else
    {
        //case n <= 20
        //the error is simply the max becauses we can merge
        //every error with pretty much no consequence
        return max(toSize, max(toAdd, repeating));
    }
}
