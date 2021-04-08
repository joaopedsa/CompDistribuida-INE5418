 #include <string.h>
 #include "./utils.h"

 char* messageWrite(int position, char* buffer, int tam_buffer) {
    char* message = malloc(sizeof(char*));
    char* positionStr = malloc(sizeof(char*));
    char* tamBufferStr = malloc(sizeof(char*));
    itoa(position, positionStr);
    itoa(tam_buffer, tamBufferStr);
    strcat(message, "write(");
    strcat(message, positionStr);
    strcat(message, ",");
    strcat(message, buffer);
    strcat(message, ",");
    strcat(message, tamBufferStr);
    strcat(message, ")");
    return message;
}

 char* messageRead(int position, int tam) {
    char* message = malloc(sizeof(char*));
    char* positionStr = malloc(sizeof(char*));
    char* tamStr = malloc(sizeof(char*));
    itoa(position, positionStr);
    itoa(tam, tamStr);
    strcat(message, "read(");
    strcat(message, positionStr);
    strcat(message, ",");
    strcat(message, tamStr);
    strcat(message, ")");
    return message;
}

 /* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  