class   Buffer
{
  enum { SIZE   = 16 };

  int   array_[SIZE];
  int   inIndex_;
  int   outIndex_;
  int   numItems_;
  pthread_mutex_t	lock_;
  pthread_cond_t	notEmpty_;
  pthread_cond_t	notFull_;

public :

  Buffer        ()
  {
    inIndex_ = outIndex_ = numItems_ = 0;
    pthread_mutex_init(&lock_,NULL);
    pthread_cond_init(&notEmpty_,NULL);
    pthread_cond_init(&notFull_,NULL);
  }

  ~Buffer       ()
  {
    pthread_mutex_destroy(&lock_);
    pthread_cond_destroy(&notEmpty_);
    pthread_cond_destroy(&notFull_);
  }

  int   getNumItems  () const
  { return(numItems_); }

  void  putIn (int    i)
  {
    pthread_mutex_lock(&lock_);
    while  (getNumItems() >= SIZE)
    {
      printf("Full!  Waiting!\n");
      usleep(10 + rand() % 10);
      pthread_cond_wait(&notFull_,&lock_);
    }

    array_[inIndex_] = i;
    countArray[array_[inIndex_]]++;

    usleep(10 + rand() % 10);
    inIndex_++;
    numItems_++;
    if  (inIndex_ >= SIZE)
      inIndex_ = 0;
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&notEmpty_);
  }

  int   pullOut ()
  {
    pthread_mutex_lock(&lock_);
    while  (getNumItems() <= 0)
    {
      printf("Empty!  Waiting!\n");
      usleep(10 + rand() % 10);
      pthread_cond_wait(&notEmpty_,&lock_);
    }

    countArray[array_[outIndex_]]--;
    int toReturn        = array_[outIndex_];

    usleep(10 + rand() % 10);
    outIndex_++;
    numItems_--;
    if  (outIndex_ >= SIZE)
      outIndex_ = 0;

    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&notFull_);
    return(toReturn);
  }
};
