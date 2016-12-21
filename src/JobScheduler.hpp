#ifndef GRAPHSHORTESTPATHS_JOBSCHEDULER_H
#define GRAPHSHORTESTPATHS_JOBSCHEDULER_H

#include <stdint.h>
#include <pthread.h>

#include "Garray.hpp"

class Job {
public:
    Job(const uint32_t &id, const uint32_t &source, const uint32_t &target) : job_id_(id),
     source_(source), target_(target) { }
    uint32_t &getJobId() { return job_id_; }
    virtual int serve() = 0;

protected:
    uint32_t job_id_;
    uint32_t source_;
    uint32_t target_;
};

class DynamicJob : public Job {
public:
    DynamicJob(const uint32_t &id, const uint32_t &source, const uint32_t &target) : Job(id, source, target) { }
    int serve();
};

class StaticJob : public Job {
public:
    StaticJob(const uint32_t &id, const uint32_t &source, const uint32_t &target) : Job(id, source, target) { }
    int serve();
};

class JobScheduler {
public:
    JobScheduler(const uint8_t &pool_size, Garray<uint32_t> &resarr);
    ~JobScheduler();
    void submitJob(Job *job);
    void executeAllJobs();
    void waitAllTasksFinish();

private:
    static void *threadExecute(void *);
    void serve();

    uint8_t execution_threads_;
    Garray<pthread_t> thread_pool_;
    Garray<Job*> job_queue_;
    Garray<uint32_t> &result_arr_;
    pthread_mutex_t queue_mutex_;
    pthread_cond_t cond_nonempty_;
    // pthread_cond_t cond_nonfull_;

};

#endif
