/* UWindsor POTW 2017
 * Week 2 - Eye of the Storm
 * Adam Vandolder
 * github.com/avandolder */

#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    int n, left, right;
    std::cin >> n;

    // Handle the 0 case.
    if (n == 0)
    {
        std::cout << -1 << std::endl;
        return 0;
    }

    // Read in all of the seperate pressure values.
    std::vector<int> pressures(n);
    for (int i = 0; i < n; i++)
        std::cin >> pressures[i];

    // Calculate the average of the pressures to the left of each element.
    std::vector<double> left_avg(n);
    for (int i = 1, sum = pressures[0]; i < n-1; sum += pressures[i], i++)
        left_avg[i] = (sum / (double)(i));

    // Calculate the average of the pressures to the right of each element.
    std::vector<double> right_avg(n);
    for (int i = n-2, sum = pressures[n-1]; i > 0; sum += pressures[i], i--)
        right_avg[i] = sum / (double)(n - i - 1);

    // Determine whether or not an eye exists, and, if it does, set eye to its
    // position in the pressures vector.
    int eye = -1;
    for (int i = 1; i < n-1; i++)
    {
        if (1 - (pressures[i] / left_avg[i]) >= 0.15 &&
            1 - (pressures[i] / right_avg[i]) >= 0.15)
        {
            eye = i;
            break;
        }
    }

    std::cout << eye << std::endl;

    return 0;
}
