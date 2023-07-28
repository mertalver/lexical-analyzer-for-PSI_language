#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool delimiterCheck(char ch) //Okunan karakterin sınırlayıcı (delimiter) olup olmadığını kontrol edip true veya false döndürür.
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ':' || ch == ';' ||
        ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '"')
        return (true);
    return (false);
}

bool identifierCheck(const char* input) //Okunan karakterin identifier olup olmadığını kontrol edip true veya false döndürür.
{                                       //Aynı zamanda identifier'ın rakamla başlamasını engeller.
                                        //Eğer identifier rakamla başladıysa algılamaz. (Hoca engellemese de olur sıkıntı olmaz diye de belirtmişti.)
    if  (input[0] == '0' || input[0] == '1' || input[0] == '2' ||
         input[0] == '3' || input[0] == '4' || input[0] == '5' ||
         input[0] == '6' || input[0] == '7' || input[0] == '8' ||
         input[0] == '9' || delimiterCheck(input[0]) == true)
        return (false);
    return (true);
}

bool integerCheck(char* input) //Okunan karakterin tam sayı olup olmadığını kontrol edip true veya false döndürür.
{
    int i;
    int len = strlen(input);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (input[i] != '0' && input[i] != '1' && input[i] != '2'
            && input[i] != '3' && input[i] != '4' && input[i] != '5'
            && input[i] != '6' && input[i] != '7' && input[i] != '8'
            && input[i] != '9')
            return (false);
    }
    return (true);
}

bool operatorCheck(char input) //Okunan karakterin operatör olup olmadığını kontrol edip true veya false döndürür.
{
    if (input == '+' || input == '-' || input == '*' ||
        input == '/' || input == ':' || input == '=' )
        return (true);
    return (false);
}

bool keywordCheck(char* input) //Okunan karakterin bir anahtar kelime olup olmadığını kontrol edip true veya false döndürür.
{
    if (!strcmp(input, "break") || !strcmp(input, "case") ||
        !strcmp(input, "char") || !strcmp(input, "const") ||
        !strcmp(input, "continue") ||
        !strcmp(input, "do") || !strcmp(input, "else")
        || !strcmp(input, "enum") || !strcmp(input, "float")
        || !strcmp(input, "for") || !strcmp(input, "goto")
        || !strcmp(input, "if") || !strcmp(input, "int")
        || !strcmp(input, "long") || !strcmp(input, "record")
        || !strcmp(input, "return") || !strcmp(input, "static")
        || !strcmp(input, "while"))
        return (true);
    return (false);
}

