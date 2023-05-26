#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>

namespace ThreadPool
{
#define MAX_THREAD_NUM 8

	//�̳߳أ������ύ��κ�����lambda���ʽ����������ִ�У����Ի�ȡִ�з���ֵ
	//֧�����Ա������֧���ྲ̬��Ա������ȫ�ֺ�����Operator()������
	class ThreadPool
	{
		typedef std::function<void()> Task;
	private:
		std::vector<std::thread> m_pool;     // �̳߳�
		std::queue<Task> m_tasks;    // �������
		std::mutex m_lock;    // ͬ����
		std::condition_variable m_cv;   // ��������
		std::atomic<bool> m_isStoped;    // �Ƿ�ر��ύ
		std::atomic<int> m_idleThreadNum;  //�����߳�����
	public:
		ThreadPool(int size = MAX_THREAD_NUM)
		{
			size = size > MAX_THREAD_NUM ? MAX_THREAD_NUM : size;
			m_idleThreadNum = size;
			for (int i = 0; i < size; i++)
			{
				//��ʼ���߳�����
				m_pool.emplace_back(&ThreadPool::scheduler, this);
			}
		}
		~ThreadPool()
		{
			Close();
			while (!m_tasks.empty()) {
				m_tasks.pop();
			}
			m_cv.notify_all();  // ���������߳�ִ��
			for (std::thread& thread : m_pool) {
				if (thread.joinable()) {
					thread.join();  // �ȴ����������ǰ�����߳�һ����ִ����
				}
			}
			m_pool.clear();
		}
		// ���̳߳أ����������ύ
		void ReOpen() {
			if (m_isStoped) m_isStoped.store(false);
			m_cv.notify_all();
		}
		// �ر��̳߳أ�ֹͣ�ύ������
		void Close() {
			if (!m_isStoped) m_isStoped.store(true);
		}
		// �ж��̳߳��Ƿ񱻹ر�
		bool IsClosed() const {
			return m_isStoped.load();
		}
		// ��ȡ��ǰ��������е�������
		int GetTaskSize() { 
			return m_tasks.size(); 
		}
		// ��ȡ��ǰ�����߳���
		int IdleCount() { 
			return m_idleThreadNum; 
		}
		// �ύ����ִ��
		// ���÷�ʽΪ std::future<returnType> var = threadpool.Submit(...)
		// var.get() ��ȴ�����ִ���꣬����ȡ����ֵ
		// ���� ... ����ֱ���ú�����+�����������棬���� threadpool.Submit(f, 0, 1)
		// �����Ҫ�������Ա����������������·�ʽ
		// threadpool.Submit(std::bind(&Class::Func, &classInstance)) ��
		// threadpool.Submit(std::mem_fn(&Class::Func), &classInstance)
		template<class F, class... Args>
		auto Submit(F&& f, Args&&... args)->std::future<decltype(f(args...))>
		{
			using RetType = decltype(f(args...));  // typename std::result_of<F(Args...)>::type, ���� f �ķ���ֵ����
			std::shared_ptr<std::packaged_task<RetType()>> task = std::make_shared<std::packaged_task<RetType()>>(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...)
				);
			std::future<RetType> future = task->get_future();
			// ��װ������ӵ�����
			addTask([task](){
				(*task)(); 
			});

			return future;
		}
	private:
		// ������
		Task getTask() {
			std::unique_lock<std::mutex> lock(m_lock); // unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
			while (m_tasks.empty() && !m_isStoped) {
				m_cv.wait(lock);
			}  // wait ֱ���� task
			if (m_isStoped) {
				return Task();
			}
			assert(!m_tasks.empty());
			Task task = std::move(m_tasks.front()); // ȡһ�� task
			m_tasks.pop();
			m_cv.notify_one();
			return task;
		}

		// ������
		void addTask(Task task)
		{
			std::lock_guard<std::mutex> lock{ m_lock }; //�Ե�ǰ��������� lock_guard �� mutex �� stack ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()
			m_tasks.push(task);
			m_cv.notify_one(); // ����һ���߳�ִ��
		}

		// �����߳���ѭ������
		void scheduler()
		{
			while (!m_isStoped.load()) {
				// ��ȡһ����ִ�е� task
				Task task(getTask());
				if (task) {
					m_idleThreadNum--;
					task();
					m_idleThreadNum++;
				}
			}
		}
	};
}

#endif