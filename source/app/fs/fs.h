#ifndef _FS_H
#define _FS_H

int spiffs_init(void);

char *readf_to_string( char *filename);

#endif /*_FS_H*/