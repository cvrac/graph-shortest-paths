#include "JobScheduler.hpp"

#include <iostream>
#include <sys/signal.h>


JobScheduler::JobScheduler(const uint32_t &pool_size, Garray<int> &resarr) : execution_threads_(pool_size),
 total_finished(0), jobs_per_thread(pool_size), thread_pool_(pool_size), job_queue_(pool_size),
 served_(pool_size), termination_(pool_size), result_arr_(resarr) {
    pthread_mutex_init(&queue_mutex_, 0);
    pthread_cond_init(&cond_nonempty_, 0);
    pthread_mutex_init(&lockf_, 0);
    pthread_cond_init(&finished_, 0);
    pthread_mutex_init(&served_mutex_, 0);
    pthread_cond_init(&cond_served_, 0);

    jobs_per_thread.setElements(execution_threads_);
    thread_pool_.setElements(execution_threads_);
    served_.setElements(execution_threads_);
    termination_.setElements(execution_threads_);

    thread_args *args;
    for (uint32_t i = 0; i < execution_threads_; i++) {
        jobs_per_thread[i] = 0;
        served_[i] = false;
        termination_[i] = false;
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
    // cout << "thread_id = " << thread_id << endl;
    Garray<Job *> local_jobs(10);

    while (termination_[thread_id] == false) {
        //cout << "Thread " << id << " served_mutex lock" << endl;
        pthread_mutex_lock(&served_mutex_);
        while (served_[thread_id] == true && termination_[thread_id] == false)
            pthread_cond_wait(&cond_served_, &served_mutex_);
        //cout << "Thread " << id << " served_mutex unlock" << endl;
        pthread_mutex_unlock(&served_mutex_);

        //cout << "Thread " << id << " queue_mutex lock" << endl;
        pthread_mutex_lock(&queue_mutex_);
        while (jobs_per_thread[thread_id] <= 0 && termination_[thread_id] == false)
            pthread_cond_wait(&cond_nonempty_, &queue_mutex_);

        //Get thread's assigned jobs
        for (uint32_t i = 0; i < jobs_per_thread[thread_id]; i++)
            local_jobs.enstack(job_queue_.popFront());

        //cout << "Thread " << id << " queue_mutex unlock" << endl;
        pthread_mutex_unlock(&queue_mutex_);

        for (uint32_t i = 0; i < local_jobs.getElements() && termination_[thread_id] == false; i++) {
            exec_job = local_jobs[i];
            if (exec_job == NULL) break;
            //cout << "job " << exec_job->getJobId() << "(" << exec_job->getSource() << "," << exec_job->getTarget() <<") starting at thread " << thread_id << endl;
            result_arr_[exec_job->getJobId()] = exec_job->serve(thread_id);
            delete exec_job;
            exec_job = NULL;

        }
        if (jobs_per_thread[thread_id] > 0 && termination_[thread_id] == false) {
            served_[thread_id] = true;
            local_jobs.clear();

            //cout << "Thread " << id << " lockf lock" << endl;
            pthread_mutex_lock(&lockf_);
            total_finished += jobs_per_thread[thread_id];
            jobs_per_thread[thread_id] = 0;
            pthread_cond_signal(&finished_);
            //cout << "Thread " << id << " lockf unlock" << endl;
            pthread_mutex_unlock(&lockf_);
        }
    }
    pthread_exit(NULL);
}

void JobScheduler::submitJob(Job *job) {
    // pthread_mutex_lock(&queue_mutex_);
    job_queue_.enqueue(job);
    // pthread_mutex_unlock(&queue_mutex_);
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
    /*cout << "Jobs per thread" << endl;
    for (uint32_t i = 0; i < execution_threads_ ; i++) {
        cout << jobs_per_thread[i] << endl;
    }*/
}
void JobScheduler::waitAllTasksFinish(const uint32_t &total_tasks) {
    pthread_mutex_lock(&lockf_);
    while (total_finished < total_tasks) {
        //cout << "total_finished " << total_finished << endl;
        pthread_cond_wait(&finished_, &lockf_);
    }
     //cout << "finished" << endl;
    pthread_mutex_unlock(&lockf_);
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
    uint32_t total_tasks = job_queue_.getElements();
    pthread_cond_broadcast(&cond_served_);
    // pthread_mutex_unlock(&served_mutex_);
    pthread_cond_broadcast(&cond_nonempty_);
    waitAllTasksFinish(total_tasks);
}

int DynamicJob::serve(const uint32_t &id) {
    if (mode_ == 'n') {
        int ret = paths_[id]->shortestPath(source_, target_, 'D', current_version_);
        paths_[id]->reset();
        return ret;
    } else if (mode_ == 'c') {
        if (cc_.sameConnectedComponent(source_, target_, current_version_)) {
            int ret = paths_[id]->shortestPath(source_, target_, 'D', current_version_);
            paths_[id]->reset();
            return ret;
        }
        else {
            //cout << "s";
            return -1;
        }
    }
}

int StaticJob::serve(const uint32_t &id) {
     //cout << "thread id " << id << endl;
     //cout << "source = " << source_ << " target = " << target_ << endl;
    int ret = -1;
    if (scc_.findNodeStronglyConnectedComponentID(source_) == scc_.findNodeStronglyConnectedComponentID(target_))
        ret = paths_[id]->shortestPath(source_, target_, 'S', 0);
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
        ret = paths_[id]->shortestPath(source_, target_, 'G', 0);
        paths_[id]->reset();
        return ret;
    }
}
