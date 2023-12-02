#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int rabin_karp(const string& text, const string& pattern, int q, int d, int h)
{
    int n = text.length();
    int m = pattern.length();

    int p = 0; // Хеш-значення підрядка pattern
    int t = 0; // Хеш-значення поточного вікна тексту

    // Обчислення початкових хеш-значень
    for (int i = 0; i < m; i++)
    {
        p = (d * p + (pattern[i] - '0')) % q;
        t = (d * t + (text[i] - '0')) % q;
    }

    // Пошук підрядка в тексті
    for (int i = 0; i <= n - m; i++)
    {
        if (p == t) 
        { // Перевірка хеш-значень

            bool match = true;

            for (int j = 0; j < m; j++)
            {
                if (pattern[j] != text[i + j])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                return i; // Повертаємо позицію першого входження підрядка
            }
        }

        if (i < n - m)
        { // Оновлення хеш-значення
            t = (d * (t - (text[i] - '0') * h) + (text[i + m] - '0')) % q;

            if (t < 0)
            {
                t += q;
            }
        }
    }

    return -1; // Підрядок не знайдено
}

int main()
{
    setlocale(LC_ALL, "Ukr");

    string text = "fdfacbacbacbadafc";
    string pattern = "cbacbacba";

    int q = 19;
    int d = 10;
    int h = 1000000000;

    int result = rabin_karp(text, pattern, q, d, h);

    if (result != -1)
    {
        cout << "Підрядок знайдено в позиції: " << result << endl;
    }
    else
    {
        cout << "Підрядок не знайдено!" << endl;
    }
    return 0;
}