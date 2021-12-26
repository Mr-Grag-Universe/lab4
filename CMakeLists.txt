cmake_minimum_required(VERSION 3.20)
project(lab4 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab4 main.c CarStruct.c KGetLine.c MainCircle.c /
        MenuCreation.c StartSession.c FunctionsExecution.h/
        FunctionsExecution.c InputFunctions.h ReadFromTerminal.c ReadFromFile.c/
        FGetLine.h FGetLine.c ReadFromFile.c test_input.txt
        InputFunctions.c OutputFunctions.c WorkWithData.h Insert.c
        InsertInSortedArray.c Erase.c Sorts.c Comporators.c Timing.h Timing.c)
