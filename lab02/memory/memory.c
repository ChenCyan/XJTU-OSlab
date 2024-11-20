#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROCESS_NAME_LEN 32 /*进程名长度*/
#define MIN_SLICE 10        /*最小碎片的大小*/
#define DEFAULT_MEM_SIZE 1024 /*内存大小*/
#define DEFAULT_MEM_START 0 /*起始位置*/

/* 内存分配算法 */
#define MA_FF 1
#define MA_BF 2
#define MA_WF 3

/* 数据结构定义 */
struct free_block_type {
    int size;
    int start_addr;
    struct free_block_type *next;
};

struct allocated_block {
    int pid;
    int size;
    int start_addr;
    char process_name[PROCESS_NAME_LEN];
    struct allocated_block *next;
};

/* 全局变量 */
struct free_block_type *free_block;
struct allocated_block *allocated_block_head = NULL;
int mem_size = DEFAULT_MEM_SIZE;
int ma_algorithm = MA_FF;
static int pid = 0;
int flag = 0;

/* 函数声明 */
struct free_block_type* init_free_block(int mem_size);
void display_menu();
void set_mem_size();
void set_algorithm();
void rearrange(int algorithm);
void rearrange_BF();
void rearrange_WF();
void new_process();
int allocate_mem(struct allocated_block *ab);
void kill_process();
struct allocated_block *find_process(int pid);
int free_mem(struct allocated_block *ab);
int dispose(struct allocated_block *free_ab);
void display_mem_usage();

/* 函数实现 */

/* 初始化空闲块 */
struct free_block_type* init_free_block(int mem_size) {
    struct free_block_type *fb = (struct free_block_type *)malloc(sizeof(struct free_block_type));
    if (fb == NULL) {
        printf("No mem\n");
        return NULL;
    }
    fb->size = mem_size;
    fb->start_addr = DEFAULT_MEM_START;
    fb->next = NULL;
    return fb;
}

/* 显示菜单 */
void display_menu() {
    printf("\n");
    printf("1 - Set memory size (default=%d)\n", DEFAULT_MEM_SIZE);
    printf("2 - Select memory allocation algorithm\n");
    printf("3 - New process \n");
    printf("4 - Terminate a process \n");
    printf("5 - Display memory usage \n");
    printf("0 - Exit\n");
}

/* 设置内存大小 */
void set_mem_size() {
    int size;
    if (flag != 0) {
        printf("Cannot set memory size again\n");
        return;
    }
    printf("Total memory size = ");
    scanf("%d", &size);
    if (size > 0) {
        mem_size = size;
        free_block->size = mem_size;
    }
    flag = 1;
}

/* 设置当前分配算法 */
void set_algorithm() {
    int algorithm;
    printf("\t1 - First Fit\n");
    printf("\t2 - Best Fit \n");
    printf("\t3 - Worst Fit \n");
    scanf("%d", &algorithm);
    if (algorithm >= 1 && algorithm <= 3)
        ma_algorithm = algorithm;
    rearrange(ma_algorithm);
}

/* 按指定算法重新排列空闲区 */
void rearrange(int algorithm) {
    switch (algorithm) {
        case MA_FF: /* First Fit 无需特殊排序 */ break;
        case MA_BF: rearrange_BF(); break;
        case MA_WF: rearrange_WF(); break;
    }
}

