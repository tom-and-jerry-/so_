#include <iostream>
#include <pthread.h>


#include <cstdio>

typedef pthread_mutex_t Mutex;

using namespace std;

void wait(Mutex &m) {
  pthread_mutex_lock(&m);
}
void signal(Mutex &m) {
  pthread_mutex_unlock(&m);
}

class rw_lock {
 public:
  rw_lock() : read_count(0) {}

  void read_lock() {
    wait(mt_read);
    if (++read_count == 1) {
      wait(mt_write);
    }
    signal(mt_read);
  }

  void read_unlock() {  
    wait(mt_read);
    if (--read_count == 0) {
      signal(mt_write);
    }
    signal(mt_read);
  }

  void write_lock() {
    wait(mt_write);
  }

  void write_unlock() { 
    signal(mt_write);
  }

 private:
  Mutex mt_write;
  Mutex mt_read;
  int read_count;
};


int main() {
  return 0;
}
