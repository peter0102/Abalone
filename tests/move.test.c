#include "../global.h"
#include "../move.h"
#include <stdio.h>

int test_moveChrConvert_incorrect_type() {
    const char chr = ERROR, type = 'a', expected = ERROR, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_incorrect_type: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvert_letter_too_small() {
    const char chr = '@', type = 'l', expected = ERROR, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_letter_too_small: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvert_letter_too_big() {
    const char chr = 'I', type = 'l', expected = ERROR, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_letter_too_big: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvert_letter() {
    const char chr = 'A', type = 'l', expected = 1, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_letter: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvert_number_too_small() {
    const char chr = '0', type = 'n', expected = ERROR, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_number_too_small: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvert_number_too_big() {
    const char chr = '9', type = 'n', expected = ERROR, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_letter_too_big: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvert_number() {
    const char chr = '1', type = 'n', expected = 1, actual = moveChrConvert(chr, type);
    if (actual != expected) {
        printf("test_moveChrConvert_number: ");
        printf("moveChrConvert(%c, %c): ", chr, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvertReverse_too_small() {
    const char index = 0, type = 'l', expected = ERROR, actual = moveChrConvertReverse(index, type);
    if (actual != expected) {
        printf("test_moveChrConvertReverse_too_small: ");
        printf("moveChrConvertReverse(%c, %c): ", index, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvertReverse_too_big() {
    const char index = 9, type = 'l', expected = ERROR, actual = moveChrConvertReverse(index, type);
    if (actual != expected) {
        printf("test_moveChrConvertReverse_too_big: ");
        printf("moveChrConvertReverse(%c, %c): ", index, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvertReverse_letter() {
    const char index = 1, type = 'l', expected = 'A', actual = moveChrConvertReverse(index, type);
    if (actual != expected) {
        printf("test_moveChrConvertReverse_letter: ");
        printf("moveChrConvertReverse(%c, %c): ", index, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvertReverse_number() {
    const char index = 1, type = 'n', expected = '1', actual = moveChrConvertReverse(index, type);
    if (actual != expected) {
        printf("test_moveChrConvertReverse_number: ");
        printf("moveChrConvertReverse(%c, %c): ", index, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_moveChrConvertReverse_incorrect_type() {
    const char index = 1, type = 'a', expected = ERROR, actual = moveChrConvertReverse(index, type);
    if (actual != expected) {
        printf("test_moveChrConvertReverse_incorrect_type: ");
        printf("moveChrConvertReverse(%c, %c): ", index, type);
        printf("expecting %c while got %c\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_translateMove_incorrect_str_length() {
    char* input = "A:B1";
    Move moveActual = {{ERROR, ERROR}, {ERROR, ERROR}};
    const Move expected = {{ERROR, ERROR}, {ERROR, ERROR}};
    translateMove(moveActual, input);
    if (moveActual != expected) {
        printf("test_translateMove_incorrect_str_length: ");
        return 0;
    }
    return 1;
}

int test_translateMove_incorrect_separator() {
    char* input = "A1uB1";
    Move moveActual = {{ERROR, ERROR}, {ERROR, ERROR}};
    const Move expected = {{ERROR, ERROR}, {ERROR, ERROR}};
    translateMove(moveActual, input);
    if (moveActual != expected) {
        printf("test_translateMove_incorrect_separator: ");
        return 0;
    }
    return 1;
}

int test_translateMove_incorrect_character() {
    char* input = "A9:B1";
    Move moveActual = {{ERROR, ERROR}, {ERROR, ERROR}};
    const Move expected = {{ERROR, ERROR}, {ERROR, ERROR}};
    translateMove(moveActual, input);
    if (moveActual != expected) {
        printf("test_translateMove_incorrect_character: ");
        return 0;
    }
    return 1;
}

int test_translateMove() {
    char* input = "A1:B1";
    Move moveActual = {{ERROR, ERROR}, {ERROR, ERROR}};
    const Move expected = {{1, 2}, {1, 1}};
    translateMove(moveActual, input);
    if (moveActual != expected) {
        printf("test_translateMove: ");
        return 0;
    }
    return 1;
}

int test_translateMoveReverse_incorrect_character() {
    Move move = {{1, 9}, {2, 3}};
    char* expected = "A2:_3"; expected[3] = ERROR;
    char* actual = translateMoveReverse(move);
    if (actual != expected) {
        printf("test_translateMoveReverse_incorrect_character: ");
        printf("expecting %s while got %s\n", expected, actual);
        return 0;
    }
    return 1;
}

int test_translateMoveReverse() {
    Move move = {{1, 2}, {2, 3}};
    const char* expected = "A2:B3";
    char* actual = translateMoveReverse(move);
    if (actual != expected) {
        printf("test_translateMoveReverse: ");
        printf("expecting %s while got %s\n", expected, actual);
        return 0;
    }
    return 1;
}

void runTest(int (*f)(), int* failures, int* runs) {
    if (!f()) (*failures)++;
    (*runs)++;
}

int main(int argc, char* argv[]) {
    int test_count = 0, failures = 0;
    
    runTest(test_moveChrConvert_incorrect_type, &failures, &test_count);
    runTest(test_moveChrConvert_letter, &failures, &test_count);
    runTest(test_moveChrConvert_letter_too_big, &failures, &test_count);
    runTest(test_moveChrConvert_letter_too_small, &failures, &test_count);
    runTest(test_moveChrConvert_number, &failures, &test_count);
    runTest(test_moveChrConvert_number_too_big, &failures, &test_count);
    runTest(test_moveChrConvert_number_too_small, &failures, &test_count);

    runTest(test_moveChrConvertReverse_too_small, &failures, &test_count);
    runTest(test_moveChrConvertReverse_too_big, &failures, &test_count);
    runTest(test_moveChrConvertReverse_incorrect_type, &failures, &test_count);
    runTest(test_moveChrConvertReverse_letter, &failures, &test_count);
    runTest(test_moveChrConvertReverse_number, &failures, &test_count);
    
    runTest(test_translateMove, &failures, &test_count);
    runTest(test_translateMove_incorrect_character, &failures, &test_count);
    runTest(test_translateMove_incorrect_separator, &failures, &test_count);
    runTest(test_translateMove_incorrect_str_length, &failures, &test_count);

    runTest(test_translateMoveReverse, &failures, &test_count);
    runTest(test_translateMoveReverse_incorrect_character, &failures, &test_count);

    printf("%d failures out of %d tests\n", failures, test_count);
    return failures;
}