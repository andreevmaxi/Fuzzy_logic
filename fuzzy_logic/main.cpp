#include <cassert>
#include <cstdio>
#include <cstdlib>



bool UserInputFunc(const int MaxInput, float* x1, float* x2, char* operation);

bool Operation(float* x1, float* x2, char* oper);

bool Not(float* a);

bool Or(float* a, float* b);

bool And(float* a, float* b);

int main()
{
    const int MaxInput = 128;

    float x1 = 0;
    float x2 = 0;

    char operation = '\0';

    UserInputFunc(MaxInput, &x1, &x2, &operation);

    Operation(&x1, &x2, &operation);

    return 0;
}

bool UserInputFunc(const int MaxInput, float* x1, float* x2, char* operation)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(operation != NULL);

    char* UserInput = (char*)calloc ( (MaxInput), sizeof(char));
    assert (UserInput != NULL);

    scanf("%s", UserInput);

    bool NowInputVariable = 1;
    int NowTen = 1;
    int NowElement = 0;

    while ( (NowElement < MaxInput) && (*(UserInput + NowElement) != '\0' && *(UserInput + NowElement) != '\n' && *(UserInput + NowElement) != 'EOF' ) )
    {
        if (*(UserInput + NowElement) >= '0' && *(UserInput + NowElement) <= '9')
        {
            if (NowInputVariable)
            {
                *x1 += (double)(*(UserInput + NowElement)-'0')/(double)NowTen;
                NowTen *= 10;
            } else
            {
                *x2 += (double)(*(UserInput + NowElement)-'0')/(double)NowTen;
                NowTen *= 10;
            }
        } else
        {
            if (*(UserInput + NowElement) == '~')
            {
                *operation = '~';
            }
            if (*(UserInput + NowElement) == '*')
            {
                *operation = '*';
                NowInputVariable = 0;
                NowTen = 1;
            }
            if (*(UserInput + NowElement) == '+')
            {
                *operation = '+';
                NowInputVariable = 0;
                NowTen = 1;
            }
        }
        ++NowElement;
    }

    free(UserInput);
    return 1;
}

bool Operation(float* x1, float* x2, char* oper)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(oper != NULL);

    switch(*oper)
    {
        case '\0':
        return 0;

        case '~':
        Not(x1);
        break;

        case '+':
        Or(x1, x2);
        break;

        case '*':
        And(x1, x2);
        break;
    }

    return 1;
}

bool Not(float* a)
{
    float tmp = 0;

    tmp = 1 - *a;
    printf("%.2f", tmp);
    return 1;
}

bool Or(float* a, float* b)
{
    float tmp = 0;

    tmp = (*a) + (*b) - (*a)*(*b);
    printf("%.2f", tmp);
    return 1;
}

bool And(float* a, float* b)
{
    float tmp = 0;

    tmp = (*a)*(*b);
    printf("%.2f", tmp);
    return 1;
}



