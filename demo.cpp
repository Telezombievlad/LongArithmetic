#include "mechanics\LongArithmetic.h"
#include "TXLib.h"
#include "mechanics\Pi.h"

//-----------------------------------------------------------------------------

void waitUntilSpaceButtonIsPressed();
void waitUntilSpaceButtonIsPressedWhileMakingThreeDots();

//-----------------------------------------------------------------------------

#define BLU txSetConsoleAttr(0xB);
#define GRN txSetConsoleAttr(0xA);
#define RED txSetConsoleAttr(0xC);
#define YEL txSetConsoleAttr(0xE);
#define WHT txSetConsoleAttr(0xF);


#define WAIT waitUntilSpaceButtonIsPressed();
#define DOTS waitUntilSpaceButtonIsPressedWhileMakingThreeDots();

#define COUNTER_STR(counter) ((counter) = GetTickCount());
#define COUNTER_FIN(counter) ((counter) = (GetTickCount() - (counter)));

// Recent-absorbed info:

#define UNUSED_VARIABLE(variable) do {static_cast<void>(variable)} while(false)


//-----------------------------------------------------------------------------

int main()
{
    unsigned int counter = 0;

    WAIT YEL puts("НАЧАЛО ДЕМОНСТРАЦИИ\n");

    //-----------------------------------------------------------------------------

    WAIT YEL puts("__ СЛОЖЕНИЕ __\n");

    WAIT GRN puts("Сложение двух переменных типа int:");
         BLU printf("4294967000");
         WHT printf(" + ");
         BLU printf("5705033000");
         WHT printf(" = ");
         BLU printf("%d\n\n", static_cast<int>(4294967000 + 5705033000));

    WAIT GRN puts("Сложение двух переменных типа LongNumber:");
         BLU printf("4294967000");
         WHT printf(" + ");
         BLU printf("5705033000");
         WHT printf(" = ");
         BLU printf("%s\n\n", (4294967000_Long + 5705033000_Long).toUserRaw());


    WAIT GRN puts("Сложение двух переменных типа LongNumber в шестнадцатеричной системе счисления:"); WHT
         BLU printf("4A");
         WHT printf(" + ");
         BLU printf("1.F");
         WHT printf(" = ");
         BLU printf("%s\n\n", (LongNumber("[4][10]", 16) + LongNumber("[1].[15]", 16)).toUserRaw());


    //-----------------------------------------------------------------------------

    WAIT YEL puts("__ УМНОЖЕНИЕ __\n");

    WAIT GRN puts("Умножение двух переменных типа int:");
         BLU printf("10000");
         WHT printf(" * ");
         BLU printf("500000");
         WHT printf(" = ");
         BLU printf("%d\n\n", static_cast<int>(10000 * 500000));

    WAIT GRN puts("Умножение двух переменных типа LongNumber:");
         BLU printf("10000");
         WHT printf(" * ");
         BLU printf("500000");
         WHT printf(" = ");
         BLU printf("%s\n\n", (10000_Long * 500000_Long).toUserRaw());

    //-----------------------------------------------------------------------------

    WAIT YEL puts("__ ВЫЧИСЛЕНИЕ КОРНЯ ИЗ 2 __\n");

    WAIT GRN puts("Вычисление корня из 2 с использованием типа double:");
         WHT printf("sqrt(");
         BLU printf("2");
         WHT printf(") = ");
         BLU printf("%f\n\n", static_cast<double>(sqrt(2.0)));

    WAIT GRN puts("Вычисление корня из 2 с использованием типа LongNumber:");
         WHT printf("sqrt(");
         BLU printf("2");
         WHT printf(") = ");                                 COUNTER_STR(counter)
         BLU printf("%s\n\n", (2_Long).root(2).toUserRaw()); COUNTER_FIN(counter)
         WHT printf("Время подсчёта: ");
         BLU printf("%d ", counter);
         WHT printf("миллисекунда\n\n");

    //-----------------------------------------------------------------------------

    WAIT YEL puts("__ ВЫЧИСЛЕНИЕ ФАКТОРИАЛА 42 __\n");

    WAIT GRN puts("Используем встроенную операцию факториала:");
    DOTS GRN puts("Встроенной операции вычисления факториала нет.\n");

    WAIT GRN puts("А у типа LongNumber она есть:");
         BLU printf("42");
         WHT printf("! = ");                                    COUNTER_STR(counter)
         BLU printf("%s\n", (42_Long).factorial().toUserRaw()); COUNTER_FIN(counter)
         WHT printf("Время подсчёта: ");
         BLU printf("%d ", counter);
         WHT printf("миллисекунд\n\n");


    //-----------------------------------------------------------------------------

    WAIT YEL puts("КОНЕЦ ПРЕЗЕНТАЦИИ");
    WAIT YEL puts("СПАСИБО ЗА ВНИМАНИЕ\n");
         YEL puts("КОТОВ ПОГЛАЖЕНО: 666");

    WHT txSleep(350);

	return 0;
}

//-----------------------------------------------------------------------------

void waitUntilSpaceButtonIsPressed()
{
    bool spaceButtonPressed = (GetAsyncKeyState(VK_SPACE)) ? true : false;
    bool ready = !spaceButtonPressed;

    while (true)
    {
        if (!GetAsyncKeyState(VK_SPACE) && spaceButtonPressed) ready = true;

        if (ready && GetAsyncKeyState(VK_SPACE)) break;
    }
}

void waitUntilSpaceButtonIsPressedWhileMakingThreeDots()
{
    bool spaceButtonPressed = (GetAsyncKeyState(VK_SPACE)) ? true : false;
    bool ready = !spaceButtonPressed;

    txSleep(500);

    unsigned int currentDot = 0;
    for (;!(ready && GetAsyncKeyState(VK_SPACE)); currentDot++)
    {
        if (!GetAsyncKeyState(VK_SPACE) && spaceButtonPressed) ready = true;

        if (currentDot == 3)
        {
            printf("\b\b\b");
            printf("   ");
            printf("\b\b\b");

            currentDot = 0;
        }

        if (currentDot != 3) printf(".");

        txSleep(600);
    }

    for (; currentDot > 0; currentDot--) printf("\b");
}