char* subString(const char* str, int left, int right) //Eğer art arda gelen karakterler birer harfse bunları harf harici bir karakter gelene kadar alt dizeye (substring) ayırır.
{
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

void parse(char* input) //Karakterlerin kontrolleri yapıldıktan sonra hangi tokene ait olduğuna bakıp dosyaya ait olduğu o token olarak yazdırır.
{                       //Yazdırmaların hepsini küçük harf olarak yapmaktadır çünkü PSI++ dili büyük harf duyarlı değildir.
    int left = 0;
    int right = 0;
    int len = strlen(input);

    FILE *fileLEX = fopen("code.lex", "w"); //code.lex isimli bir output dosyası oluşturur ve tokenleri buraya yazdırır.
    // Eğer text dosyası olarak output isteniyorsa code.lex.txt olarak değiştirilmelidir.
    // Kodu CLion IDE'sinde yazdığım için output dosyası cmake-build-debug klasörünün (main.exeden dolayı) içinde oluşacaktır.

    while (right <= len && left <= right) {
        if (delimiterCheck(input[right]) == false) //Eğer sınırlayıcı false döndürürse o karakterin geçersiz bir durumda olduğuna karar verip diğer karaktere geçer.
            right++;

        if (delimiterCheck(input[right]) == true && left == right) { //Eğer sınırlayıcı true döndürdüyse karakterlerin neler olduğunu kontrol eder.
            if (input[right] == '"') {
                right++;
                char *str_constant = (char*) malloc(1000);
                int i = 0;
                while(input[right] != EOF) {
                    str_constant[i++] = input[right];
                    right++;
                    if(input[right] == '"') {
                        str_constant[i] = '\0';
                        fprintf(fileLEX, "StringConstant(%s)\n", str_constant); //Çift tırnak içindeki karakterleri string constant olarak output dosyasına yazdırır.
                        right++;
                        break;
                    }
                }
                if(input[right] == EOF){
                    printf("ERROR! STRING CONSTANT IS NOT CLOSED.\n"); //Eğer çift tırnak kapanmadıysa konsola hata mesajı yazdırır.
                    fprintf(fileLEX, "ERROR! STRING CONSTANT IS NOT CLOSED.\n"); //Eğer çift tırnak kapanmadıysa dosyaya hata mesajı yazdırır.
                    break;
                    //Bu hatalar harici eğer çift tırnak kapanmadıysa C'nin dosyadan okuma yapma komutu da hata vermektedir.
                    //Örneğin text dosyasında çift tırnak açılıp kapanmadıysa C dili bunu '\"' karakteri olarak algılamaktadır.
                    //Bu yüzden bir sonraki çift tırnağa kadar hepsini tek bir karakter olarak almaktadır.
                }
            }

            if (input[right] == '/' & input[right+1] == '*') {
                right = right + 2;
                while (input[right] != EOF) {
                    right++;
                    if(input[right] == '*' & input[right+1] == '/') { //Yorum satırlarını algılayıp output dosyasına yazdırılmasını önler.
                        right = right + 2;
                        break;
                    }
                }
                if (input[right] == EOF) {
                    printf("ERROR! COMMENT LINE IS NOT CLOSED.\n"); //Eğer yorum satırı kapatılmadıysa konsola hata mesajı yazdırır.
                    fprintf(fileLEX, "ERROR! COMMENT LINE IS NOT CLOSED.\n"); //Eğer yorum satırı kapanmadıysa dosyaya hata mesajı yazdırır.
                    break;
                }
            }

            if (operatorCheck(input[right]) == true) {
                if (input[right] == '+') {
                    if (input[right+1] == '+') {
                        fprintf(fileLEX, "Operator(++)\n"); //++'yı tek bir operator tokeni olarak yazdırır.
                        right++;
                    }
                    else {
                        fprintf(fileLEX, "Operator(%c)\n", input[right]); //Sadece + operatorünü yazdırır.
                    }
                }

                else if(input[right] == ':') {
                    if (input[right+1] == '=') {
                        fprintf(fileLEX, "Operator(:=)\n"); //:='i tek bir operator tokeni olarak yazdırır.
                        right++;
                    }
                    else {
                        fprintf(fileLEX, "Operator(%c)\n", input[right]); //Sadece : operatorünü yazdırır.
                    }
                }

                else if(input[right] == '-') {
                    if (input[right+1] == '-') {
                        fprintf(fileLEX, "Operator(--)\n"); //--'yi tek bir operator tokeni olarak yazdırır.
                        right++;
                    }
                    else {
                        fprintf(fileLEX, "Operator(%c)\n", input[right]); //Sadece - operatorünü yazdırır.
                    }
                }

                else {
                    fprintf(fileLEX, "Operator(%c)\n", input[right]);
                }
            }

            if (input[right] == '(') {
                fprintf(fileLEX, "LeftPar\n"); //Sol parantezi algılayıp output dosyasına yazdırır.
            }
            if (input[right] == ')') {
                fprintf(fileLEX, "RightPar\n"); //Sağ parantezi algılayıp output dosyasına yazdırır.
            }
            if (input[right] == '[') {
                fprintf(fileLEX, "LeftSquareBracket\n"); //Sol köşeli parantezi algılayıp output dosyasına yazdırır.
            }
            if (input[right] == ']') {
                fprintf(fileLEX, "RightSquareBracket\n"); //Sağ köşeli parantezi algılayıp output dosyasına yazdırır.
            }
            if (input[right] == '{') {
                fprintf(fileLEX, "LeftCurlyBracket\n"); //Sol süslü parantezi algılayıp output dosyasına yazdırır.
            }
            if (input[right] == '}') {
                fprintf(fileLEX, "RightCurlyBracket\n"); //Sağ süslü parantezi algılayıp output dosyasına yazdırır.
            }

            if (input[right] == ';') {
                fprintf(fileLEX, "END OF LINE\n"); //Eğer ; konduysa end of line (satır sonu) olarak algılar ve output dosyasına yazdırır.
            }

            right++;
            left = right;
        }
        else if (delimiterCheck(input[right]) == true && left != right
                 || (right == len && left != right)) {
            char* subStr = subString(input, left, right - 1);

            if (keywordCheck(subStr) == true)
                fprintf(fileLEX, "Keyword(%s)\n", subStr); //Karakterleri inceleyip substringlere ayırdıktan sonra keyword olması durumunda bunu belirtir ve output dosyasına yazdırır.

            else if (identifierCheck(subStr) == true
                     && delimiterCheck(input[right - 1]) == false)
                if(strlen(subStr) > 30) {
                    printf("ERROR! IDENTIFIER NAMES CANNOT BE MORE THAN 30 CHARACTERS.\n"); //Eğer identifier 30 karakterden uzun olursa hata verir ve bunu konsola yazdırır.
                    fprintf(fileLEX, "ERROR! IDENTIFIER NAMES CANNOT BE MORE THAN 30 CHARACTERS.\n"); //Eğer identifier 30 karakterden uzun olursa hata verir ve hatayı output dosyasına yazdırır.
                }
                else {
                    fprintf(fileLEX, "Identifier(%s)\n", subStr); //Eğer keyword değilse ve 30 karakterden kısaysa identifier olarak output dosyasına yazdırır.
                }

            else if (integerCheck(subStr) == true) {
                if(strlen(subStr) > 10) {
                    printf("ERROR! INTEGER SIZE CANNOT BE MORE THAN 10 DIGITS.\n"); //10 basamaktan uzun tam sayı olursa hata verir ve bunu konsola yazdırır.
                    fprintf(fileLEX, "ERROR! INTEGER SIZE CANNOT BE MORE THAN 10 DIGITS.\n"); //10 basamaktan uzun tam sayı olursa hata verir ve hatayı output dosyasına yazdırır.
                }
                else {
                    fprintf(fileLEX, "IntConst(%s)\n", subStr); //Eğer 10 basamaktan kısaysa output dosyasına yazdırır.
                }
            }
            left = right;
        }
    }
    fclose(fileLEX);
}

int main() {
    char character, *chars;
    int i = 0;

    FILE *filePSI = fopen("code.psi", "r"); //code.psi isimli dosyayı okur. Okuması yapılacak psi dosyasının yeri projenin içerisinde olmalıdır.
    //Eğer text dosyası olarak input girilecekse code.psi.txt olarak değiştirilmelidir.
    // Kodu CLion IDE'sinde yazdığım için input dosyası cmake-build-debug klasörünün (main.exeden dolayı) içinde olmalıdır.
    if (filePSI == NULL) {
        printf("ERROR: FILE DOES NOT EXIST, NO SUCH FILE OR DIRECTORY, ANALYZER CANNOT FIND THE FILE SPECIFIED"); //Eğer böyle bir dosya bulamadıysa hata verecektir.
    }

    chars = malloc(1000);

    while ((character = fgetc(filePSI)) != EOF)
    {
        if(character == '\n' ) {
            character = ' '; //Dosyadaki her bir karakteri teker teker okuyarak bir diziye atmaktadır eğer sıradaki karakter \n ise bunu boşluk karakteri ile değiştirip
                             //herhangi bir hata olmasını engellemektedir. Bunun amacı "\n" komutunu bir identifier olarak algılamasını engellemektir (Boşluk olarak algılıyor.)
        }
        chars[i++] = (char) tolower(character); //Psi++ dili büyük karakter duyarlı bir dil değildir bu yüzden her bir karakteri küçük harfe çevirip işlem yapmaktadır.
    }

    chars[i] = '\0';

    fclose(filePSI);
    parse(chars);

    return 0;
}