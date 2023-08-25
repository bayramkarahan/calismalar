// Simple test of readline

#include <iostream>

#include <readline/readline.h>
#include <readline/history.h>
using namespace std;
int main(int argc, char** argv)
{
const char *line;
while ((line = readline("? ")) != nullptr) {
cout << "[" << line << "]" << endl;
if (*line) add_history(line);
free((void *)line);
}
return 0;
}
