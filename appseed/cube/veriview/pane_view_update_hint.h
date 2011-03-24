#pragma once

namespace veriview
{

enum EPaneView
{
   PaneViewNone,
   PaneViewContextMenu,
   PaneViewSourceEdit,
   PaneViewHtmlEdit,
   PaneViewHtml,
   PaneViewFileManager,
   PaneViewPlaylist,
   PaneViewMediaLibrary,
   PaneViewAudioControl,
   PaneViewOptions,
};


class CLASS_DECL_CA2_CUBE pane_view_update_hint :
   public ::radix::object  
{
public:
   enum e_type
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
      TypeOpenDocument,
   };
   
public:
   void set_type(e_type e_type);
   bool is_type_of(e_type e_type);

   pane_view_update_hint();
   virtual ~pane_view_update_hint();

   int   m_iId;
protected:
   e_type m_etype;

};


} // namespace veriview