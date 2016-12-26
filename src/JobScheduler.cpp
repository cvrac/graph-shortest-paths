#include "JobScheduler.hpp"

#include <iostream>
#include <sys/signal.h>


JobScheduler::JobScheduler(const uint8_t &pool_size, Garray<int> &resarr) : execution_threads_(pool_size),
 total_finished(0), thread_pool_(execution_threads_), result_arr_(resarr) {
    pthread_mutex_init(&queue_mutex_, 0);
    pthread_cond_init(&cond_nonempty_, 0);
    pthread_mutex_init(&lockf_, 0);
    pthread_cond_init(&finished_, 0);
    pthread_mutex_init(&served_mutex_, 0);
    pthread_cond_init(&cond_served_, 0);

    served_.init(execution_threads_);
    served_.setElements(execution_threads_);
    jobs_per_thread.init(execution_threads_);
    jobs_per_thread.setElements(execution_threads_);
    termination_.init(execution_threads_);
    termination_.setElements(execution_threads_);


    for (uint32_t i = 0; i < execution_threads_; i++) {
        served_[i] = false;
        termination_[i] = false;
    }

    thread_args *args;
    for (uint32_t i = 0; i < execution_threads_; i++) {
        args = new thread_args(this, i);
        pthread_create(&thread_pool_[i], 0, threadExecute, args);
    }
}

JobScheduler::~JobScheduler() {
    pthread_cond_destroy(&cond_nonempty_);
    pthread_mutex_destroy(&queue_mutex_);
    pthread_mutex_destroy(&lockf_);
    pthread_cond_destroy(&finished_);
    pthread_mutex_destroy(&served_mutex_);
    pthread_cond_destroy(&cond_served_);

    for (uint32_t i = 0; i < execution_threads_; i++) {
        pthread_join(thread_pool_[i], NULL);
        pthread_detach(thread_pool_[i]);
    }
}

void *JobScheduler::threadExecute(void *args) {
    thread_args *arg = (thread_args *)args;
    JobScheduler *sched = (JobScheduler *)arg->object;
    uint32_t id = (uint32_t)arg->thread_id;
    delete arg;
    arg = NULL;
    sched->serve(id);
    return NULL;
}

void JobScheduler::serve(const uint32_t &id) {
    Job *exec_job = NULL;
    uint32_t thread_id = id;
    Garray<Job *> local_jobs;

    while (termination_[thread_id] == false) {
        pthread_mutex_lock(&served_mutex_);
        while (served_[thread_id] == true && termination_[thread_id] == false)
            pthread_cond_wait(&cond_served_, &served_mutex_);
        pthread_mutex_unlock(&served_mutex_);

        pthread_mutex_lock(&queue_mutex_);
        while (job_queue_.getElements() <= 0 && termination_[thread_id] == false)
            pthread_cond_wait(&cond_nonempty_, &queue_mutex_);

        //Get thread's assigned jobs
        for (uint32_t i = 0; i < jobs_per_thread[thread_id]; i++)
            local_jobs.enstack(job_queue_.popFront());

        pthread_mutex_unlock(&queue_mutex_);

        for (uint32_t i = 0; i < jobs_per_thread[thread_id]; i++) {
            exec_job = local_jobs[i];
            // cout << "job " << exec_job->getJobId() << " starting at thread " << thread_id << endl;
            result_arr_[exec_job->getJobId()] = exec_job->serve(thread_id);
            delete exec_job;
            exec_job = NULL;

        }
        if (jobs_per_thread[thread_id] > 0) {
            pthread_mutex_lock(&lockf_);
            total_finished += jobs_per_thread[thread_id];
            pthread_cond_signal(&finished_);
            pthread_mutex_unlock(&lockf_);
            local_jobs.clear();
            pthread_mutex_lock(&served_mutex_);
            served_[thread_id] = true;
            pthread_mutex_unlock(&served_mutex_);
            jobs_per_thread[thread_id] = 0;
        }
    }
    pthread_exit(NULL);
}

void JobScheduler::submitJob(Job *job) {
    job_queue_.enqueue(job);
}

void JobScheduler::jobAssignmentPerThread() {
    uint32_t total_tasks = job_queue_.getElements();
    uint32_t left = total_tasks;

    for (uint32_t i = 0; i < execution_threads_ && left > 0; i++) {
        jobs_per_thread[i] = total_tasks / execution_threads_;
        if (jobs_per_thread[i] == 0)
            jobs_per_thread[i] = 1;
        // cout << "thread i " << jobs_per_thread[i] << " jobs" << endl;
        left -= jobs_per_thread[i];
    }

    if (left > 0)
        jobs_per_thread[0] += left;
}

void JobScheduler::waitAllTasksFinish() {
    uint32_t total_tasks = job_queue_.getElements();
    pthread_mutex_lock(&lockf_);
    while (total_finished < total_tasks)
        pthread_cond_wait(&finished_, &lockf_);
    pthread_mutex_unlock(&lockf_);
    // cout << "finished" << endl;
}

void JobScheduler::terminateThreads() {
    for (uint32_t i = 0; i < execution_threads_; i++) {
        termination_[i] = true;
        jobs_per_thread[i] = 0;
    }
    pthread_cond_broadcast(&cond_served_);
    pthread_cond_broadcast(&cond_nonempty_);
}

void JobScheduler::executeAllJobs() {
    // ShortestPath::increaseExploredSet; for each ShortestPath object (to include new nodes from current batch)
    // Maybe call it from OperationsControl just before calling executeAllJobs, so as not to include a ShortestPath reference in this module
    // cout << "waking up threads" << endl;
    // cout << job_queue_.getElements() << endl;
    // uint32_t total_tasks = job_queue_.getElements();
    total_finished = 0;
    // uint32_t total_tasks = job_queue_.getElements();
    jobAssignmentPerThread();
    // pthread_mutex_lock(&served_mutex_);
    for (uint32_t i = 0; i < execution_threads_; i++)
        served_[i] = false;
    pthread_cond_broadcast(&cond_served_);
    // pthread_mutex_unlock(&served_mutex_);
    pthread_cond_broadcast(&cond_nonempty_);
    waitAllTasksFinish();
}

int DynamicJob::serve(const uint32_t &id) {
    int ret = paths_[id]->shortestPath(source_, target_, 'A');
    paths_[id]->reset();
    return ret;
}

int StaticJob::serve(const uint32_t &id) {
    // cout << "thread id " << id << endl;
    // cout << "source = " << source_ << " target = " << target_ << endl;
    int ret = -1;
    if (scc_.findNodeStronglyConnectedComponentID(source_) == scc_.findNodeStronglyConnectedComponentID(target_))
        ret = paths_[id]->shortestPath(source_, target_, 'S');
    // else if (scc_.findNodeStronglyConnectedComponentID(target_) > scc_.findNodeStronglyConnectedComponentID(source_))
    //     ret = -2;

    if (ret > -1) {
        paths_[id]->reset();
        return ret;
    }

    enum GRAIL_ANSWER grail_ans;
    if ((grail_ans = grail_.isReachableGrailIndex(source_, target_, 'R')) == NO || (grail_ans = grail_.isReachableGrailIndex(target_, source_, 'L')) == NO) {
        return -1;
    } else if (grail_ans == MAYBE) {
        ret = paths_[id]->shortestPath(source_, target_, 'G');
        paths_[id]->reset();
        return ret;
    }
}
