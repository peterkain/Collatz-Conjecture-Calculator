/*
 * Author: Peter Maximilian Kain
 * Date: 15th of January, 2018
 * Purpose: Calculations regarding the "3n+1 problem", also
 *          called "Collatz Conjecture"
 * Sources: https://en.wikipedia.org/wiki/Collatz_conjecture
 */

#include <iostream>

/*
 * Macro Information:
 *   DEBUG_INFO:
 *     If set to 1 prints information regarding the
 *     number of operations needed to get to 1 and
 *     the results of each iteration.
 *     Should you not want this, set to 0
 *
 *   WRITE_TO_FILE:
 *     ONLY HAS AN EFFECT, IF DEBUG_INFO IS SET TO 1
 *     If set to 1 prints information of DEBUG_INFO
 *     to a file named output.data (simply open with editor)
 *     instead of the console
 *     Should you not want this, set to 0
 *
 *   You should disable both of this, if you want maximum performance
 *
 *   RANGE_MIN:
 *     Decides where the loop starts. Set accordingly
 *   RANGE_MAX:
 *     Decides where the loop ends. Set accordingly
 */

#define DEBUG_INFO 0
#define WRITE_TO_FILE 0
#define RANGE_MIN 1
#define RANGE_MAX 1000000

using namespace std;

#if WRITE_TO_FILE && DEBUG_INFO
#include <fstream>
#include <sstream>
fstream file {"output.data", ios::out};
#endif

struct PressEnter
{ ~PressEnter()
   { cout << "Press any key to exit...";
     cin.get();
   }
} press_enter;

int main()
{
    if(RANGE_MIN <= 0)
    {
        cout << "Please specify a minimum value greater than 0\n";
        return -1;
    }
    if(RANGE_MIN > RANGE_MAX)
    {
        cout << "Minimum range can't be greater than maximum range\n";
        return -1;
    }

    ios::sync_with_stdio(false); // For faster output, since I don't use the
                                 // C io function

#if DEBUG_INFO
    unsigned int counter {0};
#endif

    for(unsigned long long n {RANGE_MIN}; n <= RANGE_MAX; n++)
    {
        unsigned long long value {n};
        while(true)
        {
#if DEBUG_INFO && !WRITE_TO_FILE
            cout << value << "\n";
#elif DEBUG_INFO && WRITE_TO_FILE
            file << value << (value == n ? ": " : (value == 1 ? "" : " "));
#endif
            if(value == 1) break;

            if(value & 0x1)
                value = 3 * value + 1;
            else
                value = value >> 1; // Halfs the number
                                    // ( 00011110 (30) >> 1 = 00001111 (15) )
#if DEBUG_INFO
            counter++;
#endif
        }
#if DEBUG_INFO && !WRITE_TO_FILE
        cout << "\n";
#elif DEBUG_INFO && WRITE_TO_FILE
        file << "\n";
#endif
    }

#if DEBUG_INFO && !WRITE_TO_FILE
    cout << "Finished in a total of " << counter << " operations" << endl;
#elif DEBUG_INFO && WRITE_TO_FILE
    file << "\nFinished in a total of " << counter << " operations";
    cout << "Finished!" << endl;
#endif
    return 0;
}
