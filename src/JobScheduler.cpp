#include "JobScheduler.hpp"

#include <iostream>


JobScheduler::JobScheduler(const uint8_t &pool_size, Garray<uint32_t> &resarr) : execution_threads_(pool_size),
 thread_pool_(execution_threads_), result_arr_(resarr) {
    pthread_mutex_init(&queue_mutex_, 0);
    pthread_cond_init(&cond_nonempty_, 0);
    // pthread_cond_init(&cond_nonfull_, 0);

    for (uint32_t i = 0; i < execution_threads_; i++)
        pthread_create(&thread_pool_[i], 0, threadExecute, this);
}

JobScheduler::~JobScheduler() {
    // pthread_cond_destroy(&cond_nonfull_);
    pthread_cond_destroy(&cond_nonempty_);
    pthread_mutex_destroy(&queue_mutex_);

    for (uint32_t i = 0; i < execution_threads_; i++)
        pthread_detach(thread_pool_[i]);
}

void *JobScheduler::threadExecute(void *object) {
    ((JobScheduler *)object)->serve();
}

void JobScheduler::serve() {
    Job *exec_job = NULL;
    int result = 0;

    while (true) {
        pthread_mutex_lock(&queue_mutex_);
        while (job_queue_.getSize() <= 0)
            pthread_cond_wait(&cond_nonempty_, &queue_mutex_);
        exec_job = job_queue_.popFront();
        pthread_mutex_unlock(&queue_mutex_);

        result = exec_job->serve();
        result_arr_[exec_job->getJobId()] = result;
    }
}

void JobScheduler::submitJob(Job *job) {
    pthread_mutex_lock(&queue_mutex_);
    job_queue_.enstack(job);
    pthread_mutex_unlock(&queue_mutex_);
}

void JobScheduler::executeAllJobs() {
    pthread_cond_signal(&cond_nonempty_);
}
