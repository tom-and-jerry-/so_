#include <iostream>


template <typename T>
class smart_ptr {
public:
  smart_ptr(T *t) {
    //printf("CALL");
    this->ptr = t;
    this->ref_count = new int[1];
    *ref_count = 1;
  }
  smart_ptr(smart_ptr<T> &t) {
    //printf("CA");
    ptr = t.ptr;
    ref_count = t.ref_count;
    *ref_count += 1;
  }
  smart_ptr<T>& operator = (smart_ptr<T> &t) {
    return smart_ptr(t);
  }
  ~smart_ptr() {
    *ref_count -= 1;
    if (*ref_count == 0) {
      delete ref_count;
      delete ptr;
      ptr = nullptr;
      ref_count = nullptr;
    }
  }

  void print_state() {
    printf("Ref num:%d\n", *ref_count);
  }
private:
  T *ptr;
  int *ref_count;
};

int main() {
  int *ptr = new int[5]{1,2,3,4,5};

  smart_ptr<int> t(ptr);

  smart_ptr<int> t2(t);
  smart_ptr<int> *t3 = new smart_ptr<int>(t);

  delete t3;

  t.print_state();
  //t2.print_state();

}
