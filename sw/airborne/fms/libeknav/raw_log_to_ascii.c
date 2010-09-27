

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>




#include "fms/libeknav/raw_log.h"

void print_raw_log_entry(struct raw_log_entry*);
void build_fake_log(void);

#define PRT(a) printf("%f ", a);



int main(int argc, char** argv) {

  //  build_fake_log();

  const char* filename = "log_test3.bin";
  int raw_log_fd = open(filename, O_RDONLY); 
  
  if (raw_log_fd == -1) {
    perror("opening log\n");
    return -1;
  }
  
  while (1) {
    struct raw_log_entry e;
    ssize_t nb_read = read(raw_log_fd, &e, sizeof(e));
    if (nb_read != sizeof(e)) break;
    print_raw_log_entry(&e);
    //printf("%f %f %f %f", e.time, e.gyro.p, e.gyro.q, e.gyro.r);
    printf("\n");
  }

  return 0;
}



void print_raw_log_entry(struct raw_log_entry* entry){
	printf("%f\t", entry->time);
	printf("%+f %+f %+f\t", entry->gyro.p, entry->gyro.q, entry->gyro.r);
	printf("%+f %+f %+f\t", entry->accel.x, entry->accel.y, entry->accel.z);
	printf("%+f %+f %+f\t", entry->mag.x, entry->mag.y, entry->mag.z);
}



void build_fake_log(void) {
  int raw_log_fd = open( "log_test3.bin", O_WRONLY|O_CREAT, 00644);
  for (int i=0; i<5000; i++) {
    struct raw_log_entry e;
    e.time = i;
    write(raw_log_fd, &e, sizeof(e));
  }
  close(raw_log_fd);
}