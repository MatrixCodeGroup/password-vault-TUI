#include <stdio.h>
#include <string.h>

struct Accounts {
    char service[100];
    char login[50];
    char pass[200];
};

int deleteacc(void)
{
    char line[1000];
    char delete[100];

    printf("What to delete: ");
    fgets(delete, sizeof(delete), stdin);
    delete[strcspn(delete, "\n")] = '\0';

    FILE *f = fopen("acc.txt", "r");
    FILE *tf = fopen("temp.txt", "w");

    if (f == NULL || tf == NULL) {
        printf("Error opening file.\n");
        if (f != NULL) fclose(f);
        if (tf != NULL) fclose(tf);
        return 1;
    }

    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, delete) != NULL) {
            continue;
        }

        fprintf(tf, "%s", line);
    }

    fclose(f);
    fclose(tf);

    remove("acc.txt");
    rename("temp.txt", "acc.txt");

    return 0;
}

int findacc(void)
{
    FILE *f = fopen("acc.txt", "r");

    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[500];
    char search[200];

    printf("Search >> ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, search) != NULL) {
            printf("\nFOUND!!\n");
            printf("%s", line);
        }
    }

    fclose(f);
    return 0;
}

int snowacc(void)
{
    FILE *f = fopen("acc.txt", "r");

    if (f == NULL) {
        printf("\n[!] No accounts found.\n\n");
        return 1;
    }

    char line[500];

    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║                  SAVED ACCOUNTS                ║\n");
    printf("╠════════════════════════════════════════════════╣\n");

    while (fgets(line, sizeof(line), f) != NULL) {
        printf("║  %s", line);
    }

    printf("╚════════════════════════════════════════════════╝\n\n");

    fclose(f);
    return 0;
}

int addacc(struct Accounts *account)
{
    FILE *f = fopen("acc.txt", "a");

    if (f == NULL) {
        printf("\n[!] Error opening file.\n");
        return 1;
    }

    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║                  ADD ACCOUNT                   ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    printf("  Service  >> ");
    fgets(account->service, sizeof(account->service), stdin);
    account->service[strcspn(account->service, "\n")] = '\0';

    printf("  Login    >> ");
    fgets(account->login, sizeof(account->login), stdin);
    account->login[strcspn(account->login, "\n")] = '\0';

    printf("  Password >> ");
    fgets(account->pass, sizeof(account->pass), stdin);
    account->pass[strcspn(account->pass, "\n")] = '\0';

    fprintf(f,
            "|%s |%s |%s |\n",
            account->pass,
            account->login,
            account->service);

    fclose(f);

    memset(account, 0, sizeof(*account));

    printf("\n[+] Account saved successfully!\n\n");

    return 0;
}

int main(void)
{
    char *art[] = {
        "█████▄ ▄████▄ ▄█████ ▄█████ ██     ██ ▄████▄ █████▄  ████▄    ██  ██ ▄████▄ ██  ██ ██    ██████",
        "██▄▄█▀ ██▄▄██ ▀▀▀▄▄▄ ▀▀▀▄▄▄ ██ ▄█▄ ██ ██  ██ ██▄▄██▄ ██  ██   ██▄▄██ ██▄▄██ ██  ██ ██      ██",
        "██     ██  ██ █████▀ █████▀  ▀██▀██▀  ▀████▀ ██   ██ ████▀     ▀██▀  ██  ██ ▀████▀ ██████  ██"
    };

    char choice;
    struct Accounts account;

    printf("\n%s\n%s\n%s\n\n", art[0], art[1], art[2]);

    do {
        printf("╔════════════════════════════════════════════════╗\n");
        printf("║                    MAIN MENU                   ║\n");
        printf("╠════════════════════════════════════════════════╣\n");
        printf("║  [1]  Add account                              ║\n");
        printf("║  [2]  Show accounts                            ║\n");
        printf("║  [3]  Find account                             ║\n");
        printf("║  [4]  Delete account                           ║\n");
        printf("║  [5]  Exit                                     ║\n");
        printf("╚════════════════════════════════════════════════╝\n");

        printf("\nChoice >> ");

        scanf(" %c", &choice);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {
            case '1':
                addacc(&account);
                break;

            case '2':
                snowacc();
                break;

            case '3':
                findacc();
                break;

            case '4':
                deleteacc();
                break;

            case '5':
                printf("\nGoodbye!\n\n");
                return 0;

            default:
                printf("\n[!] Unknown choice.\n\n");
        }

    } while (choice != '5');

    return 0;
}
