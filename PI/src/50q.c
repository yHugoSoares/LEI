#include <stdio.h>
#include <string.h>
#include <math.h>

void q1() 
{
    int n = 0, resultado = 0;
    printf("Insira numeros inteiros (0 para terminar)\n");
    while (scanf("%d", &n) && n != 0)
    {
        if (n > resultado) 
        {
            resultado = n;
        }
    }
    printf("Maior: %d\n", resultado);
}


void q2() 
{
    int n = 0, counter = 0;
    float soma = 0, media = 0;
    printf("Insira numeros para media (0 para terminar)\n");
    while(scanf("%i", &n) && n != 0)
    {
        soma += n;
        counter++;
    }
    media = soma / counter;
    printf("Media: %.2f\n", media);
}

void q3()
{
    int n = 0, counter = 0, v[100], max = 0, max2 = 0;
    printf("Insira numeros inteiros (0 para terminar)\n");
    while(scanf("%i", &n) && n != 0)
    {
        v[counter++] = n;
    }
    for (int i = 0; i < counter; i++)
    {
        if (max < v[i])
        {
            max = v[i];
        }
    }
    for (int i = 0; i < counter; i++)
    {
        if (max2 < v[i] && v[i] != max)
        {
            max2 = v[i];
        }
    }
    printf("2º maior: %i\n", max2);
}

int bitsUm (unsigned int n)
{
    int counter = 0;
    while (n != 0)
    {
        if (n % 2 == 1)
        {
            counter++;
        }
        n = n / 2;
    }
    return counter;
}

int trailingZ (unsigned int n)
{
    int counter = 0;
    while (n != 0)
    {
        if (n % 2 == 0)
        {
            counter++;
        }
        n = n / 2;
    }
    return counter;
}

int qDig (unsigned int n)
{
    int counter = 0;
    while (n > 9)
    {
        counter++;
        n /= 10;
    }
    
    return counter + 1;
}

char *strcatV2 (char s1[], char s2[])
{
    char sUnited[strlen(s1) + strlen(s2)];
    for (long unsigned int i = 0; i < strlen(s1); i++)
    {
        sUnited[i] = s1[i];
    }
    for (long unsigned int i = strlen(s1); i < strlen(s1) + strlen(s2); i++)
    {
        sUnited[i] = s2[i];
    }
    return fgets(sUnited, sizeof(sUnited), stdout);
}

char *strcpyV2 (char *dest, char source[])
{
    for (long unsigned int i = 0; i < strlen(source); i++)
    {
        dest[i] = source[i];
    }
    return dest;
}

int strcmpV2 (char s1[], char s2[])
{
    int sum = 0;
    for (long unsigned int i = 0; i < strlen(s1); i++)
    {
        if (s1[i]  == s2[i])
        {
            sum = 0;
        }
        else if (s1[i] > s2[i])
        {
            sum += s1[i] - s2[i];
        }
        else
        {
            sum += s2[i] - s1[i];
        }
    }
    return sum;
}

char *strstrV2 (char s1[], char s2[])
{
    long unsigned int counter = 0;
    for (int i = 0; s1[i] != '\0' ; i++)
    {
        if (s1[i] == s2[counter])
        {
            counter++;
            if (counter == strlen(s2))
            {
                return &s1[i - counter + 1];
            }
        }
        else
        {
            counter = 0;
        }
    }
    return NULL;
}

char *strstrWorking (char haystack[], char needle[]) 
{
    int Nh, Nn, found;
    for(Nh = 0; haystack[Nh]; Nh++) 
    {
        found = 1;
        for (Nn = 0; needle[Nn]; Nn++)
            if (needle[Nn] != haystack[Nh + Nn])
                found = 0;
        if (found == 1) break;
    }
    if(found == 1) return haystack + Nh;
    return NULL;
}

void strrev (char s[])
{
    int counter = 0;
    char sReversed[strlen(s)];
    for (long unsigned int i = strlen(s); i > 0; i--)
    {
        sReversed[counter++] = s[i - 2];
    }
    printf("%s\n", sReversed);
}

void truncW (char t[], int n)
{
    int counter = 0;
    for (int i = 0; t[i] != '\0'; i++)
    {
        if (i == ' ')
        {
            
        }
        
        for (int j = 0; j < n; j++)
        {
            t[counter++] = t[j+i];
        }
    }
}

void strnoV (char s[])
{
    char sNoV[strlen(s)];
    int counter = 0;
    for (long unsigned int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
        {

        }
        else sNoV[counter++] = s[i];
    }
    printf("%s\n", sNoV);
}

int freqC(char ch, char s[]) 
{
    int i, freq = 0;
    for(i = 0; s[i]; i++) 
    {
        if (s[i] == ch) freq++;
    }
    return freq;
}

