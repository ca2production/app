#pragma once


#define FILE_MANAGER_ID_FILE_NAME 1


class FileManagerInterface;


namespace fs
{


   class item;
   class item_array;


} // namespace fs




namespace filemanager
{


   enum EFolder
   {


      FolderMyComputer,


   };


   class CLASS_DECL_CORE SimpleFolderTreeInterface :
      public ::userfs::tree,
      virtual public FileManagerViewInterface
   {
   public:


      enum e_message
      {
         MessageMainPost,
      };
      enum EMessageMainPost
      {
         MessageMainPostCreateImageListItemRedraw,
      };

      enum ETimer
      {
         TimerDelayedListUpdate = 100,
         TimerCreateImageList
      };


      critical_section        m_csBrowse;
      bool                    m_bCreateImageList;
      bool                    m_bCreateImageListRedraw;
      int32_t                     m_iAnimate;
      bool                    m_bTimer123;
      stringa                 m_straUpdatePtrFilter;
      mutex                   m_mutexMissinUpdate;
      stringa                 m_straMissingUpdate;
      bool                    m_bDelayedListUpdate;
#ifdef WINDOWSEX
      map < EFolder, EFolder, IShellFolder *, IShellFolder *> m_mapFolder;
#endif
      sp(::data::tree_item)        m_pdataitemCreateImageListStep;
      string                  m_strPath;
      //sp(image_list)            m_pimagelistFs;
      int32_t   m_iDefaultImage;
      int32_t   m_iDefaultImageSelected;


      SimpleFolderTreeInterface(sp(base_application) papp);
      virtual ~SimpleFolderTreeInterface();


      virtual void _001InsertColumns();
      //virtual void _001CreateImageList(CColumn & column);
      virtual void _001UpdateImageList(sp(::data::tree_item) pitem);

      DECL_GEN_VSIGNAL(_001OnTimer)


      virtual void _017Synchronize();
      void install_message_handling(::message::dispatch * pinterface);


      void _StartCreateImageList();
      void _StopCreateImageList();
      void _CreateImageListStep();

      // user::tree
      virtual void _001OnOpenItem(sp(::data::tree_item) pitem);
      virtual void _001OnItemExpand(sp(::data::tree_item) pitem);
      virtual void _001OnItemCollapse(sp(::data::tree_item) pitem);


      virtual void _017OpenFolder(sp(::fs::item)  item);

      virtual COLORREF get_background_color();


#ifdef WINDOWSEX

      int32_t MapToCSIDL(EFolder efolder);

      IShellFolder * _001GetFolder(EFolder efolder);

#endif


      void _017PreSynchronize();
      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      DECL_GEN_SIGNAL(_001OnMainPostMessage)
      void GetSelectedFilePath(stringa & stra);
      virtual bool _001IsTranslucent();

      void _017Browse(const char * lpcsz, bool bForceUpdate = false);
      void _017UpdateList();
      void _017UpdateList(const char * lpcsz, sp(::data::tree_item) pitemParent, int32_t iLevel);
      void _017UpdateZipList(const char * lpcsz, sp(::data::tree_item) pitemParent, int32_t iLevel);
      void _017EnsureVisible(const char * lpcsz);

      sp(::data::tree_item) find_item(const char * lpcsz);



   protected:


      void _StartDelayedListUpdate();
      void _StopDelayedListUpdate();
      void _DelayedListUpdate();


   };


} // namespace filemanager



