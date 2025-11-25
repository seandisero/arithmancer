@echo off
@REM -Wall - Enable all common warnings
@REM -Wextra - Enable extra warnings not covered by -Wall
@REM -Wpedantic - Strict ISO C compliance
@REM -Werror - Treat warnings as errors (force you to fix them)
@REM -std=c11 - Use C11 standard
@REM Safety-Critical Warnings:
@REM -Wconversion - Warn about implicit type conversions that may lose data
@REM -Wsign-conversion - Warn about sign conversions
@REM -Wshadow - Warn if variable shadows another
@REM -Wformat=2 - Extra format string checking
@REM -Wformat-security - Warn about security issues in format strings
@REM -Wnull-dereference - Warn about potential NULL dereferences
@REM Code Quality Warnings:
@REM -Wstrict-prototypes - Warn if function declared without argument types
@REM -Wmissing-prototypes - Warn if function defined without prototype
@REM -Wwrite-strings - String constants are const
@REM -Wpointer-arith - Warn about pointer arithmetic issues
@REM Optimization:
@REM -O2 - Level 2 optimization (good balance)

set CFLAGS=-g -Wall -Wextra -Wpedantic -Werror -std=c11 -O2
set CFLAGS=%CFLAGS% -Wconversion -Wsign-conversion -Wshadow
set CFLAGS=%CFLAGS% -Wformat=2 -Wformat-security -Wnull-dereference
set CFLAGS=%CFLAGS% -Wstrict-prototypes -Wmissing-prototypes
set CFLAGS=%CFLAGS% -Wwrite-strings -Wpointer-arith
set CFLAGS=%CFLAGS% -I./include

gcc %CFLAGS% -c src\token.c -o build\token.o
gcc %CFLAGS% -c src\stack.c -o build\stack.o
gcc %CFLAGS% -c src\queue.c -o build\queue.o
gcc %CFLAGS% -c src\arithmancer.c -o build\arithmancer.o
gcc %CFLAGS% -c main.c -o build\main.o
gcc -g -o arithmancer build\token.o build\stack.o build\queue.o build\arithmancer.o build\main.o -lm
.\arithmancer.exe
