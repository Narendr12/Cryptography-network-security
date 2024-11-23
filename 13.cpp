#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int determinant_mod(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + mod) % mod;
}

void matrix_inverse_mod(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod, int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant_mod(matrix, mod);
    int det_inv = mod_inverse(det, mod);
    if (det_inv == -1) {
        printf("Matrix is not invertible under mod %d.\n", mod);
        exit(1);
    }
    inverse[0][0] = (matrix[1][1] * det_inv) % mod;
    inverse[0][1] = (-matrix[0][1] * det_inv + mod) % mod;
    inverse[1][0] = (-matrix[1][0] * det_inv + mod) % mod;
    inverse[1][1] = (matrix[0][0] * det_inv) % mod;
}

void matrix_multiply(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][1], int result[MATRIX_SIZE][1], int mod) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i][0] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][0] += A[i][j] * B[j][0];
        }
        result[i][0] %= mod;
    }
}

void hill_encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext, int len) {
    int block[MATRIX_SIZE][1], result[MATRIX_SIZE][1];
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j][0] = plaintext[i + j] - 'A';
        }
        matrix_multiply(key, block, result, 26);
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = (result[j][0] + 26) % 26 + 'A';
        }
    }
}

void known_plaintext_attack(char *plaintext, char *ciphertext, int len, int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int P[MATRIX_SIZE][MATRIX_SIZE], C[MATRIX_SIZE][MATRIX_SIZE];
    int P_inv[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            P[i][j] = plaintext[i * MATRIX_SIZE + j] - 'A';
            C[i][j] = ciphertext[i * MATRIX_SIZE + j] - 'A';
        }
    }
    matrix_inverse_mod(P, 26, P_inv);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            key[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                key[i][j] += C[i][k] * P_inv[k][j];
            }
            key[i][j] %= 26;
        }
    }
}

int main() {
    char plaintext[] = "HELP";
    char ciphertext[] = "XJNG";
    int key[MATRIX_SIZE][MATRIX_SIZE];

    known_plaintext_attack(plaintext, ciphertext, 4, key);

    printf("Recovered key matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