char charMaisFreq(char s[]) 
{
    char maisFreq = 0;
    int i, freqMax = 0, freq;
    for(i = 0; s[i]; i++) 
    {
        if((freq = freqC(s[i],s)) > freqMax) 
        {
            freqMax = freq;
            maisFreq = s[i];
        }
    }
    return maisFreq;
}

int iguaisConsecutivos (char s[]) 
{
    char ch = s[0];
    int counter1 = 0, counter2 = 0;
    for (int i = 0; s[i] != '\0' ; i++)
    {
        if (ch == s[i])
        {
            counter1++;
        }
        else
        {
            counter1 = 1;
        }
        if (counter1 > counter2)
        {
            counter2 = counter1;
        }
    }
    return counter2;
}

int difConsecutivos (char s[])
{
    char ch = s[0];
    int counter1 = 0, counter2 = 0;
    for (int i = 0; s[i] != '\0' ; i++)
    {
        if (ch != s[i])
        {
            counter1++;
        }
        else
        {
            counter1 = 1;
        }
        if (counter1 > counter2)
        {
            counter2 = counter1;
        }
    }
    return counter2;
}

int maiorPrefixo (char s1 [], char s2 [])
{
    int counter = 0;
    for (int i = 0; s1[i] != '\0' ; i++)
    {
        if (s1[i] == s2[i])
        {
            counter++;
        }
        else break;
    }
    return counter;
}

int maiorSufixo (char s1 [], char s2 [])
{
    int counter = 0;
    long unsigned int j = strlen(s2) - 1;
    for (long unsigned int i = strlen(s1) - 1; i > 0; i--)
    {
        if (s1[i] == s2[j--])
        {
            counter++;
        }
        else break;
    }
    return counter - 1;
}

int sufPref (char s1[], char s2[]) 
{
    int N1, N2 = 0;
    for(N1 = 0; s1[N1]; N1++) 
    {
        if(s1[N1] == s2[N2]) N2++;
        else N2 = 0;
    }
    return N2;
}


int main()
{
    // int n1 = 0;
    // scanf("%i", &n1);
    // printf("Numero de bits 1: %i\n", bitsUm(n1));

    // int n2 = 0;
    // scanf("%i", &n2);
    // printf("Numero de bits 0: %i\n", trailingZ(n2));

    // int n3 = 0;
    // scanf("%i", &n3);
    // printf("Numero de digitos: %i\n", qDig(n3));

    // char s1[100], s2[100];
    // fgets(s1, 100, stdin);
    // fgets(s2, 100, stdin);
    // printf("String concatenada: %s\n", strcatV2(s1, s2));

    // char source[100], dest[100];
    // fgets(source, 100, stdin);
    // printf("String copiada: %s\n", strcpy(dest, source));

    // char s1[100], s2[100];
    // fgets(s1, 100, stdin);
    // fgets(s2, 100, stdin);
    // printf("Comparacao: %i\n", strcmpV2(s1, s2));

    // char s1[100], s2[100];
    // scanf("%s", s1);
    // scanf("%s", s2);
    // printf("String encontrada: %s\n", strstrV2(s1, s2));

    // char s[100];
    // fgets(s, 100, stdin);
    // strrev(s);

    // char t[100];
    // int n = 0;
    // fgets(t, 100, stdin);
    // scanf("%i", &n);
    // truncW(t, n);

    // char t[1000];
    // int n = 0;
    // fgets(t, 100, stdin);
    // scanf("%i", &n);
    // truncW(t, n);

    // char s[100];
    // fgets(s, 100, stdin);
    // strnoV(s);

    // char s[100];
    // fgets(s, 100, stdin);
    // printf("Caracter mais frequente: %c\n", charMaisFreq(s));

    // char s[100];
    // fgets(s, 100, stdin);
    // printf("Iguais consecutivos: %i\n", iguaisConsecutivos(s));

    // char s[100];
    // fgets(s, 100, stdin);
    // printf("Diferentes consecutivos: %i\n", difConsecutivos(s));

    // char s1[100], s2[100];
    // fgets(s1, 100, stdin);
    // fgets(s2, 100, stdin);
    // printf("Maior prefixo: %i\n", maiorPrefixo(s1, s2));

    // char s1[100], s2[100];
    // fgets(s1, 100, stdin);
    // fgets(s2, 100, stdin);
    // printf("Maior sufixo: %i\n", maiorSufixo(s1, s2));

    char s1[100], s2[100];
    scanf("%s", s1);
    scanf("%s", s2);
    printf("Sufixo prefixo: %i\n", sufPref(s1, s2));

    return 0;
}