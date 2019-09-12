#include <cassert>
#include <cstdio>
#include <cstdlib>



bool UserInputFunc(float* x1, float* x2, char* operation);

bool Operation(float* x1, float* x2, char* oper);

float Not(float* a);

float Or(float* a, float* b);

float And(float* a, float* b);

int main()
{

    float x1 = 0;
    float x2 = 0;

    char operation = '\0';

    UserInputFunc(&x1, &x2, &operation);

    Operation(&x1, &x2, &operation);

    return 0;
}

bool UserInputFunc(float* x1, float* x2, char* operation)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(operation != NULL);

    int CharSize = 0;

    FILE* f = fopen("input.txt", "r");
    fseek(f, 0L, SEEK_END);
    CharSize = ftell(f);
    rewind(f);

    char* UserInput = (char*)calloc ( (CharSize), sizeof(char));
    assert (UserInput != NULL);

    fgets(UserInput, CharSize+1 , f);
    fclose(f);

    bool NowInputVariable = 1;
    int NowTen = 1;
    int NowElement = 0;

    while ( (NowElement < CharSize) && (*(UserInput + NowElement) != '\0' && *(UserInput + NowElement) != '\n' && *(UserInput + NowElement) != 'EOF' ) )
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

    float tmp = 0;
    switch(*oper)
    {
        case '\0':
        return 0;

        case '~':
        tmp = Not(x1);
        break;

        case '+':
        tmp = Or(x1, x2);
        break;

        case '*':
        tmp = And(x1, x2);
        break;
    }

    FILE* f = fopen("output.txt", "w");
    fprintf(f, "%.2f", tmp);
    fclose(f);
    return 1;
}

float Not(float* a)
{
    float tmp = 0;

    tmp = 1 - *a;
    return tmp;
}

float Or(float* a, float* b)
{
    float tmp = 0;

    tmp = (*a) + (*b) - (*a)*(*b);
    return tmp;
}

float And(float* a, float* b)
{
    float tmp = 0;

    tmp = (*a)*(*b);
    return tmp;
}



