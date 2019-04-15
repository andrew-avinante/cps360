#ifndef VFS_RAM_H
#define VFS_RAM_H

extern struct vfs_ops ramfs_vfs_ops;

void raminit();

struct vfile* ramfs_create(char *, short, short, short);
void ramfs_stati(struct vfile *, struct stat *st);
void ramfs_ilock(struct vfile*);
void ramfs_iunlock(struct vfile*);
void ramfs_iput(struct vfile*);
int ramfs_writei(struct vfile*, char *src, uint off, uint n);
int ramfs_readi(struct vfile*, char *src, uint off, uint n);

#endif