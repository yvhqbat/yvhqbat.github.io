## When pthread_join called, I get an error “Resource deadlock avoided”


### Q
As I mentioned in the title, when I try to join the threads, I get an error.

m_threadid : 4615464704, pthread_join error : Resource deadlock avoided, thread name : NetworkWorker

I was wondering what kind of situation it is and any suggestion on fixing this.

Thank you

### A
  	 	
This error (EDEADLK) results when you have a closed loop of threads trying to join each other. 
In the simplest cases, this is either a thread calling pthread_join() on itself, or two threads calling pthread_join() on each other.
