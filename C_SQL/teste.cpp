#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>
#include <conio.h> // para o uso de getch()

#define USUARIO_VALIDO "admin"  // Usu�rio pr�-definido
#define SENHA_VALIDO "123456"   // Senha pr�-definida

char *LerSenha(int max);
char *LerUsuario(int max);
void LerDadosFuncionario(int *chapa, char *nome, char *data, char *funcao, char *hora);

int main() {
    // Vari�veis para o login e senha
    char *Key;
    char *User;

    // Ler usu�rio
    printf("login: \n");
    User = LerUsuario(100);
    printf("\n");

    // Ler senha
    printf("senha: \n");
    Key = LerSenha(8);
    printf("\n");

    // Verificar credenciais
    if (strcmp(User, USUARIO_VALIDO) != 0 || strcmp(Key, SENHA_VALIDO) != 0) {
        printf("Usu�rio ou senha inv�lidos!\n");
        free(User);
        free(Key);
        return EXIT_FAILURE;
    }

    // Inicializar a estrutura de conex�o
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Falha na inicializa��o do MySQL: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Conectar ao banco de dados
    if (mysql_real_connect(conn, "localhost", USUARIO_VALIDO, SENHA_VALIDO, "banco_de_dados", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Conex�o ao banco de dados bem-sucedida!\n");

    // Dados do funcion�rio
    int chapa;
    char nome[100];
    char data[11];   // Formato YYYY-MM-DD
    char funcao[100];
    char hora[9];    // Formato HH:MM:SS

    // Ler dados do funcion�rio
    LerDadosFuncionario(&chapa, nome, data, funcao, hora);

    // Preparar a query SQL para inser��o ou atualiza��o
    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO ponto_dos_funcionarios (chapa, nome, data, funcao, hora) "
             "VALUES (%d, '%s', '%s', '%s', '%s') "
             "ON DUPLICATE KEY UPDATE nome = VALUES(nome), data = VALUES(data), funcao = VALUES(funcao), hora = VALUES(hora);",
             chapa, nome, data, funcao, hora);

    // Executar a query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Falha ao executar a query: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Dados inseridos ou atualizados com sucesso!\n");

    // Fechar a conex�o
    mysql_close(conn);

    // Libera a mem�ria alocada
    free(User);
    free(Key);

    return EXIT_SUCCESS;
}

void LerDadosFuncionario(int *chapa, char *nome, char *data, char *funcao, char *hora) {
    // Ler dados do funcion�rio
    printf("Digite a chapa do funcion�rio: ");
    scanf("%d", chapa);
    getchar(); // Limpar o buffer de entrada

    printf("Digite o nome do funcion�rio: ");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha do final

    printf("Digite a data (YYYY-MM-DD): ");
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove a nova linha do final

    printf("Digite a fun��o do funcion�rio: ");
    fgets(funcao, 100, stdin);
    funcao[strcspn(funcao, "\n")] = '\0'; // Remove a nova linha do final

    printf("Digite a hora (HH:MM:SS): ");
    fgets(hora, 9, stdin);
    hora[strcspn(hora, "\n")] = '\0'; // Remove a nova linha do final
}

char *LerSenha(int max) {
    int i = 0;
    char *Key = (char *)malloc(sizeof(char) * (max + 1)); // +1 para o caractere nulo
    if (Key == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para senha.\n");
        exit(EXIT_FAILURE);
    }

    // Ler a senha sem mostrar os caracteres (substitui por '*')
    while (i < max) {
        Key[i] = getch();
        if (Key[i] == 13) { // 13 � o c�digo ASCII de Enter
            break;
        }
        putchar('*'); // Mostrar '*' em vez da senha
        i++;
    }
    Key[i] = '\0'; // Terminar a string com nulo

    return Key;
}

char *LerUsuario(int max) {
    int i = 0;
    char *User = (char *)malloc(sizeof(char) * (max + 1)); // +1 para o caractere nulo
    if (User == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para usu�rio.\n");
        exit(EXIT_FAILURE);
    }

    // Ler o usu�rio (normalmente vis�vel)
    while (i < max) {
        User[i] = getch();
        if (User[i] == 13) { // 13 � o c�digo ASCII de Enter
            break;
        }
        putchar(User[i]); // Mostrar os caracteres
        i++;
    }
    User[i] = '\0'; // Terminar a string com nulo

    return User;
}

