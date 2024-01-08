#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <btrfs/ioctl.h>

int inode_lookup(int fd, __u64 inode) {
    struct btrfs_ioctl_ino_lookup_args args = {
        .treeid = 0,
        .objectid = inode,
    };

    if (ioctl(fd, BTRFS_IOC_INO_LOOKUP, &args) < 0) {
        perror("ioctl(BTRFS_IOC_INO_LOOKUP)");
        return 1;
    }

    printf("name: %s\n", args.name);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <path> <inode>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    __u64 inode = atoll(argv[2]);

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    inode_lookup(fd, inode);

    close(fd);
    return 0;
}
