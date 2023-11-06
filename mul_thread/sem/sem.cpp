 #include <iostream>
 #include <thread>
 #include <semaphore>
 using namespace std;
 
 counting_semaphore sema(1);
 counting_semaphore semb(0);
 counting_semaphore semc(0);
 
 
 void pthread_fun1() //线程函数 1 打印 a
 {
     int i = 0;
     for (; i < 10; ++i)
     {
     sema.acquire();
     cout << "A" << endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(200));
     semb.release();
     }
 }
 void pthread_fun2() //线程函数 2 打印 l
 {
     int i = 0;
     for (; i < 10; ++i)
     {
          semb.acquire();
          cout << "B" << endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(200));
          semc.release();
     }
 }
 void pthread_fun3() //线程函数 3 打印 i
 {
     int i = 0;
     for (; i < 10; ++i)
     {
          semc.acquire();
          cout << "C" << endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(200));
          sema.release();
     }
 }
 int main()
 {
     thread s1(pthread_fun1);
     thread s2(pthread_fun2);
     thread s3(pthread_fun3);
     s1.join();
     s2.join();
     s3.join();
     return 0;
 }