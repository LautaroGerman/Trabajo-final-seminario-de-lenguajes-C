// CMoka dependencies
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
// Dependencies
#include "ppm-operations.h"
#include "ppm.h"

/**
 * Generate Matrix with next values:
 * [(0,0,0)] [(0,0,0)] [(0,0,0)]... width times
 * [(1,1,1)] [(1,1,1)] [(1,1,1)]...
 * [(2,2,2)] [(2,2,2)] [(2,2,2)]...
 * ... height timesgit
 */
static t_ppm create_test_ppm(unsigned int height, unsigned int width, unsigned short depth) {
    t_ppm img = ppm_create(height, width, depth);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            img.pixels[i][j].red = i;
            img.pixels[i][j].green = i;
            img.pixels[i][j].blue = i;
        }
    }
    return img;
}

static void assert_dimension_and_depth(t_ppm img, unsigned int height, unsigned int width, unsigned short depth) {
    assert_int_equal(img.height, height);
    assert_int_equal(img.width, width);
    assert_int_equal(img.depth, depth);
}

/* Test negative operation */
static void test_ppm_operation_negative(void **state) {
    (void) state;

    unsigned int height = 2;
    unsigned int width = 2;
    unsigned int depth = 255;


    t_ppm img = create_test_ppm(height, width, depth);
    t_ppm neg = ppm_operation_negative(img);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            assert_int_equal(neg.pixels[i][j].red, depth - img.pixels[i][j].red);
            assert_int_equal(neg.pixels[i][j].green, depth - img.pixels[i][j].green);
            assert_int_equal(neg.pixels[i][j].blue, depth - img.pixels[i][j].blue);
        }
    }
    assert_dimension_and_depth(img, neg.height, neg.width, neg.depth);

    ppm_free(img);
    ppm_free(neg);
}

/* Test horizontal flip */
static void test_ppm_operation_flip_horizontal(void **state) {
    (void) state;
    unsigned int height = 2;
    unsigned int width = 3;
    unsigned int depth = 255;

    t_ppm img = create_test_ppm(height, width, depth);
    t_ppm flipped = ppm_operation_flip_horizontal(img);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            assert_memory_equal(&flipped.pixels[i][j], &img.pixels[i][width - j - 1], sizeof(t_ppm_pixel));
        }
    }
    assert_dimension_and_depth(img, flipped.height, flipped.width, flipped.depth);

    ppm_free(img);
    ppm_free(flipped);
}

/* Test vertical flip */
static void test_ppm_operation_flip_vertical(void **state) {
    (void) state;
    unsigned int height = 3;
    unsigned int width = 2;
    unsigned int depth = 255;

    t_ppm img = create_test_ppm(height, width, depth);
    t_ppm flipped = ppm_operation_flip_vertical(img);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            assert_memory_equal(&flipped.pixels[i][j], &img.pixels[height - i - 1][j], sizeof(t_ppm_pixel));
        }
    }
    assert_dimension_and_depth(img, flipped.height, flipped.width, flipped.depth);

    ppm_free(img);
    ppm_free(flipped);
}

/* Test rotate 90 degrees */
static void test_ppm_operation_rotate90(void **state) {
    (void) state;
    unsigned int height = 3;
    unsigned int width = 2;
    unsigned int depth = 255;

    t_ppm img = create_test_ppm(height, width, depth);
    t_ppm rotated = ppm_operation_rotate90(img);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            assert_memory_equal(&img.pixels[i][j], &rotated.pixels[1-j][i], sizeof(t_ppm_pixel));
        }
    }
    assert_dimension_and_depth(img, rotated.width, rotated.height, rotated.depth);

    ppm_free(img);
    ppm_free(rotated);
}

/* Test blur */
static void test_ppm_operation_blur(void **state) {
    /*  ratio = 2
        Input Matrix:                       Output blurred Matrix:
        [(0,0,0)] [(0,0,0)] [(0,0,0)]       [(1,1,1)] [(1,1,1)] [(1,1,1)]
        [(1,1,1)] [(1,1,1)] [(1,1,1)]       [(1,1,1)] [(1,1,1)] [(1,1,1)]
        [(2,2,2)] [(2,2,2)] [(2,2,2)]       [(1,1,1)] [(1,1,1)] [(1,1,1)]
    */

    (void) state;
    unsigned int height = 3, width = 3, depth = 255, ratio = 2;

    t_ppm img = create_test_ppm(height, width, depth);
    t_ppm blurred = ppm_operation_blur(img, ratio);
    t_ppm_pixel expected = {1,1,1};

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            assert_memory_equal(&blurred.pixels[i][j], &expected, sizeof(t_ppm_pixel));
        }
    }
    assert_dimension_and_depth(img, blurred.height, blurred.width, blurred.depth);

    ppm_free(img);
    ppm_free(blurred);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ppm_operation_negative),
        cmocka_unit_test(test_ppm_operation_flip_horizontal),
        cmocka_unit_test(test_ppm_operation_flip_vertical),
        cmocka_unit_test(test_ppm_operation_rotate90),
        cmocka_unit_test(test_ppm_operation_blur),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}