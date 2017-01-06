#ifndef GRAPHSHORTESTPATHS_JOBSCHEDULER_H
#define GRAPHSHORTESTPATHS_JOBSCHEDULER_H

#include <stdint.h>
#include <pthread.h>

#include "Garray.hpp"
#include "ShortestPath.hpp"
#include "SCC.hpp"
#include "CC.hpp"
#include "GrailIndex.hpp"

class Job {
public:
    Job(const uint32_t &id, const uint32_t &source, const uint32_t &target, Garray<ShortestPath *> &path) : job_id_(id),
     source_(source), target_(target), paths_(path) { }
    uint32_t getJobId() { return job_id_; }
    uint32_t getSource() const {return source_;}
    uint32_t getTarget() const { return target_;}
    virtual int serve(const uint32_t &id) = 0;

protected:
    uint32_t job_id_;
    uint32_t source_;
    uint32_t target_;
    Garray<ShortestPath *> &paths_;
};

class DynamicJob : public Job {
public:
    DynamicJob(const uint32_t &id, const uint32_t &source, const uint32_t &target, const uint32_t &current_version, Garray<ShortestPath *> &path, CC &cc, const char &mode) :
    Job(id, source, target, path), current_version_(current_version), cc_(cc), mode_(mode) { }
    int serve(const uint32_t &id);

private:
    uint32_t current_version_;
    CC &cc_;
    char mode_; // Decides index usage

};

class StaticJob : public Job {
public:
    StaticJob(const uint32_t &id, const uint32_t &source, const uint32_t &target, Garray<ShortestPath *> &path, SCC &scc, GrailIndex &grail) :
    Job(id, source, target, path), scc_(scc), grail_(grail) { }
    int serve(const uint32_t &id);

private:
    SCC &scc_;
    GrailIndex &grail_;

};

class JobScheduler {
public:
    JobScheduler(const uint32_t &pool_size, Garray<int> &resarr);
    ~JobScheduler();
    void submitJob(Job *job);
    void executeAllJobs();
    void waitAllTasksFinish(const uint32_t &total_tasks);
    void terminateThreads();

private:
    struct thread_args {
        thread_args(JobScheduler *obj, const uint32_t &id) : object(obj), thread_id(id) { }

        JobScheduler *object;
        uint32_t thread_id;
    };

    static void *threadExecute(void *);
    void serve(const uint32_t &id);
    void jobAssignmentPerThread();

    uint32_t execution_threads_;
    uint32_t total_finished;
    Garray<uint32_t> jobs_per_thread;
    Garray<pthread_t> thread_pool_;
    Garray<Job*> job_queue_;
    Garray<bool> served_;
    Garray<bool> termination_;
    Garray<int> &result_arr_;
    pthread_mutex_t queue_mutex_;
    pthread_cond_t cond_nonempty_;
    pthread_mutex_t lockf_;
    pthread_cond_t finished_;
    pthread_mutex_t served_mutex_;
    pthread_cond_t cond_served_;
    // pthread_cond_t cond_nonfull_;

};

#endif
