//
//  multithreading_set_event_on_exit.h
//  ace
//
//
//


class CLASS_DECL_ACE set_event_on_exit
{
public:
   
   
   event * m_pevent;
   
   
   set_event_on_exit(event & ev) { m_pevent = &ev; }
   ~set_event_on_exit() { if(m_pevent != NULL) m_pevent->set_event(); }
   
   
};






