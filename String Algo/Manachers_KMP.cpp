// https : //github.com/ADJA/algos/blob/master/Strings/ManacherPalindromes.cpp
#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;
// finds number of palindromic substrings
// odd[i]<- number of palindromic substrings centered at i including the
// charater itself even[i]<- number of palindromic substrings centered at i
int manachers(string s)
{
    int n = s.size();
    vi odd(n);
    vi even(n);
    int l, r;
    l = r = -1;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int cur = 1;
        if (i < r)
            cur = min(r - i + 1, odd[l + r - i]);
        while (i + cur < n && i - cur >= 0 && s[i - cur] == s[i + cur])
            cur++;
        odd[i] = cur;
        if (i + cur - 1 > r)
        {
            l = i - cur + 1;
            r = i + cur - 1;
        }
    }

    // Even case
    l = r = -1;
    for (int i = 0; i < n; i++)
    {
        int cur = 0;
        if (i < r)
            cur = min(r - i + 1, even[l + r - i + 1]);
        while (i + cur < n && i - 1 - cur >= 0 && s[i - 1 - cur] == s[i + cur])
            cur++;
        even[i] = cur;
        if (i + cur - 1 > r)
        {
            l = i - cur;
            r = i + cur - 1;
        }
    }

    for (int i = 0; i < n; i++)
    {

        ans += odd[i];
        // or ans+=odd[i]-1 ; to negelect the single character palindromes but
        // make sure odd[i]>1
        if (even[i])
            ans += even[i];
    }
    return ans;
}

// Fills lps[] for given patttern pat[0..M-1]
void LPS(string pat, int M, vector<int> &lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            // len++;
            // lps[i] = len;

            lps[i] = ++len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
// given a string it will find the number of occurences of it in txt
void KMPSearch(string pat, string txt)
{
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    vi lps(M);

    // Preprocess the pattern (calculate lps[] array)
    LPS(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not rematch lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}
int main()
{
    string txt = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";
    KMPSearch(pat, txt);
    cout << "\n";
    cout << manachers("aaa");

    return 0;
}
