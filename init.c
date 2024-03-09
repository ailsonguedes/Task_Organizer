#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_DESC 100
#define TASKS_FILE "./src/tasks.txt"

typedef struct {
    char description[MAX_TASK_DESC];
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks() {
    FILE* file = fopen(TASKS_FILE, "r");
    if (file == NULL) return;

    taskCount = 0;
    while (fgets(tasks[taskCount].description, MAX_TASK_DESC, file) != NULL) {
        tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] =
            0;  // Remove newline character
        taskCount++;
    }

    fclose(file);
}

void saveTasks() {
    FILE* file = fopen(TASKS_FILE, "w");
    if (file == NULL) return;

    for (int i = 0; i < taskCount; i++) { fprintf(file, "%s\n", tasks[i].description); }

    fclose(file);
}

void addTask(char* description) {
    if (taskCount >= MAX_TASKS) {
        printf("Não é possível adicionar mais tarefas.\n");
        return;
    }
    strcpy(tasks[taskCount].description, description);
    taskCount++;
    saveTasks();  // Salva as tarefas no arquivo após adicionar uma nova
}

// As funções removeTask, listTasks e o main podem permanecer as mesmas, com a adição de loadTasks() no início do main.

void removeTask(int index) {
    if (index < 0 || index >= taskCount) {
        printf("Índice de tarefa inválido.\n");
        return;
    }
    for (int i = index; i < taskCount - 1; i++) { tasks[i] = tasks[i + 1]; }
    taskCount--;
}

void listTasks() {
    printf("Tarefas:\n");
    for (int i = 0; i < taskCount; i++) { printf("%d %s\n", i + 1, tasks[i].description); }
}

int main() {
    loadTasks();
    int choice;
    char description[MAX_TASK_DESC];

    while (1) {
        printf(
            "\nEscolha uma Opção Abaixo\n\n1. Adicionar Tarefa\n2. Remover Tarefa\n3. Listar "
            "Tarefa\n4. Sair\n");
        scanf("%d", &choice);
        getchar();  // Consume newline character

        switch (choice) {
            case 1:
                printf("Descrição da Tarefa: ");
                fgets(description, MAX_TASK_DESC, stdin);
                description[strcspn(description, "\n")] = 0;  // Remove newline character
                addTask(description);
                break;
            case 2:
                printf("Número de tarefa a ser removida: ");
                scanf("%d", &choice);
                removeTask(choice - 1);
                break;
            case 3:
                listTasks();
                break;
            case 4:
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
