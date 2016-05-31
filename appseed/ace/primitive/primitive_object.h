#pragma once


class var;
class application_bias;
class create;
class command_line;
#include "ace/multithreading/multithreading_wait_result.h"
// Duplicated root here... element is essentially like root (Rute, Inha, Lenir) for templates, but not for polymorphism



//class CLASS_DECL_ACE ::object :
class CLASS_DECL_ACE object
   // virtual public element
   //class CLASS_DECL_ACE waitable :
   //class CLASS_DECL_ACE object
   //   virtual public ::object
{
public:

   //class CLASS_DECL_ACE element //:
   //   //virtual public root
   //{
   //public:


   enum flag
   {

      flag_auto_clean = 1 << 0,
      flag_discard_to_factory = 1 << 1,
      flag_ready_for_delete = 1 << 2,
      flag_auto_delete = 1 << 3,
      flag_heap_alloc = 1 << 4,
      flag_locked = 1 << 5

   };


   uint64_t                      m_ulFlags;
   factory_item_base *           m_pfactoryitembase;
   void *                        m_pthis;
   int64_t                       m_countReference;
   ::ace::application *         m_paceapp;
   mutex *                       m_pmutex;
   property_set *                m_psetObject;



//   ::datetime::time              m_time;

   // OBJECT :: object :> is a a a root, and is an element

   //element();
   //element(const element & o);
   //element(::ace::application * papp);
   //virtual ~element();

   object();
   object(::ace::application * papp);
   object(const object & objectSrc);              // no implementation
   virtual ~object();  // virtual destructors are necessary


   template < typename PRED >
   inline void fork(PRED pred);


   virtual void delete_this();


   virtual object * clone();


   static void system(const char * pszProjectName);

   inline ::ace::allocatorsp & allocer();

   inline ::ace::allocatorsp & allocer() const { return ((object *)this)->allocer(); }

   inline ::ace::application * get_app() const { return m_paceapp; }

   virtual void set_app(::ace::application * papp);

   inline bool is_set_ca_flag(object::flag eflag)
   {
      return (m_ulFlags & ((uint32_t)eflag)) == (uint32_t)eflag;
   }

   inline void clear_ca_flag(object::flag eflag)
   {
      m_ulFlags &= ~eflag;
   }

   inline void set_ca_flag(object::flag eflag)
   {

      m_ulFlags |= eflag;

   }


   //   object & operator = (const object & o);





   inline int64_t get_ref_count()
   {

      return m_countReference;

   }

   inline bool is_heap()
   {

      return (m_ulFlags & (uint64_t) flag_heap_alloc) != 0;

   }


   virtual int64_t add_ref();
   virtual int64_t dec_ref();
   virtual int64_t release();

   // OBJECT :: object :> is a ::object

   virtual void add_line(const char * pszCommandLine,application_bias * pbiasCreate = NULL);
   virtual void add_line_uri(const char * pszCommandLine,application_bias * pbiasCreate = NULL);

   virtual void add_fork(const char * pszCommandLine,application_bias * pbiasCreate = NULL);
   virtual void add_fork_uri(const char * pszCommandLine,application_bias * pbiasCreate = NULL);


   // semantics defined by the requested object - ::object implementator
   virtual void request_file(var & varFile);
   virtual void request_file_query(var & varFile,var & varQuery);
   virtual void request_command(sp(command_line) pcommandline);
   virtual void request_create(sp(::create) pcreatecontext);

   // another name for request
   virtual void create(sp(::create) pcreatecontext);


   // main loosely coupled semantics :
   // varFile   : empty, one file path, many file paths, one file object, one or more file objects, or Url, of cached, downloaded, dowloading or queuing files to be opened
   // varQuery  : more ellaborated requests for the requested object - syntax and semantic defined by requested object - ::object implementator
   // virtual void on_request(sp(command_line) pcommandline);
   virtual void on_request(sp(::create) pcreatecontext);




   // OBJECT :: object :> is a waitable

   //waitable();
   //waitable(const waitable & objectSrc);
   //virtual ~waitable();


   //virtual void * get_os_data() const;


   //virtual void lock();
   //virtual bool lock(const duration & durationTimeout);
   //virtual bool unlock();
   //virtual bool unlock(LONG lCount,LPLONG lpPrevCount = NULL);


   ///  \brief		abstract function to initialize a waiting action without a timeout
   //virtual void wait();

   ///  \brief		*no more as of 2012-05-12* abstract function to initialize a waiting action with a timeout
   ///  \param		duration time period to wait for item
   ///  \return	waiting action result as wait_result
   //virtual wait_result wait(const duration & duration);


   //virtual bool is_locked() const;


   virtual string lstr(id id, const string & strDefault = (const string &) *((const string *) NULL ));

   // OBJECT :: object :> is a object

   void common_construct();

   bool IsSerializable() const;


   property & oprop(const char * psz);
   property & oprop(const char * psz) const;
   property_set & oprop_set();


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   object & operator = (const object & objectSrc);       // no implementation


   inline sp(::command_thread) command_thread();


   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
   // OBJECT :: object :> is an ace::live_object
//{
//
//
//   class CLASS_DECL_ACE live_object:
//   virtual public root
//   {
//   public:

      virtual void keep_alive();
      virtual void on_keep_alive();
      virtual bool is_alive();

   //};


//} // namespace ace


};




//};


namespace ace
{


   class CLASS_DECL_ACE allocator:
      virtual public object
   {
   public:


      virtual ~allocator();


   };


   class CLASS_DECL_ACE allocatorsp:
      public sp(allocator)
   {
   public:


      allocatorsp(::ace::application * papp);


   };



} // namespace ace






//class CLASS_DECL_ACE object :
//   virtual public waitable
//{
//public:
//
//
//   property_set *     m_psetObject;
//
//
//   object();
//   object(const object & objectSrc);              // no implementation
//   virtual ~object();  // virtual destructors are necessary
//
//
//   void common_construct();
//
//   bool IsSerializable() const;
//
//
//   property & oprop(const char * psz);
//   property & oprop(const char * psz) const;
//   property_set & oprop_set();
//
//
//   virtual void assert_valid() const;
//   virtual void dump(dump_context & dumpcontext) const;
//
//   object & operator = (const object & objectSrc);       // no implementation
//
//
//   inline sp(::command_thread) command_thread();
//
//
//   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
//
//};
//







template < class T >
T * dereference_no_delete(T * p) { p->m_ulFlags |= (uint64_t) ::object::flag_heap_alloc; p->m_countReference--; return p; }




template < class c_derived >
inline int64_t add_ref(c_derived * pca)
{
   if(pca == NULL)
      return -1;
   return pca->add_ref();
}

template < class c_derived >
inline int64_t release(c_derived * & pca)
{
   if(pca == NULL)
      return -1;
   c_derived * p = pca;
   pca = NULL;
   try
   {
      int64_t count = p->release();
      return count;
   }
   catch(...)
   {
      return -1;
   }
}



template < class c_derived >
inline int64_t ref_count(c_derived * pca)
{
   if(pca == NULL)
      return -1;
   return pca->get_ref_count();
}


template < class TYPE >
bool is_null(TYPE * p)
{
   return (((int_ptr)p) < sizeof(TYPE));
}


template < class TYPE >
bool is_null(TYPE & t)
{
   return (((int_ptr)&t) < sizeof(TYPE));
}


template <class t>
inline void delptr(t *& p)
{
   if(p != NULL)
   {
      delete p;
      p = NULL;
   }
}




#define canew(x) dereference_no_delete(new x)



