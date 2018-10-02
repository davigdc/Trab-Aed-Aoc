#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

char hexCode(char code[]) {

    if(!strcmp( code, "An;")){
       //cout << "An\n";
       return '0';
    }
    else if(!strcmp(code, "nAoB;")){
       //cout << "nAoB\n";
       return '1';
    }
    else if(!strcmp(code, "AnB;")){
       //cout << "AnB\n";
       return '2';
    }
    else if(!strcmp(code, "zeroL;")){
       //cout << "zeroL\n";
       return '3';
    }
    else if(!strcmp(code, "nAeB;")){
       //cout << "nAeB\n";
       return '4';
    }
    else if(!strcmp(code, "Bn;")){
       //cout << "Bn\n";
       return '5';
    }
    else if(!strcmp(code, "AxB;")){
       //cout << "AxB\n";
       return '6';
    }
    else if(!strcmp(code, "ABn;")){
       //cout << "ABn\n";
       return '7';
    }
    else if(!strcmp(code, "AnoB;")){
       //cout << "AnoB\n";
       return '8';
    }
    else if(!strcmp(code, "nAxB;")){
       //cout << "nAxB\n";
       return '9';
    }
    else if(!strcmp(code, "B;")){
       //cout << "B\n";
       return 'A';
    }
    else if(!strcmp(code, "AB;")){
       //cout << "AB\n";
       return 'B';
    }
    else if(!strcmp(code, "umL;")){
       //cout << "umL\n";
       return 'C';
    }
    else if(!strcmp(code, "AoBn;")){
       //cout << "AoBn\n";
       return 'D';
    }
    else if(!strcmp(code, "AoB;")){
       //cout << "AoB\n";
       return 'E';
    }
    else if(!strcmp(code, "A;")){
       //cout << "A\n";
       return 'F';
    }
    //else { cout << "\nH� um problema de sintaxe no arquivo: "<<code; }
    return '\n';
}


void Define_Valores(char *v, char &a, char &b, char &c, bool &atribuicao, int &atri_a, int &b_int, int &ins_c){

    bool Mnemonico=true;
    int aux = 0;
    for(int i = 1; i < 8; i++){
        if(v[i] == '='){    // Valor de A e B
        Mnemonico = false;
            if(v[i-1] == 'A'){
               a=v[i+1];
               atri_a++;
            }
            if(v[i-1] == 'B'){
                b=v[i+1];
                b_int++;
            }
        }

        if(Mnemonico){
            aux = 1;
            c=hexCode(v);
            atribuicao= true;
        }
    }
    ins_c += aux;
}


int main(){

    FILE *arq= fopen("74181.alu", "r");
    if(arq==NULL) //Verifica se o arquivo � nulo
    {
        printf("\nErro ao abrir arquivo .alu\n");
        return 1;
    }

    FILE *arq_hex= fopen("74181.hex", "w+");
    if(arq==NULL) //Verifica se o arquivo � nulo
    {
        printf("\nErro ao abrir arquivo .alu\n");
        return 1;
    }

    FILE *arq_log= fopen("74181.log", "a+");
    if(arq==NULL) //Verifica se o arquivo � nulo
    {
        printf("\nErro ao abrir arquivo .alu\n");
        return 1;
    }

    clock_t t;
    t = clock();

    char linha[5];
    char a, b, c;
    bool atribuicao;
    int line_alu=0,line_hex=0, atri_a=0, atri_b=0, ins_c=0;

    time_t t2 = time(NULL);
    struct tm *tm = localtime(&t2);
    char s[64];
    strftime(s, sizeof(s), "%d/%m/%Y %X", tm);
    fprintf(arq_log, "%s\n", s);

    if(arq){
        cout<<"\tLendo arquivo...\n";
        while(!feof(arq)){
            if(!feof(arq)){
                line_alu++;
                fscanf(arq, "%[^\n]\n", linha);
                if(!strcmp("inicio:", linha) || !strcmp("fim.", linha)){
                    //cout<<endl<<"Inicio ou fim do arquivo";
                } else {
                    atribuicao= false;
                    Define_Valores(linha, a, b, c, atribuicao, atri_a, atri_b, ins_c);
                    if(atribuicao){
                        //printf("\nValores: %c%c%c", a, b, c);
                        fprintf(arq_hex, "%c%c%c\n", a, b, c);
                        line_hex++;
                    }
                }
            }
        }
    }

    fprintf(arq_log, "Linhas .alu: %i linhas .hex: %i\n", line_alu, line_hex);
    fprintf(arq_log, "Atribuicoes feitas em A: %i, atribuicoes feitas em B: %i\n", atri_a, atri_b);
    fprintf(arq_log, "Instrucoes (C): %i\n", ins_c);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    fprintf(arq_log, "%f segundos para executar \n\n", time_taken);

    fclose(arq);
    fclose(arq_hex);
    fclose(arq_log);

    return 0;
}
