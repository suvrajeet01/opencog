/*
 * WordSenseProcessor.h
 *
 * Main entry point for word-sense disambiguation. This class inherits
 * from Agent; it scans for new input sentences, and then invokes
 * the disambiguation algorithms on it.
 *
 * Copyright (c) 2008 Linas Vepstas <linas@linas.org>
 */

#ifndef _OPENCOG_WORD_SENSE_PROCESSOR_H
#define _OPENCOG_WORD_SENSE_PROCESSOR_H

#include <pthread.h>
#include <opencog/server/CogServer.h>
#include <opencog/nlp/wsd/Mihalcea.h>

namespace opencog {

class WordSenseProcessor 
{
	private:

		bool do_use_threads;
		pthread_t worker;
		static void * thread_start(void *);
		std::queue<Handle> work_queue;
		pthread_mutex_t queue_lock;
		bool thread_running;
		void work_thread(void);

		int cnt;
		AtomSpace *atom_space;
		bool do_document(Handle h);

		Handle start_handle;
		Handle completion_handle;
		bool check_start(Handle h);

		Mihalcea *wsd;

		void run_wsd(void);

	public:

		WordSenseProcessor(void);
		virtual ~WordSenseProcessor();
		virtual void init(void);
		virtual void run(CogServer *server);
		virtual void run_no_delay(CogServer *server);
		void use_threads(bool);
};

} // namespace opencog

#endif // _OPENCOG_WORD_SENSE_PROCESSOR_H
