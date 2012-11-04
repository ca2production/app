#pragma once


namespace ca
{


   class window;


} // namespace ca


namespace user
{


   class CLASS_DECL_ca oswindow_array :
      public comparable_array < oswindow, oswindow >
   {
   public:
      void SortByZOrder();
      void SortSiblingsByZOrder();
      void top_windows_by_z_order();
   };


   class CLASS_DECL_ca interaction_ptr_array :
      virtual public pha(::user::interaction)
   {
   public:
//      using pha(::user::interaction)::find_first;
      ::user::interaction * find_first(::ca::type_info info);
      ::user::interaction * find_first(oswindow oswindow);
      void get_wnda(user::oswindow_array & oswindowa);
      void send_message(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);
      void send_message_to_descendants(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0, bool bRecursive = true);
   };


   class CLASS_DECL_ca oswindow_tree
   {
   public:

      class CLASS_DECL_ca Array :
         public array_ptr_alloc < oswindow_tree, const oswindow_tree &>
      {
      public:
         bool remove(oswindow oswindow);
         int_ptr find(oswindow oswindow);
         void EnumDescendants();
         Array & operator = (oswindow_array & oswindowa);

      };

      oswindow_tree();
      oswindow_tree(const oswindow_tree & tree);

      oswindow   m_oswindow;
      DWORD m_dwUser;
      oswindow m_pvoidUser;
      Array m_oswindowtreea;
      public:
         void EnumDescendants();
      static int compare_oswindow(oswindow_tree & tree1,  oswindow_tree & tree2);
      public:
      oswindow_tree & operator = (const oswindow_tree & tree);
   };


   class CLASS_DECL_ca window_util
   {
   public:
      static void ContraintPosToParent(oswindow oswindow);
      //static void EnumChildren(::ca::window * pwnd, interaction_ptr_array & wndpa);
      static void EnumChildren(oswindow oswindow, oswindow_array & oswindowa);
      /*static void ExcludeChild(interaction_ptr_array & wndpa);*/
      /*static void SortByZOrder(interaction_ptr_array & wndpa);*/
      static void SortByZOrder(oswindow_array & oswindowa);
      static HRGN GetAClipRgn(oswindow oswindow, POINT ptOffset, bool bExludeChilren);
      static void ExcludeChildren(oswindow oswindow, HRGN hrgn, POINT ptOffset);
      window_util();
      virtual ~window_util();
      /*static void SendMessageToDescendants(oswindow oswindow, UINT message,
         WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm);*/
      static void SendMessageToDescendants(oswindow oswindow, UINT message,
         WPARAM wParam, LPARAM lParam, bool bDeep);
      static bool IsAscendant(oswindow oswindowAscendant, oswindow oswindowDescendant);

      static int GetZOrder(oswindow oswindow);
      static void GetZOrder(oswindow oswindow, int_array & ia);

//      static HRGN GetAClipRgn(oswindow oswindow, POINT ptOffset, bool bExludeChilren);
//      static void ExcludeChildren(oswindow oswindow, HRGN hrgn, POINT ptOffset);

      //static void SortByZOrder(comparable_array < ::ca::window *, ::ca::window * > & wndpa);
      //static void SortByZOrder(comparable_array < oswindow, oswindow > & oswindowa);
      //static void EnumChildren(oswindow oswindow, comparable_array < oswindow, oswindow > & oswindowa);

   };




}

