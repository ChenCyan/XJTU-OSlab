#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define DEVICE_FILE "/dev/globalvar"

int main() {
    int fd;
    int data;
    char buf[128];
    
    // 打开字符设备
    fd = open(DEVICE_FILE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    
    // 模拟设备写入
    printf("Enter a number to write to the device: ");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &data);

    if (write(fd, &data, sizeof(data)) < 0) {
        perror("Failed to write to device");
        close(fd);
        return -1;
    }
    printf("Data written to the device: %d\n", data);
    
    // 模拟设备读取
    if (read(fd, &data, sizeof(data)) < 0) {
        perror("Failed to read from device");
        close(fd);
        return -1;
    }
    printf("Data read from the device: %d\n", data);

    // 关闭设备
    close(fd);
    return 0;
}

