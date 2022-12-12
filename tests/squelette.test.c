//#include "../nom_module.h"
#include <stdio.h>

void runTest(int (*f)(), int* failures, int* runs) {
    if (!f()) (*failures)++;
    (*runs)++;
}

int main(int argc, char* argv[]) {
    int test_count = 0, failures = 0;
    //Insérer les runTest(nom_fonction, &failures, &runs);
    printf("%d failures out of %d tests\n", failures, test_count);
    return failures;
}