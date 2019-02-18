// Program 14.1 Classifying wide characters
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

int main(void)
{
    wchar_t ch = 0;

    fwprintf_s(stdout, L"Enter a character: ");
    fwscanf_s(stdin, L" %lc", &ch, sizeof(ch));

    if(iswalnum(ch))
    {
        if(iswdigit(ch))
            fwprintf_s(stdout, L"You entered the digit %lc\n", ch);
        else if(iswlower(ch))
            fwprintf_s(stdout, L"You entered a lowercase %lc\n", towupper(ch));
        else
            fwprintf_s(stdout, L"You entered an uppercase %lc\n", towlower(ch));
    }
    else if(iswpunct(ch))
        fwprintf_s(stdout, L"You entered the punctuation character %lc.\n", ch);
    else
        fwprintf_s(stdout, L"You entered %lc, but I don't know what it is!\n", ch);
    return 0;
}