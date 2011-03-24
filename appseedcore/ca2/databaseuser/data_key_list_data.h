#pragma once

namespace databaseuser
{

   class CLASS_DECL_ca data_key_list_data :
      public ::user::list_data,
      public ::database::client
   {
   public:


      data_key_list_data(::ca::application * papp);
      virtual ~data_key_list_data(void);


      virtual bool _001GetItemText(::user::list * plist, string &str, index iItem, index iSubItem, index iListItem);

      virtual count _001GetItemCount();

      bool add_unique(const stringa & stra);
      bool remove(const stringa & stra);

      void GetSel(::user::list * plist , stringa & stra);
   };

} // namespace databaseuser