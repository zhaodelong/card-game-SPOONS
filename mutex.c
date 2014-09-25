//Description:这个程序是测试pthread_mutex对多线程上锁。
#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex; //~ 创建互斥锁mutex
int share = 0; //~ 共享数据
string sharestr="a";

//~ 线程入口
void * thread_function(void *arg)
{
        const int N = 1000000;
        for(int i = 0; i < N; ++i)
        {
                //~ 访问共享数据
                pthread_mutex_lock(&mutex);
                share++;
                usleep(1000);
               if(i%100000==0)
                        sharestr.append("b");
                pthread_mutex_unlock(&mutex);
        }
}
int
main()
{
        pthread_mutex_init(&mutex, NULL); //~ 初始化互斥锁mutex
        pthread_t thread_id;
        void *exit_status;
        pthread_create(&thread_id, NULL, thread_function, NULL); //~ 创建新线程
        for(int i = 0; i < 10; ++i)
        {
                usleep(10000); //~ 延时10ms
                //~ 访问共享数据
                pthread_mutex_lock(&mutex);
                cout<<share<<endl;
                cout<<sharestr<<endl;
               pthread_mutex_unlock(&mutex);
        }
        cout<<"waiting pthread finished"<<endl;
        pthread_join(thread_id, &exit_status); //~ 等待线程结束
        cout<<"destroy pthread mutex"<<endl;
        pthread_mutex_destroy(&mutex); //~ 销毁互斥锁
        cout<<"destroy pthread mutex finished"<<endl;
        return 0;
}
