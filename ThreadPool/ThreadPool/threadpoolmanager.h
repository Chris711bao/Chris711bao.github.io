

#pragma once

#include "stdafx.h"
#include "..\include\pthread.h"
typedef void (*task_fun)(void *);

class ThreadPool;
class TaskPool;

class ThreadPoolManager
{
public:
    ThreadPoolManager();
    ~ThreadPoolManager();

    
    int Init(const int &tastPoolSize,
            const int &threadPoolMax,
            const int &threadPoolPre);

    
    int Run(task_fun fun,void* arg=NULL);
	
public: //以下public函数主要用于静态函数调用
    bool GetStop();
    void TaskCondWait();
    TaskPool * GetTaskPool();
    ThreadPool * GetThreadPool();
    void LockTask();
    void UnlockTask();
    void LockFull();

private:
	static void * TaskThread(void*); //任务处理线程
	void StopAll();
    
private:
    ThreadPool *m_threadPool; //线程池
    TaskPool * m_taskPool; //任务池
    bool m_bStop; // 是否终止管理器
    
    pthread_t m_taskThreadId; // TaskThread线程id
	pthread_mutex_t m_mutex_task;
    pthread_cond_t m_cond_task;
};

