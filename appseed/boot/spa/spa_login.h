#pragma once


namespace spa_install
{

   class plugin;

} // namespace spa


class CLASS_DECL_BOOT spa_login :
   public simple_ui
{
public:



   enum e_result
   {
      
      result_ok,
      result_wrong_password,
      result_fail,
      result_registration_deferred

   };

   class CLASS_DECL_BOOT callback
   {
   public:

       virtual void login_result(e_result eresult);

   };

   simple_label         m_labelUser;
   simple_edit_box      m_editUser;
   simple_label         m_labelPassword;
   simple_password      m_password;
   simple_tap           m_tap;

   string             m_strPasshash;

   callback *           m_pcallback;
   string             m_strKeyHash;

   
   spa_login();
   virtual ~spa_login();


   virtual void on_action(const char * pszId);

   void initialize();

   void defer_translate(::spa_install::plugin * pplugin);

   void start_login();

   static uint32_t thread_proc_login(void * lpParam);

   e_result login();

   string calc_key_hash();


   virtual void login_result(e_result eresult);

   virtual void authentication_succeeded();

   virtual void authentication_failed();


};





