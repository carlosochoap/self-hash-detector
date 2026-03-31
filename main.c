#include <stdio.h>
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")

int main() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    printf("Mi ruta: %s\n", path);

    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        printf("Error: no pude abrir el archivo\n");
        return 1;
    }
    printf("Archivo abierto correctamente\n");

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("Tamano del archivo: %ld bytes\n", fileSize);

    unsigned char* buffer = (unsigned char*)malloc(fileSize);
    if (buffer == NULL) {
        printf("Error: no pude reservar memoria\n");
        fclose(file);
        return 1;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);
    printf("Bytes leidos correctamente\n");

    BCRYPT_ALG_HANDLE hAlgorithm;
    BCryptOpenAlgorithmProvider(&hAlgorithm, BCRYPT_SHA256_ALGORITHM, NULL, 0);
    BCRYPT_HASH_HANDLE hHash;
    BCryptCreateHash(hAlgorithm, &hHash, NULL, 0, NULL, 0, 0);
    
    BCryptHashData(hHash, buffer, fileSize, 0);
    unsigned char hash[32];
    BCryptFinishHash(hHash, hash, 32, 0);

    printf("SHA-256: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    free(buffer);
    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlgorithm, 0);

    getchar();
    return 0;
}
