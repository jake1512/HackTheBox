#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdio.h>


void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {

    FILE *encrypted;
    FILE *decrypted;
    FILE *keyfile;

    keyfile = fopen("updater", "rb");
    fseek(keyfile, 0, 2);
    int len = ftell(keyfile);
    fseek(keyfile, 0, 0);
    unsigned char key[len];
    fread(key, len, 1, keyfile);
    fclose(keyfile);

    unsigned char iv[] =
        {
        0x01, 0x44, 0x8C, 0x79, 0x09, 0x93, 0x9E, 0x13, 0xCE, 0x35, 
        0x97, 0x10, 0xB9, 0xF0, 0xDC, 0x2E
        };
    
    encrypted = fopen("takeover.docx.24bes", "rb");
    fseek(encrypted, 0, 2);
    int encrypted_len = ftell(encrypted);
    fseek(encrypted, 0, 0);
    unsigned char encrypted_buffer[encrypted_len];
    fread(encrypted_buffer, encrypted_len, 1, encrypted);

    decrypted = fopen("takeover.docx", "wb");
    unsigned char decrypted_buffer[encrypted_len];

    if(decrypted) {

        EVP_CIPHER_CTX *ctx;
        int len1;
        int decrypted_len;

        if(!(ctx = EVP_CIPHER_CTX_new()))
            handleErrors();
        
        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
            handleErrors();

        if(1 != EVP_DecryptUpdate(ctx, decrypted_buffer, &len1, encrypted_buffer, encrypted_len))
            handleErrors();
        decrypted_len = len1;
        if(1 != EVP_DecryptFinal_ex(ctx, decrypted_buffer + len, &len1))
            handleErrors();
        decrypted_len += len1;
        
        fwrite(decrypted_buffer, 1, decrypted_len, decrypted);
        EVP_CIPHER_CTX_free(ctx);
        fclose(decrypted);
    }
    return 0;
}