/* 按 BF 算法重新整理空闲区链表 */
void rearrange_BF() {
    struct free_block_type *current, *prev, *min, *min_prev, *sorted = NULL;
    while (free_block != NULL) {
        min = free_block;
        min_prev = NULL;
        prev = free_block;
        current = free_block->next;

        while (current != NULL) {
            if (current->size < min->size) {
                min = current;
                min_prev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (min_prev != NULL) min_prev->next = min->next;
        else free_block = free_block->next;

        min->next = sorted;
        sorted = min;
    }
    free_block = sorted;
}

/* 按 WF 算法重新整理空闲区链表 */
void rearrange_WF() {
    struct free_block_type *current, *prev, *max, *max_prev, *sorted = NULL;
    while (free_block != NULL) {
        max = free_block;
        max_prev = NULL;
        prev = free_block;
        current = free_block->next;

        while (current != NULL) {
            if (current->size > max->size) {
                max = current;
                max_prev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (max_prev != NULL) max_prev->next = max->next;
        else free_block = free_block->next;

        max->next = sorted;
        sorted = max;
    }
    free_block = sorted;
}

/* 创建新进程 */
void new_process() {
    struct allocated_block *ab;
    int size, ret;
    ab = (struct allocated_block *)malloc(sizeof(struct allocated_block));
    if (!ab) exit(-5);

    ab->next = NULL;
    pid++;
    sprintf(ab->process_name, "PROCESS-%02d", pid);
    ab->pid = pid;

    printf("Memory for %s: ", ab->process_name);
    scanf("%d", &size);
    if (size > 0) ab->size = size;

    ret = allocate_mem(ab);
    if (ret == 1) {
        if (allocated_block_head == NULL) {
            allocated_block_head = ab;
        } else {
            ab->next = allocated_block_head;
            allocated_block_head = ab;
        }
    } else {
        printf("Allocation fail\n");
        free(ab);
    }
}

/* 分配内存 */
int allocate_mem(struct allocated_block *ab) {
    struct free_block_type *current = free_block, *prev = NULL;
    int request_size = ab->size;

    rearrange(ma_algorithm);

    while (current != NULL) {
        if (current->size >= request_size) {
            ab->start_addr = current->start_addr;

            if (current->size - request_size >= MIN_SLICE) {
                current->start_addr += request_size;
                current->size -= request_size;
            } else {
                if (prev != NULL) prev->next = current->next;
                else free_block = current->next;
                free(current);
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return -1;
}

/* 终止进程 */
void kill_process() {
    struct allocated_block *ab;
    int pid;
    printf("Kill Process, pid = ");
    scanf("%d", &pid);
    ab = find_process(pid);
    if (ab != NULL) {
        free_mem(ab);
        dispose(ab);
    }
}

/* 找到进程 */
struct allocated_block *find_process(int pid) {
    struct allocated_block *ab = allocated_block_head;
    while (ab != NULL) {
        if (ab->pid == pid) return ab;
        ab = ab->next;
    }
    return NULL;
}

/* 释放内存 */
int free_mem(struct allocated_block *ab) {
    struct free_block_type *current = free_block, *prev = NULL, *new_block;

    new_block = (struct free_block_type *)malloc(sizeof(struct free_block_type));
    if (!new_block) return -1;

    new_block->start_addr = ab->start_addr;
    new_block->size = ab->size;
    new_block->next = NULL;

    while (current != NULL && current->start_addr < new_block->start_addr) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        new_block->next = free_block;
        free_block = new_block;
    } else {
        new_block->next = current;
        prev->next = new_block;
    }

    current = free_block;
    while (current != NULL && current->next != NULL) {
        if (current->start_addr + current->size == current->next->start_addr) {
            current->size += current->next->size;
            struct free_block_type *temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    return 1;
}

/* 释放进程描述节点 */
int dispose(struct allocated_block *free_ab) {
    struct allocated_block *prev = NULL, *ab = allocated_block_head;

    if (free_ab == allocated_block_head) {
        allocated_block_head = allocated_block_head->next;
        free(free_ab);
        return 1;
    }

    while (ab != free_ab && ab != NULL) {
        prev = ab;
        ab = ab->next;
    }

    if (ab == NULL) return -1;

    prev->next = ab->next;
    free(ab);

    return 2;
}

/* 显示内存使用情况 */
void display_mem_usage() {
    struct free_block_type *fb = free_block;
    struct allocated_block *ab = allocated_block_head;

    printf("----------------------------------------------------------\n");
    printf("Free Memory:\n");
    while (fb != NULL) {
        printf("Address: %d, Size: %d\n", fb->start_addr, fb->size);
        fb = fb->next;
    }

    printf("----------------------------------------------------------\n");
    printf("Allocated Memory:\n");
    while (ab != NULL) {
        printf("PID: %d, Process Name: %s, Address: %d, Size: %d\n",
               ab->pid, ab->process_name, ab->start_addr, ab->size);
        ab = ab->next;
    }

    printf("----------------------------------------------------------\n");
}

/* 主函数 */
int main() {
    int choice;
    free_block = init_free_block(mem_size);

    while (1) {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: set_mem_size(); break;
            case 2: set_algorithm(); break;
            case 3: new_process(); break;
            case 4: kill_process(); break;
            case 5: display_mem_usage(); break;
            case 0: exit(0);
            default: break;
        }
    }

    return 0;
}

